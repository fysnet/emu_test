comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: clc.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the clc/stc/cmc instructions                                   *
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
; This routine 'tests' the clc/stc/cmc instructions
; On entry:
;       nothing
; On return:
;       nothing
test_clc   proc near

           mov  si,offset TestClcStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_AUXILIARY))  ; shouldn't change any flags, but don't display the auxilary flag due to the XOR not clearing it

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           clc
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           cmc
           call std_out

           ret
test_clc   endp

TestClcStr db 'Test: CLC/STC/CMC',13,10,0

.end
