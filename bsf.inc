comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: bsf.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the bsf instruction                                            *
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
; This routine 'tests' the bsf instruction
; On entry:
;       nothing
; On return:
;       nothing
test_bsf   proc near

           mov  si,offset TestBsfStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_CARRY | FLAGS_OVERFLOW | FLAGS_SIGN | FLAGS_AUXILIARY | FLAGS_PARITY))

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)

           mov  ax,0A5A5h
           bsf  ax,ax
           call std_out

           mov  word WORD0,1
           bsf  ax,WORD0
           call std_out

           mov  ax,0
           bsf  ax,ax
           call std_out

           mov  word WORD0,8000h
           bsf  ax,WORD0
           call std_out


           mov  eax,0A5A5A5A5h
           bsf  eax,eax
           call std_out

           mov  word DWORD0,1
           bsf  eax,DWORD0
           call std_out

           mov  eax,0
           bsf  eax,eax
           call std_out

           mov  dword DWORD0,80000000h
           bsf  ax,DWORD0
           call std_out


           ret
test_bsf   endp

TestBsfStr db 'Test: BSF',13,10,0

.endif

.end
