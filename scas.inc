comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: scas.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the scasb/w/d instructions                                     *
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
; This routine 'tests' the scasb/w/d instructions
; On entry:
;       nothing
; On return:
;       nothing
test_scas  proc near

           mov  si,offset TestScasStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0xFFFF

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  al,'A'
           mov  di,offset sbuffer0
           mov  cx,26
           repe
             scasb
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ax,'A'
           mov  di,offset sbuffer1
           mov  cx,26
           repe 
             scasw
           call std_out

.if (HIGHEST_CPU == 3)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  eax,'A'
           mov  di,offset sbuffer2
           mov  cx,26
           repe 
             scasd
           call std_out
.endif


           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  al,'Q'
           mov  di,offset sbuffer3
           mov  cx,26
           repne
             scasb
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ax,'J'
           mov  di,offset sbuffer4
           mov  cx,26
           repne 
             scasw
           call std_out

.if (HIGHEST_CPU == 3)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  eax,'Y'
           mov  di,offset sbuffer5
           mov  cx,26
           repne 
             scasd
           call std_out
.endif

           ret
test_scas  endp

TestScasStr db 'Test: SCASB/W/D',13,10,0

sbuffer0   db 'AAAAAAAAAAAAAAABCDEFGHIJKL',0
sbuffer1   dw 'AAAAAAAAAAABCDEFGHIJKLMNOP',0
sbuffer2   dd 'AAAAAAAAAAAAAAAAAAAABCDEFG',0

sbuffer3   db 'ABCDEFGHIJKLMNOPQRSTUVWXYZ',0
sbuffer4   dw 'ABCDEFGHIJKLMNOPQRSTUVWXYZ',0
sbuffer5   dd 'ABCDEFGHIJKLMNOPQRSTUVWXYZ',0

.end
