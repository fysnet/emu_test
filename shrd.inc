comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: shrd.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the shrd instruction                                           *
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
; This routine 'tests' the shrd instruction
; On entry:
;       nothing
; On return:
;       nothing
test_shrd  proc near

           mov  si,offset TestShrdStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_AUXILIARY))

           mov  ax,1234h
           mov  bx,4321h
           shrd ax,bx,1
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_AUXILIARY | FLAGS_OVERFLOW))
           mov  ax,1234h
           mov  bx,4321h
           shrd bx,ax,6
           call std_out

           mov  cl,3
           mov  ax,7765h
           mov  bx,9834h
           shrd bx,ax,cl
           call std_out

           mov  dx,4367h
           mov  word WORD0,7A7Dh
           shrd WORD0,dx,3
           mov  ax,WORD0
           call std_out

           mov  cl,10
           mov  dx,4367h
           mov  word WORD0,7A7Dh
           shrd WORD0,dx,cl
           mov  ax,WORD0
           call std_out

           mov  eax,12345678h
           mov  ebx,87654321h
           shrd eax,ebx,9
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_AUXILIARY))
           mov  eax,12345678h
           mov  ebx,87654321h
           shrd ebx,eax,1
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_AUXILIARY | FLAGS_OVERFLOW))
           mov  cl,3
           mov  eax,7AA88765h
           mov  ebx,9B65C834h
           shrd ebx,eax,cl
           call std_out

           mov  edx,4367h
           mov  dword DWORD0,7A77761Dh
           shrd DWORD0,edx,7
           mov  eax,DWORD0
           call std_out

           mov  cl,12
           mov  edx,6FF34367h
           mov  dword DWORD0,7A33AA7Dh
           shrd DWORD0,edx,cl
           mov  eax,DWORD0
           call std_out

           ret
test_shrd  endp

TestShrdStr db 'Test: SHRD',13,10,0

.endif

.end
