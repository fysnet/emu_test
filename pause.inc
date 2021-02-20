comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: pause.inc                                                          *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the pause instruction                                          *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 19 Feb 2021                                                *
*                                                                          *
*                                                                          *
***************************************************************************|

.if (HIGHEST_CPU >= 3)

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine 'tests' the pause instruction
;  Does nothing more than execute the instruction (to test if your emulator supports this instruction)
; On entry:
;       nothing
; On return:
;       nothing
test_pause proc near

           mov  si,offset TestPauseStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; no flags are not affected
           
           pause
           call std_out

           ret
test_pause endp

TestPauseStr db 'Test: PAUSE',13,10,0

.endif

.end
