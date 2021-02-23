comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: neg.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the neg instruction                                            *
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
; This routine 'tests' the neg instruction
; On entry:
;       nothing
; On return:
;       nothing
test_neg   proc near

           mov  si,offset TestNegStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0xFFFF   ; all other flags are not affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)

           mov  al,0xFE
           neg  al
           call std_out

           mov  al,0xFF
           neg  al
           call std_out

           mov  al,0x00
           neg  al
           call std_out

           mov  al,0x01
           neg  al
           call std_out

           mov  al,0x7F
           neg  al
           call std_out

           mov  al,0x80
           neg  al
           call std_out


           mov  ax,0xFFFE
           neg  ax
           call std_out

           mov  ax,0xFFFF
           neg  ax
           call std_out

           mov  ax,0x0000
           neg  ax
           call std_out

           mov  ax,0x0001
           neg  ax
           call std_out

           mov  ax,0x7FFF
           neg  ax
           call std_out

           mov  ax,0x8000
           neg  ax
           call std_out


.if (HIGHEST_CPU == 3)
           mov  eax,0xFFFFFFFE
           neg  eax
           call std_out

           mov  eax,0xFFFFFFFF
           neg  eax
           call std_out

           mov  eax,0x00000000
           neg  eax
           call std_out

           mov  eax,0x00000001
           neg  eax
           call std_out

           mov  eax,0x7FFFFFFF
           neg  eax
           call std_out

           mov  eax,0x80000000
           neg  eax
           call std_out
.endif

           ret
test_neg   endp

TestNegStr db 'Test: NEG',13,10,0

.end
