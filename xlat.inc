comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: xlat.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the xlat instruction                                           *
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
; This routine 'tests' the xlat instruction
; On entry:
;       nothing
; On return:
;       nothing
test_xlat  proc near

           mov  si,offset TestXlatStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; no flags affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)

           mov  bx,offset xbuffer0
           
           mov  al,0
           xlatb
           call std_out
           
           mov  al,10
           xlatb
           call std_out
           
           mov  al,25
           xlatb
           call std_out
           
           ; test the (redundant) ds:override
           mov  al,16
           xlat ds:[bx]
           call std_out
           
           ; test the es:override
           mov  al,13
           xlat es:[bx]
           call std_out
           
           ; test the ss:override
           mov  cx,ss              ; save the ss segment register
           mov  dx,ds              ;  (no need to worry about interrupts)
           mov  ss,dx              ; make ss = ds
           mov  al,21              ;
           xlat ss:[bx]            ;
           mov  ss,cx              ; restore the ss segment register (*before* we call std_out)
           call std_out
           
           ret
test_xlat  endp

TestXlatStr db 'Test: XLAT',13,10,0

xbuffer0   db  'ABCDEFGHIJKLMNOPQRSTUVWXYZ',0

.end
