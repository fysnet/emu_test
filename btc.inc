comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: btc.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the btc instruction                                            *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 19 Feb 2021                                                *
*                                                                          *
*                                                                          *
***************************************************************************|

.if (HIGHEST_CPU == 3)

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine 'tests' the btc instruction
; On entry:
;       nothing
; On return:
;       nothing
test_btc   proc near

           mov  si,offset TestBtcStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_OVERFLOW | FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)

           mov  ax,0A5A5h
           btc  ax,ax
           call std_out

           mov  word WORD0,1
           mov  ax,10
           btc  WORD0,ax
           mov  bx,WORD0   ; display the WORD0 value too, to make sure it is complimented
           call std_out

           mov  ax,0A5A5h
           btc  ax,13
           call std_out

           mov  word WORD0,1
           btc  word WORD0,13
           mov  bx,WORD0   ; display the WORD0 value too, to make sure it is complimented
           call std_out

           
           mov  eax,0A5A5A5A5h
           mov  ebx,25
           btc  eax,ebx
           call std_out

           mov  dword DWORD0,1
           mov  ecx,23
           btc  DWORD0,ecx
           mov  ebx,DWORD0   ; display the DWORD0 value too, to make sure it is complimented
           call std_out

           mov  eax,0A5A5A5A5h
           btc  eax,15
           call std_out

           ret
test_btc   endp

TestBtcStr db 'Test: BTC',13,10,0

.endif

.end
