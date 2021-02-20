comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: char_out.inc                                                       *
*                                                                          *
* DESCRIPTION:                                                             *
*   'Prints' characters to the E9 port or the screen using the BIOS        *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 19 Feb 2021                                                *
*                                                                          *
*                                                                          *
***************************************************************************|

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; if we have included this after the first sector, we are in error...
.ifa $, 200h
%error 1, 'This must be in the first sector of the code...'
.endif

OUTPORT  equ  0xE9   ; if this is defined, we print to the E9 io port
USEBIOS  equ  0      ; if this is defined, we print to the screen using the BIOS

.if ((USEBIOS == 1) && (OPTION == 1))
.error 'Cannot use the BIOS to display chars in Option 1'
.endif

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine prints characters to a specified target:
;   OUTPORT = 0xE9
;   USEBIOS = BIOS interrupt 0Eh
; On entry:
;       al = char to display
; On return:
;       nothing
display_char proc near uses ax

.if IGNORECR
           cmp  al,13
           je   display_char_done
.endif

; use the given IO out port technique
.if (OUTPORT > 0)
           push dx
           mov  dx,OUTPORT
           out  dx,al
           pop  dx
.endif
.if (USEBIOS == 1)
           ; display a char to the screen using the BIOS
           push bx
           mov  ah,0Eh             ; print char service
           xor  bx,bx              ; 
           int  10h                ; output the character
           pop  bx
.endif
display_char_done:
           ret
display_char endp

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; display a space(s)
; On entry:
;   nothing
; On return:
;   nothing
display_space proc near uses ax
           mov  al,' '
           call display_char
           ret
display_space endp

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; display end of line
; On entry:
;   nothing
; On return:
;   nothing
display_eol proc near uses ax
           mov  al,13
           call display_char
           mov  al,10
           call display_char
           ret
display_eol endp

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; display a string
; On entry:
;   ds:si -> asciiz string to display
; On return:
;   nothing
display_string proc near uses ax si
           cld
@@:        lodsb
           or   al,al
           jz   short @f
           call display_char
           jmp  short @b
@@:        ret
display_string endp

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; display a 16-decimal number
;  * zero left-pads the number *
; On entry:
;   ax = number to print
; On return:
;   nothing
display_dec16 proc near uses ax bx cx dx
           mov  cx,5                    ; at most 5 chars (used to zero pad) (16-bit number max = 65535, 5 chars)
           mov  bx,0FFFFh               ; Ending flag
           push bx
           mov  bx,10
PD1:       dec  cx                      ; 'count' of chars in this number
           xor  dx,dx
           div  bx                      ; Divide by 10
           push dx                      ; Store remainder
           or   ax,ax                   ; Are we done?
           jnz  short PD1               ; No, so continue
           jcxz short PD3
PD2:       mov  al,'0'
           call display_char
           loop short PD2
PD3:       pop  ax                      ; Character is now in DL
           cmp  ax,0FFFFh               ; Is it the ending flag?
           je   short PD4               ; Yes, so continue
           add  al,'0'                  ; Convert to ASCII
           call display_char
           jmp  short PD3               ; Keep doing it
PD4:       ret
display_dec16 endp


.if (HIGHEST_CPU == 3)
; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; display a hexadecimal number
; On entry:
;   eax = number to print
; On return:
;   nothing
display_hex32 proc near  ; cannot use 'uses' since the ret will pop ax each time we execute it
hexdd:  push    eax
        shr     eax,16          ;do high word first
        call    hexdw
        pop     eax
hexdw:  push    eax
        shr     eax,8           ;do high byte first
        call    hexdb
        pop     eax
hexdb:  push    eax
        shr     eax,4           ;do high nibble first
        call    hexdn
        pop     eax
hexdn:  and     eax,0Fh         ;isolate nibble
        add     al,'0'          ;convert to ascii
        cmp     al,'9'          ;valid digit?
        jbe     hexdn1          ;yes
        add     al,7            ;use alpha range
hexdn1: call    display_char
        ret
display_hex32 endp

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; standard out string
; prints the following registers
;  eax, ebx, ecx, edx, esi, edi, ebp, eflags
; On entry:
;   the above registers contain the values to print
; On return:
;   nothing
std_out    proc near uses eax si
           
           ; save the flags register
           pushfd
           push ebp
           push edi
           push esi
           push edx
           push ecx
           push ebx
           push eax
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; print a line number
           mov  ax,LINENUM
           call display_dec16
           mov  al,':'
           call display_char
           call display_space

           pop  eax
           call display_hex32
           call display_space
           pop  eax
           call display_hex32
           call display_space
           pop  eax
           call display_hex32
           call display_space
           pop  eax
           call display_hex32
           call display_space
           pop  eax
           call display_hex32
           call display_space
           pop  eax
           call display_hex32
           call display_space
           pop  eax
           call display_hex32
           call display_space
           
           pop  eax
           and  eax,(FLAGS_CARRY | FLAGS_PARITY | FLAGS_AUXILIARY | FLAGS_ZERO | FLAGS_SIGN | FLAGS_DIRECTION | FLAGS_OVERFLOW)
           and  eax,UNDEFINED_FLAGS
           call display_hex32
           call display_eol
           
           inc  word LINENUM
           ret
std_out    endp

.else

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; display a hexadecimal number
; On entry:
;   ax = number to print
; On return:
;   nothing
display_hex16 proc near  ; cannot use 'uses' since the ret will pop ax each time we execute it
        push    ax
        mov     al,ah
        call    hexdb
        pop     ax
hexdb:  push    ax
.if (HIGHEST_CPU >= 1)
        shr     ax,4            ;do high nibble first
.else
        shr     ax,1            ;do high nibble first
        shr     ax,1
        shr     ax,1
        shr     ax,1
.endif
        call    hexdn
        pop     ax
hexdn:  and     al,0Fh          ;isolate nibble
        add     al,'0'          ;convert to ascii
        cmp     al,'9'          ;valid digit?
        jbe     hexdn1          ;yes
        add     al,7            ;use alpha range
hexdn1: call    display_char
        ret
display_hex16 endp

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; standard out string
; prints the following registers
;  ax, bx, cx, dx, si, di, bp, flags
; On entry:
;   the above registers contain the values to print
; On return:
;   nothing
std_out    proc near uses ax si
           
           ; save the flags register
           pushf
           push bp
           push di
           push si
           push dx
           push cx
           push bx
           push ax
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; print a line number
           mov  ax,LINENUM
           call display_dec16
           mov  al,':'
           call display_char
           call display_space

           pop  ax
           call display_hex16
           call display_space
           pop  ax
           call display_hex16
           call display_space
           pop  ax
           call display_hex16
           call display_space
           pop  ax
           call display_hex16
           call display_space
           pop  ax
           call display_hex16
           call display_space
           pop  ax
           call display_hex16
           call display_space
           pop  ax
           call display_hex16
           call display_space
           
           pop  ax
           and  ax,(FLAGS_CARRY | FLAGS_PARITY | FLAGS_AUXILIARY | FLAGS_ZERO | FLAGS_SIGN | FLAGS_DIRECTION | FLAGS_OVERFLOW)
           and  ax,UNDEFINED_FLAGS
           call display_hex16
           call display_eol
           
           inc  word LINENUM
           ret
std_out    endp

.endif

.end
