comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: cmps.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the cmpsb/w/d instructions                                     *
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
; This routine 'tests' the cmpsb/w/d instructions
; On entry:
;       nothing
; On return:
;       nothing
test_cmps  proc near

           mov  si,offset TestCmpsStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0xFFFF

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  si,offset cbuffer0
           mov  di,offset cbuffer1
           mov  cx,26
           repe
             cmpsb
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  si,offset cbuffer2
           mov  di,offset cbuffer3
           mov  cx,26
           repe 
             cmpsw
           call std_out

.if (HIGHEST_CPU == 3)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  si,offset cbuffer4
           mov  di,offset cbuffer5
           mov  cx,26
           repe 
             cmpsd
           call std_out
.endif


           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  si,offset cbuffer0
           add  si,1
           mov  di,offset cbuffer1
           mov  cx,26
           repne
             cmpsb
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  si,offset cbuffer2
           add  si,2
           mov  di,offset cbuffer3
           mov  cx,26
           repne 
             cmpsw
           call std_out

.if (HIGHEST_CPU == 3)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  si,offset cbuffer4
           add  si,4
           mov  di,offset cbuffer5
           mov  cx,26
           repne 
             cmpsd
           call std_out
.endif

           ret
test_cmps  endp

TestCmpsStr db 'Test: CMPSB/W/D',13,10,0

cbuffer0    db  'ABCDEFGHIJKLMNOPQRSTUVZZZ'
cbuffer1    db  'ABCDE_GHIJKLMNOPQRSTUVZZZ'

cbuffer2    dw  'ABCDEFGHIJKLMNOPQRSTUVZZZ'
cbuffer3    dw  'ABCDEFGHI_KLMNOPQRSTUVZZZ'

cbuffer4    dd  'ABCDEFGHIJKLMNOPQ_STUVZZZ'
cbuffer5    dd  'ABCDEFGHIJKLMNOPQRSTUVZZZ'

.end
