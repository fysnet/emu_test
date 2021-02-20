comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: ud2.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the ud2 instruction                                            *
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
; This routine 'tests' the ud2 instruction
; On entry:
;       nothing
; On return:
;       nothing
test_ud2   proc near

           mov  si,offset TestUd2Str
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; no flags modified

           mov  cx,2   ; the ud2 instruction is 2 bytes in size
           ud2
           xor  bp,bp           ; clear the bp register since the exception handler modifies it
           call std_out
           
           ret
test_ud2   endp

TestUd2Str db 'Test: UD2',13,10,0

.end
