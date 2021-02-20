comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: shld.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the shld instruction                                           *
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
; This routine 'tests' the shld instruction
; On entry:
;       nothing
; On return:
;       nothing
test_shld  proc near

           mov  si,offset TestShldStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,(~(FLAGS_AUXILIARY | FLAGS_OVERFLOW))

           mov  ax,1234h
           mov  bx,4321h
           shld ax,bx,5
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_AUXILIARY))
           mov  ax,1234h
           mov  bx,4321h
           shld bx,ax,1
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_AUXILIARY | FLAGS_OVERFLOW))
           mov  cl,3
           mov  ax,7765h
           mov  bx,9834h
           shld bx,ax,cl
           call std_out

           mov  dx,4367h
           mov  word WORD0,7A7Dh
           shld WORD0,dx,3
           mov  ax,WORD0
           call std_out

           mov  cl,10
           mov  dx,4367h
           mov  word WORD0,7A7Dh
           shld WORD0,dx,cl
           mov  ax,WORD0
           call std_out

           mov  eax,12345678h
           mov  ebx,87654321h
           shld eax,ebx,9
           call std_out

           mov  eax,12345678h
           mov  ebx,87654321h
           shld ebx,eax,15
           call std_out

           mov  cl,3
           mov  eax,7AA88765h
           mov  ebx,9B65C834h
           shld ebx,eax,cl
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_AUXILIARY))
           mov  edx,4367h
           mov  dword DWORD0,7A77761Dh
           shld DWORD0,edx,1
           mov  eax,DWORD0
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_AUXILIARY | FLAGS_OVERFLOW))
           mov  cl,12
           mov  edx,6FF34367h
           mov  dword DWORD0,7A33AA7Dh
           shld DWORD0,edx,cl
           mov  eax,DWORD0
           call std_out

           ret
test_shld  endp

TestShldStr db 'Test: SHLD',13,10,0

.endif

.end
