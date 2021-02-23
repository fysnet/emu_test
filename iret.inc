comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: iret.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the iret instruction                                           *
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
; This routine 'tests' the iret instruction
; On entry:
;       nothing
; On return:
;       nothing
test_iret  proc near

           mov  si,offset TestIretStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0xFFFF   ; flags are not affected, but we need to still print them to check the INT flag
           
           ; give ax a value so that we print it below making sure
           ;  that we returned to the correct place
           mov  ax,1234h
           
           pushf
           push cs
           push offset @f
           iret
@@:        call std_out


.if (HIGHEST_CPU == 3)

           ; give eax a value so that we print it below making sure
           ;  that we returned to the correct place
           mov  eax,12345678h

           pushfd
           push bx   ; bx = 0 (push it so the push below is a 32-bit push. (we're still in real mode here))
           push cs
           push dword offset @f
           iretd
@@:        call std_out

.endif

           ret
test_iret  endp

TestIretStr db 'Test: IRET',13,10,0

.end
