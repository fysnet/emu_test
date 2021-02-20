comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: cbw.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the cbw instruction                                            *
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
; This routine 'tests' the cbw instruction
; On entry:
;       nothing
; On return:
;       nothing
test_cbw   proc near

           mov  si,offset TestCbwStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; flags are not affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)

           mov  ax,0EE00h
           cbw
           call std_out

           mov  ax,0EE01h
           cbw
           call std_out

           mov  ax,0EE80h
           cbw
           call std_out

           mov  ax,0EEFFh
           cbw
           call std_out

.if (HIGHEST_CPU == 3)
           mov  eax,0EEEE0000h
           cwde
           call std_out

           mov  eax,0EEEE0001h
           cwde
           call std_out

           mov  eax,0EEEE8000h
           cwde
           call std_out

           mov  eax,0EEEEFFFFh
           cwde
           call std_out
.endif

           ret
test_cbw   endp

TestCbwStr db 'Test: CBW/CWDE',13,10,0

.end
