comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: aaa.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the aaa instruction                                            *
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
; This routine 'tests' the aaa instruction
; On entry:
;       nothing
; On return:
;       nothing
test_aaa   proc near

           mov  si,offset TestAaaStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_OVERFLOW | FLAGS_SIGN | FLAGS_ZERO | FLAGS_PARITY))

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  al,0
           aaa
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  al,9
           aaa
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  al,10
           aaa
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  al,15
           aaa
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  al,16   ; should be the same as the zero above
           aaa
           call std_out

           ret
test_aaa   endp

TestAaaStr db 'Test: AAA',13,10,0

.end
