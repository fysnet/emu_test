comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: movxx.inc                                                          *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the movsx/movzx instructions                                   *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 22 Feb 2021                                                *
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

.if (HIGHEST_CPU >= 3)

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine 'tests' the movsx/movzx instructions
; On entry:
;       nothing
; On return:
;       nothing
test_movxx proc near

           mov  si,offset TestMovxxStr
           call display_string
           
           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; no flags are affected

           mov   byte BYTE0,7Fh
           mov   byte BYTE1,80h
           mov   word WORD0,7FFFh
           mov   word WORD1,8000h

           movsx ax,byte BYTE0
           movsx bx,byte BYTE1
           movzx cx,byte BYTE0
           movzx dx,byte BYTE1
           call std_out
           
           mov  al,7Fh
           movsx ax,al
           mov  bl,80h
           movsx bx,bl
           mov  cl,7Fh
           movsx dx,cl
           call std_out

           mov  al,7Fh
           movzx ax,al
           mov  bl,80h
           movzx bx,bl
           mov  cl,7Fh
           movzx dx,cl
           call std_out

           mov  ax,7FFFh
           movsx ebx,ax
           mov  cx,8000h
           movsx edx,cx
           call std_out

           movsx eax,byte BYTE0
           movsx ebx,byte BYTE1
           movzx ecx,byte BYTE0
           movzx edx,byte BYTE1
           call std_out

           movsx eax,word WORD0
           movsx ebx,word WORD1
           movzx ecx,word WORD0
           movzx edx,word WORD1
           call std_out

           mov  ax,7FFFh
           movzx ebx,ax
           mov  cx,8000h
           movzx edx,cx
           call std_out

           mov  al,7Fh
           movsx eax,al
           mov  bl,80h
           movsx ebx,bl
           mov  cl,7Fh
           movsx edx,cl
           call std_out

           mov  al,7Fh
           movzx eax,al
           mov  bl,80h
           movzx ebx,bl
           mov  cl,7Fh
           movzx edx,cl
           call std_out

           ret
test_movxx endp

TestMovxxStr db 'Test: MOVSX/MOVZX',13,10,0

.endif

.end
