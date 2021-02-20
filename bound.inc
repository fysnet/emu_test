comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: bound.inc                                                          *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the bound instruction                                          *
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
; This routine 'tests' the bound instruction
; On entry:
;       nothing
; On return:
;       nothing
test_bound proc near

           mov  si,offset TestBoundStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; flags are not affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; 16/16<->16 version

           ; should not fire an exception
           mov  eax,00200010h   ; 16 <--> 32
           mov  DWORD0,eax
           mov  eax,24
           mov  cx,(b1-b0)      ; the bound instruction below is x bytes
b0:        bound ax,DWORD0
b1:        xor  bp,bp           ; clear the bp register since the exception modifies it
           xor  cx,cx           ; clear the cx register since OPTION 0 and OPTION 1 will have different sizes for DWORD0
           call std_out         ; ax should be 24

           ; should fire an exception
           mov  eax,00200010h   ; 16 <--> 32
           mov  DWORD0,eax
           mov  eax,33
           mov  cx,(b3-b2)      ; the bound instruction below is x bytes
b2:        bound ax,DWORD0
b3:        xor  bp,bp           ; clear the bp register since the exception modifies it
           xor  cx,cx           ; clear the cx register since OPTION 0 and OPTION 1 will have different sizes for DWORD0
           call std_out         ; ax should be 5

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; 32/32<->32 version

           ; should not fire an exception
           mov  eax,00000100h   ; 256 <--> 512
           mov  DWORD0,eax
           mov  eax,00000200h   ; 256 <--> 512
           mov  DWORD1,eax
           mov  eax,300
           mov  cx,(b5-b4)      ; the bound instruction below is x bytes
b4:        bound eax,DWORD0
b5:        xor  bp,bp           ; clear the bp register since the exception modifies it
           xor  cx,cx           ; clear the cx register since OPTION 0 and OPTION 1 will have different sizes for DWORD0
           call std_out         ; ax should be 300

           ; should fire an exception
           mov  eax,00000100h   ; 256 <--> 512
           mov  DWORD0,eax
           mov  eax,00000200h   ; 256 <--> 512
           mov  DWORD1,eax
           mov  eax,1024
           mov  cx,(b7-b6)      ; the bound instruction below is x bytes
b6:        bound eax,DWORD0
b7:        xor  bp,bp           ; clear the bp register since the exception modifies it
           xor  cx,cx           ; clear the cx register since OPTION 0 and OPTION 1 will have different sizes for DWORD0
           call std_out         ; ax should be 5

           ret
test_bound endp

TestBoundStr db 'Test: BOUND',13,10,0

.endif

.end
