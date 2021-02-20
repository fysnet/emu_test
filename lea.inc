comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: lea.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the lea instruction                                            *
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
; This routine 'tests' the lea instruction
; On entry:
;       nothing
; On return:
;       nothing
test_lea   proc near

           mov  si,offset TestLeaStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; no flags affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           mov  bp,1234h
           mov  di,4321h

           lea  bx,WORD0
           call std_out

           lea  bx,DWORD0
           call std_out

           lea  si,[bp+0]
           call std_out

           lea  bx,[bp+di]
           call std_out

           lea  ax,[bx+di+5]
           call std_out

.if (HIGHEST_CPU == 3)

           mov  ebp,12345678h
           mov  edi,87654321h

           lea  ebx,WORD0
           call std_out

           lea  ebx,DWORD0
           call std_out

           lea  esi,[ebp+1]
           call std_out

           lea  ebx,[ebp+edi]
           call std_out

           lea  eax,[ebx+edi+5]
           call std_out

.endif

           ret
test_lea   endp

TestLeaStr db 'Test: LEA',13,10,0

.end
