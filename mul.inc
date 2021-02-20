comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: mul.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the mul instruction                                            *
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
; This routine 'tests' the mul instruction
; On entry:
;       nothing
; On return:
;       nothing
test_mul   proc near

           mov  si,offset TestMulStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))

           mov  ax,1234h
           mov  bl,12h
           mul bl
           call std_out

           mov  ax,1234h
           mov  byte BYTE0,12h
           mul  byte BYTE0
           call std_out

           mov  dx,4321h
           mov  ax,1234h
           mov  bx,7623h
           mul  bx
           call std_out

           mov  dx,4321h
           mov  ax,1234h
           mov  word WORD0,7623h
           mul  word WORD0
           call std_out

           mov  bx,4321h
           mov  ax,1234h
           mul  bx
           call std_out

           mov  word WORD0,4321h
           mov  ax,1234h
           mul  word WORD0
           call std_out

.if (HIGHEST_CPU == 3)

           mov  edx,12345678h
           mov  eax,87654321h
           mov  ebx,22334455h
           mul  ebx
           call std_out

           mov  edx,12345678h
           mov  eax,87654321h
           mov  dword DWORD0,22334455h
           mul  dword DWORD0
           call std_out

           mov  ebx,4321h
           mov  eax,1234h
           mul  ebx
           call std_out

           mov  dword DWORD0,23234321h
           mov  eax,12348736h
           mul  dword DWORD0
           call std_out
.endif
           ret
test_mul   endp

TestMulStr db 'Test: Unsigned MUL',13,10,0

.end
