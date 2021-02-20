comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: test_proc.inc                                                      *
*                                                                          *
* DESCRIPTION:                                                             *
*   checks for specified processor                                         *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 19 Feb 2021                                                *
*                                                                          *
*                                                                          *
***************************************************************************|

.if (HIGHEST_CPU >= 1)
; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine checks for the 186 processor
; On entry:
;       nothing
; On return:
;       carry set if not a 186
check_186  proc near uses cx

           ; the 186 limits the shift count by anding the shift by 1Fh, resulting in CL = 0
           ; the 8086 does not
           ; therefore, a 186 will not shift CH 21h times
           ; but the 8086 will shift it 21h times, resulting in CH being zero
           mov  cx,0121h
           shl  ch,cl
           jz   short Nota186

.if (HIGHEST_CPU == 1)
           ; next, the 8086 and 186 decrement the value of SP *before* it pushes it on the stack.
           ; check that we do that too
           ; *** Please note that this check assumes the emulator is set to emulate a 80x186.
           ; *** If the emulator is set to emulate anything above a 80x186, this test will fail.
           push sp
           pop  ax
           add  ax,2
           cmp  ax,sp
           mov  si,offset Not186StrA
           jne  short Nota186a
.endif

           mov  si,offset Found186Str
           call display_string
           
           clc
           ret

Nota186:   mov  si,offset Not186Str
Nota186a:  call display_string
           
           stc
           ret
check_186  endp

Found186Str db  'Found 186...',13,10,0
Not186Str   db  'Did not find a 186!',13,10,0
Not186StrA  db  '186 didn',39,'t push SP-2',13,10,0

.endif

.if (HIGHEST_CPU >= 2)
; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine checks for the 286 processor
; On entry:
;       nothing
; On return:
;       carry set if not a 286
check_286  proc near

           ; if SP is pushed as it's original value, then it is a 286+
           push sp
           pop  ax
           cmp  ax,sp
           jne  short @f
           
           mov  si,offset Found286Str
           call display_string
           
           clc
           ret

@@:        mov  si,offset Not286Str
           call display_string
           
           stc
           ret
check_286  endp

Found286Str db  'Found 286...',13,10,0
Not286Str  db  'Did not find a 286!',13,10,0

.endif

.if (HIGHEST_CPU == 3)
; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine checks for the 386 processor
; On entry:
;       nothing
; On return:
;       carry set if not a 386
check_386  proc near

           pushf                   ; save original flags
           mov  ax,7000h           ; if bits 14:12 are still set
           push ax                 ;  after pushing them to the flags register,
           popf                    ;  then we have a 386+
           pushf                   ;
           pop  ax
           popf
           and  ax,7000h
           cmp  ax,7000h
           jne  short @f

           mov  si,offset Found386Str
           call display_string
           
           clc
           ret

@@:        mov  si,offset Not386Str
           call display_string
           
           stc
           ret
check_386  endp

Found386Str db  'Found 386...',13,10,0
Not386Str  db  'Did not find a 386!',13,10,0

.endif

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine resets registers for each instruction test
; On entry:
;       nothing
; On return:
;       nothing
reset_all  proc near

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ;  clear the registers
.if (HIGHEST_CPU == 3)
           xor  eax,eax
           xor  ebx,ebx
           xor  ecx,ecx
           xor  edx,edx
           xor  esi,esi
           xor  edi,edi
           xor  ebp,ebp
.else
           xor  ax,ax
           xor  bx,bx
           xor  cx,cx
           xor  dx,dx
           xor  si,si
           xor  di,di
           xor  bp,bp
.endif
           ret
reset_all  endp

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine sets an exception handler pointer
; On entry:
;       ax = handler (0 -> 7)
;       ds:bx -> address to handler
; On return:
;       nothing
set_handler proc near uses ax di es

           shl  ax,1
           shl  ax,1
           mov  di,ax
           xor  ax,ax
           mov  es,ax
           mov  es:[di+0],bx
           mov  es:[di+2],ds

           ret
set_handler endp

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine creates dummy exception handlers
;  they are nothing more than:
;    mov  ax,##bad code##
;    skip over last instruction
;    iret
;  so that our code can check the value of ax to see if it was actuall called.
;
; On entry:
;       nothing
; On return:
;       nothing
reset_handlers proc near uses ax bx
           
           mov  bx,offset exceptions
           xor  ax,ax
@@:        call set_handler
           add  bx,16
           inc  ax
           cmp  ax,8
           jb   short @b

           ret
reset_handlers endp


; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; 8 generic exception handlers
.align 16
exceptions:
.if (HIGHEST_CPU == 3)
          mov  eax,0BAD0h  ; divide by zero  #DE
.else
          mov  ax,0BAD0h
.endif
          mov  bp,sp
          add  [bp-0],cx   ; skip instruction?
          iret

          ; 4 bytes left (if 32-bit)

.align 16
.if (HIGHEST_CPU == 3)
          mov  eax,0BAD1h  ; single step  #DB
.else
          mov  ax,0BAD1h
.endif
          mov  bp,sp
          add  [bp-0],cx   ; skip instruction?
          iret

.align 16
.if (HIGHEST_CPU == 3)
          mov  eax,0BAD2h  ; nonmaskable
.else
          mov  ax,0BAD2h
.endif
          mov  bp,sp
          add  [bp-0],cx   ; skip instruction?
          iret

.align 16
.if (HIGHEST_CPU == 3)
          mov  eax,0BAD3h  ; break point    #BP
.else
          mov  ax,0BAD3h
.endif
          mov  bp,sp
          add  [bp-0],cx   ; skip instruction?
          iret

.align 16
.if (HIGHEST_CPU == 3)
          mov  eax,0BAD4h  ; overflow    #OF
.else
          mov  ax,0BAD4h
.endif
          mov  bp,sp
          add  [bp-0],cx   ; skip instruction?
          iret

.align 16
.if (HIGHEST_CPU == 3)
          mov  eax,0BAD5h  ; Bound fail   #BR
.else
          mov  ax,0BAD5h
.endif
          mov  bp,sp
          add  [bp-0],cx   ; skip instruction?
          iret

.align 16
.if (HIGHEST_CPU == 3)
          mov  eax,0BAD6h  ; invalid op    #UD
.else
          mov  ax,0BAD6h
.endif
          mov  bp,sp
          add  [bp-0],cx   ; skip instruction?
          iret

.align 16
.if (HIGHEST_CPU == 3)
          mov  eax,0BAD7h  ; extention not available    #NM
.else
          mov  ax,0BAD7h
.endif
          mov  bp,sp
          add  [bp-0],cx   ; skip instruction?
          iret

.end
