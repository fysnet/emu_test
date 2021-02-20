comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: div.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the div instruction                                            *
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
; This routine 'tests' the div instruction
; On entry:
;       nothing
; On return:
;       nothing
test_div   proc near

           mov  si,offset TestDivStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; flags are undefined

           mov  cx,2    ; the div instruction below is 2 bytes

           ; this will cause an exception ( (1234h / 12h) > 0xFF )
           mov  ax,1234h
           mov  bl,12h
           div  bl
           xor  bp,bp           ; clear the bp register since the exception handler modifies it
           call std_out

           ; this will not cause an exception ( (1234h / 20h) < 0xFF )
           mov  ax,1234h
           mov  bl,20h
           div  bl
           call std_out

           ; this will not cause an exception ( (56781234h / 6543h) < 0xFFFF )
           mov  dx,5678h
           mov  ax,1234h
           mov  bx,6543h
           div  bx
           call std_out

           ; this will cause an exception ( (56781234h / 3456h) > 0xFFFF )
           mov  dx,5678h
           mov  ax,1234h
           mov  bx,3456h
           div  bx
           xor  bp,bp           ; clear the bp register since the exception handler modifies it
           call std_out

           ; this will cause an exception (56781234h / zero)
           mov  dx,5678h
           mov  ax,1234h
           mov  bx,0000h
           div  bx
           xor  bp,bp           ; clear the bp register since the exception handler modifies it
           call std_out

.if (HIGHEST_CPU == 3)

           mov  cx,3    ; the div instruction below is 3 bytes

           ; this will not cause an exception ( (1234567887654321h / 25252525h) < 0xFFFFFFFF )
           mov  edx,12345678h
           mov  eax,87654321h
           mov  ebx,25252525h
           div  ebx
           call std_out

           ; this will cause an exception ( (1234567887654321h / 12121212h) > 0xFFFFFFFF )
           mov  edx,12345678h
           mov  eax,87654321h
           mov  ebx,12121212h
           div  ebx
           xor  bp,bp           ; clear the bp register since the exception handler modifies it
           call std_out

           ; this will cause an exception (1234567887654321h / zero)
           mov  edx,12345678h
           mov  eax,87654321h
           mov  ebx,0h
           div  ebx
           xor  bp,bp           ; clear the bp register since the exception handler modifies it
           call std_out

.endif
           ret
test_div   endp

TestDivStr db 'Test: Unsigned DIV',13,10,0

.end
