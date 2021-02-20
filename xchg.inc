comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: xchg.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the xchg instruction                                           *
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
; This routine 'tests' the xchg instruction
; On entry:
;       nothing
; On return:
;       nothing
test_xchg  proc near

           mov  si,offset TestXchgStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; no flags affected

           mov  byte BYTE0,12h
           mov  byte BYTE1,34h
           mov  word WORD0,7754h
           mov  word WORD1,9283h

           mov  ax,1234h
           mov  bx,4321h          
           
           xchg al,ah
           xchg bl,bh
           xchg bl,ah
           xchg al,bh
           call std_out

           xchg al,BYTE0
           xchg bl,BYTE1
           call std_out
           
           xchg ax,bx
           call std_out

           xchg bx,ax
           call std_out

           xchg ax,ax
           call std_out
           
           xchg ax,WORD0
           xchg bx,WORD1
           call std_out

.if (HIGHEST_CPU == 3)

           mov  eax,12345678h
           mov  ebx,87654321h          
           mov  dword DWORD0,77938454h
           mov  dword DWORD1,9AB63283h

           xchg eax,ebx
           call std_out

           xchg ebx,eax
           call std_out

           xchg eax,eax
           call std_out

           xchg eax,DWORD0
           xchg ebx,DWORD1
           call std_out

.endif
           ret
test_xchg  endp

TestXchgStr db 'Test: XCHG',13,10,0

.end
