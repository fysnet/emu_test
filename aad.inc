comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: aad.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the aad instruction                                            *
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
; This routine 'tests' the aad instruction
; On entry:
;       nothing
; On return:
;       nothing
test_aad   proc near

           mov  si,offset TestAadStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_OVERFLOW | FLAGS_AUXILIARY | FLAGS_CARRY))

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  ax,0000h
           aad
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  ax,0123h
           aad
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  ax,00FFh
           aad
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  ax,0FF00h
           aad
           call std_out

           ret
test_aad   endp

TestAadStr db 'Test: AAD',13,10,0

.end
