comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: lahf.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the lahf/sahf instructions                                     *
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
; This routine 'tests' the lahf/sahf instructions
; On entry:
;       nothing
; On return:
;       nothing
test_lahf  proc near

           mov  si,offset TestLahfStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0xFFFF   ; all other flags are not affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)

           ; the lahf should clear bits 3 & 5 before storing to ah, while setting bit 1 whether it is set in the flags register or not
           lahf           
           call std_out

           ; let's set the carry flag in AH first (as a test)
           clc
           or  ah,1
           sahf
           call std_out

           ret
test_lahf  endp

TestLahfStr db 'Test: LAHF/SAHF',13,10,0

.end
