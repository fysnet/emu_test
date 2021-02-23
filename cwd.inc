comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: cwd.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the cwd instruction                                            *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 22 Feb 2021                                                *
*                                                                          *
*                                                                          *
***************************************************************************|

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine 'tests' the cwd instruction
; On entry:
;       nothing
; On return:
;       nothing
test_cwd   proc near

           mov  si,offset TestCwdStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; flags are not affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)

           mov  dx,0EEEEh
           mov  ax,0000h
           cwd
           call std_out

           mov  dx,0EEEEh
           mov  ax,0001h
           cwd
           call std_out

           mov  dx,0EEEEh
           mov  ax,8000h
           cwd
           call std_out

           mov  dx,0EEEEh
           mov  ax,0FFFFh
           cwd
           call std_out

.if (HIGHEST_CPU == 3)
           mov  edx,0EEEEEEEEh
           mov  eax,00000000h
           cdq
           call std_out

           mov  edx,0EEEEEEEEh
           mov  eax,000000001h
           cdq
           call std_out

           mov  edx,0EEEEEEEEh
           mov  eax,80000000h
           cdq
           call std_out

           mov  edx,0EEEEEEEEh
           mov  eax,0FFFFFFFFh
           cdq
           call std_out
.endif

           ret
test_cwd   endp

TestCwdStr db 'Test: CWD/CDQ',13,10,0

.end
