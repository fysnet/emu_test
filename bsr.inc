comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: bsr.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the bsr instruction                                            *
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
; This routine 'tests' the bsr instruction
; On entry:
;       nothing
; On return:
;       nothing
test_bsr   proc near

           mov  si,offset TestBsrStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_CARRY | FLAGS_OVERFLOW | FLAGS_SIGN | FLAGS_AUXILIARY | FLAGS_PARITY))

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)

           mov  ax,0A5A5h
           bsr  ax,ax
           call std_out

           mov  word WORD0,1
           bsr  ax,WORD0
           call std_out

           mov  ax,0
           bsr  ax,ax
           call std_out

           mov  word WORD0,8000h
           bsr  ax,WORD0
           call std_out


           mov  eax,0A5A5A5A5h
           bsr  eax,eax
           call std_out

           mov  word DWORD0,1
           bsr  eax,DWORD0
           call std_out

           mov  eax,0
           bsr  eax,eax
           call std_out

           mov  dword DWORD0,80000000h
           bsr  ax,DWORD0
           call std_out


           ret
test_bsr   endp

TestBsrStr db 'Test: BSR',13,10,0

.endif

.end
