comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: imul.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the imul instruction                                           *
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
; This routine 'tests' the imul instruction
; On entry:
;       nothing
; On return:
;       nothing
test_imul  proc near

           mov  si,offset TestImulStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))

           mov  ax,1234h
           mov  bl,12h
           imul bl
           call std_out

           mov  ax,1234h
           mov  byte BYTE0,12h
           imul byte BYTE0
           call std_out

           mov  dx,4321h
           mov  ax,1234h
           mov  bx,7623h
           imul bx
           call std_out

           mov  dx,4321h
           mov  ax,1234h
           mov  word WORD0,7623h
           imul word WORD0
           call std_out

.if (HIGHEST_CPU >= 2)   ; TODO: could have been the 186
           mov  bx,4321h
           imul ax,bx,8
           call std_out

           mov  word WORD0,4321h
           imul ax,WORD0,5
           call std_out

           mov  ax,3721h
           imul ax,74
           call std_out

           mov  ax,5711h
           imul ax,1637h
           call std_out
.endif

.if (HIGHEST_CPU >= 3)
           mov  bx,4321h
           mov  ax,1234h
           imul ax,bx
           call std_out

           mov  word WORD0,4321h
           mov  ax,1234h
           imul ax,WORD0
           call std_out
.endif

.if (HIGHEST_CPU == 3)

           mov  edx,12345678h
           mov  eax,87654321h
           mov  ebx,22334455h
           imul ebx
           call std_out

           mov  edx,12345678h
           mov  eax,87654321h
           mov  dword DWORD0,22334455h
           imul dword DWORD0
           call std_out

           mov  ebx,4321h
           mov  eax,1234h
           imul eax,ebx
           call std_out

           mov  dword DWORD0,23234321h
           mov  eax,12348736h
           imul eax,DWORD0
           call std_out

           mov  ebx,43421218h
           imul eax,ebx,8
           call std_out

           mov  dword DWORD0,41312216h
           imul eax,DWORD0,19
           call std_out

           mov  eax,13721231h
           imul eax,93
           call std_out

           mov  eax,52835711h
           imul eax,11133637h
           call std_out

.endif
           ret
test_imul  endp

TestImulStr db 'Test: Signed IMUL',13,10,0

.end
