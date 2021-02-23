comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: not.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the not instruction                                            *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 22 Feb 2021                                                *
*                                                                          *
*                                                                          *
***************************************************************************|

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine 'tests' the not instruction
; On entry:
;       nothing
; On return:
;       nothing
test_not   proc near

           mov  si,offset TestNotStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0xFFFF   ; all other flags are not affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)

           mov  al,0xFE
           not  al
           call std_out

           mov  al,0xFF
           not  al
           call std_out

           mov  al,0x00
           not  al
           call std_out

           mov  al,0x01
           not  al
           call std_out

           mov  al,0x7F
           not  al
           call std_out

           mov  al,0x80
           not  al
           call std_out


           mov  ax,0xFFFE
           not  ax
           call std_out

           mov  ax,0xFFFF
           not  ax
           call std_out

           mov  ax,0x0000
           not  ax
           call std_out

           mov  ax,0x0001
           not  ax
           call std_out

           mov  ax,0x7FFF
           not  ax
           call std_out

           mov  ax,0x8000
           not  ax
           call std_out


.if (HIGHEST_CPU == 3)
           mov  eax,0xFFFFFFFE
           not  eax
           call std_out

           mov  eax,0xFFFFFFFF
           not  eax
           call std_out

           mov  eax,0x00000000
           not  eax
           call std_out

           mov  eax,0x00000001
           not  eax
           call std_out

           mov  eax,0x7FFFFFFF
           not  eax
           call std_out

           mov  eax,0x80000000
           not  eax
           call std_out
.endif

           ret
test_not   endp

TestNotStr db 'Test: NOT',13,10,0

.end
