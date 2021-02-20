comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: loopcc.inc                                                         *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the loopcc instructions                                        *
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
; This routine 'tests' the loopcc instructions
; On entry:
;       nothing
; On return:
;       nothing
test_loopcc proc near

           mov  si,offset TestLoopccStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; no flags are affected

           xor  ax,ax      ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)

           ; unfortunetly, if the emulation is not correct, this
           ;  test may loop indefinately
           mov  cx,10      ; so we can test the jcxz instruction
@@:        loop @b         ; will cx == 0 ?
           call std_out

           xor  ax,ax      ; set the zero flag
           mov  cx,10
@@:        loopz @b        ; will cx == 0 ?
           call std_out

           xor  ax,ax      ; clear the zero flag
           sub  ax,1       ;  ' ' ' 
           mov  cx,10
@@:        loopnz @b        ; will cx == 0 ?
           call std_out

.if (HIGHEST_CPU == 3)
           ; ecx should still have bit 16 set after the following
           mov  ecx,00010001h
@@:        loop @b        
           call std_out
           
           ; ecx should be clear after the following
           mov  ecx,00010001h
@@:        .adsize 
             loop @b
           call std_out
.endif
           ret
test_loopcc endp

TestLoopccStr db 'Test: Loopcc',13,10,0

.end
