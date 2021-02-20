comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: lods.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the lodsb/w/d instructions                                     *
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
; This routine 'tests' the lodsb/w/d instructions
; On entry:
;       nothing
; On return:
;       nothing
test_lods  proc near

           mov  si,offset TestLodsStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000

           mov  si,offset lbuffer0
           mov  cx,14
           rep
             lodsb
           call std_out
           
           mov  si,offset lbuffer1
           mov  cx,3
           rep
             lodsw
           call std_out

.if (HIGHEST_CPU == 3)
           mov  si,offset lbuffer2
           mov  cx,22
           rep
             lodsd
           call std_out
.endif
           ret
test_lods  endp

TestLodsStr db 'Test: LODSB/W/D',13,10,0

lbuffer0   db 'ABCDEFGHIJKLMNOPQRSTUVWXYZ',0
lbuffer1   dw 'ABCDEFGHIJKLMNOPQRSTUVWXYZ',0
lbuffer2   dd 'ABCDEFGHIJKLMNOPQRSTUVWXYZ',0

.end
