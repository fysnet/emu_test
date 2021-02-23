comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: bt.inc                                                             *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the bt instruction                                             *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 22 Feb 2021                                                *
*                                                                          *
*                                                                          *
***************************************************************************|

.if (HIGHEST_CPU == 3)

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine 'tests' the bt instruction
; On entry:
;       nothing
; On return:
;       nothing
test_bt    proc near

           mov  si,offset TestBtStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_OVERFLOW | FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)

           mov  ax,0A5A5h
           bt   ax,ax
           call std_out

           mov  word WORD0,1
           mov  ax,10
           bt   WORD0,ax
           call std_out

           mov  ax,0A5A5h
           bt   ax,13
           call std_out

           mov  word WORD0,1
           bt   word WORD0,13
           call std_out

           
           mov  eax,0A5A5A5A5h
           mov  ebx,25
           bt   eax,ebx
           call std_out

           mov  dword DWORD0,1
           mov  ecx,23
           bt   DWORD0,ecx
           call std_out

           mov  eax,0A5A5A5A5h
           bt   eax,15
           call std_out

           ret
test_bt    endp

TestBtStr db 'Test: BT',13,10,0

.endif

.end
