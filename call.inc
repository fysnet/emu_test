comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: call.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the call instruction                                           *
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
; This routine 'tests' the call instruction
; On entry:
;       nothing
; On return:
;       nothing
test_call  proc near

           mov  si,offset TestCallStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; flags are not affected
           
           ; give ax a value so that we print it below making sure
           ;  that we returned to the correct place
           mov  ax,1234h
           
           mov  bx,sp
           call @f
@@:        mov  cx,sp
           call std_out
           add  sp,2          ; clean up the stack
           
           mov  bx,sp
           mov  dx,offset @f
           call dx
@@:        mov  cx,sp
           call std_out
           add  sp,2          ; clean up the stack
           


           
.if (HIGHEST_CPU == 3)

           ; give eax a value so that we print it below making sure
           ;  that we returned to the correct place
;           mov  eax,12345678h



.endif

           ret
test_call  endp

TestCallStr db 'Test: CALL',13,10,0

.end
