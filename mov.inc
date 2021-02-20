comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: mov.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the mov instruction                                            *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 19 Feb 2021                                                *
*                                                                          *
* Note:  The below assumes that the addresses being read from              *
*        will always be the same between tests, and emulators.             *
*        since DS: and ES: points to 0xF000, which was loaded from         *
*        our code, it should always be the same across tests and           *
*        more importantly, emulators, as long as the range is within       *
*        F000:0000 -> F000:0010.  This is the only 16 bytes we can         *
*        assume that will be the same across all tests.                    *
*                                                                          *
*        When adding reads, be sure that you do not set a register to      *
*        a value outside the normal range, in one instruction, then use    *
*        that same register in another address, that might case a fault.   *
*        For example:                                                      *
*           mov  eax,[ebx+100]  ; reads a dword of 0x87654321              *
*           mov  ebx,[eax]      ; will now cause a fault, trying to read   *
*                               ;  from address [0x87654321]               *
*                                                                          *
***************************************************************************|

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine 'tests' the mov instruction
; On entry:
;       nothing
; On return:
;       nothing
test_mov   proc near

           mov  si,offset TestMovStr
           call display_string
           
           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; no flags are affected
           
           mov  al,81h
           mov  bl,72h
           mov  cl,63h
           mov  dl,54h
           mov  ah,45h
           mov  bh,36h
           mov  ch,27h
           mov  dh,18h
           call std_out
           
           mov  ax,9AA9h
           mov  bx,0BC12h
           mov  cx,0FE87h
           mov  dx,1234h
           mov  si,876Ah
           mov  di,3453h
           mov  bp,0BB88h
           call std_out
           
           mov  al,bl
           mov  bl,cl
           mov  cl,dl
           mov  dl,ah
           mov  ah,bh
           mov  bh,ch
           mov  ch,dh
           mov  dh,al
           call std_out
           
           mov  ax,bx
           mov  bx,cx
           mov  cx,dx
           mov  dx,si
           mov  si,di
           mov  di,bp
           mov  bp,ax
           call std_out
           
           ; must set the bx, bp, si, and di registers to something that
           ;  won't cause a fault, when used below
           mov  si,10
           mov  di,20
           mov  bx,0
           mov  bp,10
           
           mov  al,BYTE0
           mov  dl,BYTE1
           mov  cl,[bx]
           mov  dl,es:[si]
           call std_out
           
           mov  ax,WORD0
           mov  dx,WORD1
           mov  cx,[bx]
           mov  dx,[si]
           call std_out
           
           mov  ax,[bx+10]
           mov  dx,es:[si-4]
           mov  cx,[bx+si+4]
           mov  dx,[bp+di-5]
           call std_out
           
.if (HIGHEST_CPU == 3)

           mov  eax,23459AA9h
           mov  ebx,7443BC12h
           mov  ecx,937DFE87h
           mov  edx,0FFFF1234h
           mov  esi,2235876Ah
           mov  edi,88AA3453h
           mov  ebp,99AABB88h
           call std_out

           ; must set the ebx, ebp, esi, and edi registers to something that
           ;  won't cause a fault, when used below
           mov  esi,5              ; must be at least than 5 (5 used below)
           mov  edi,10             ; must be at least than 5 (5 used below)
           mov  ebx,4
           mov  ebp,10

           mov  eax,DWORD0
           mov  edx,DWORD1
           mov  ecx,[bx]
           mov  edx,es:[si]
           call std_out

           mov  eax,DWORD0
           mov  edx,DWORD1
           mov  ecx,[ebx]
           mov  edx,[esi]
           mov  ecx,[ebx+esi]
           mov  edx,[ebp+edi]      ; reads from SS:
           call std_out

           mov  eax,[ebx+4]
           mov  edx,es:[esi-5]
           mov  ecx,[ebx+esi+1]
           mov  edx,[ebp+edi-5]   ; reads from SS:
           call std_out

           ; must set the eax and edx registers to something that
           ;  won't cause a fault, when used below
           mov  eax,10
           mov  edx,20

           mov  ecx,[eax+10]
           mov  ecx,[edx-10]
           mov  eax,es:[eax*4]
           mov  eax,[ebp+edi*2]    ; reads from SS:
           mov  edx,[esp]          ; reads from SS:
           call std_out

.endif
           ret
test_mov   endp

TestMovStr db 'Test: MOV',13,10,0

.end
