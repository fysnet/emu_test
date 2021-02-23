comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: btr.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the btr instruction                                            *
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
; This routine 'tests' the btr instruction
; On entry:
;       nothing
; On return:
;       nothing
test_btr   proc near

           mov  si,offset TestBtrStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_OVERFLOW | FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)

           mov  ax,0A5A5h
           btr  ax,ax
           call std_out

           mov  word WORD0,1
           mov  ax,10
           btr  WORD0,ax
           mov  bx,WORD0   ; display the WORD0 value too, to make sure it is reset
           call std_out

           mov  ax,0A5A5h
           btr  ax,13
           call std_out

           mov  word WORD0,1
           btr  word WORD0,13
           mov  bx,WORD0   ; display the WORD0 value too, to make sure it is reset
           call std_out

           
           mov  eax,0A5A5A5A5h
           mov  ebx,25
           btr  eax,ebx
           call std_out

           mov  dword DWORD0,1
           mov  ecx,23
           btr  DWORD0,ecx
           mov  ebx,DWORD0   ; display the DWORD0 value too, to make sure it is reset
           call std_out

           mov  eax,0A5A5A5A5h
           btr  eax,15
           call std_out

           ret
test_btr   endp

TestBtrStr db 'Test: BTR',13,10,0

.endif

.end
