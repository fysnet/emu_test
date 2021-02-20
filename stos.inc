comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: stos.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the stosb/w/d instructions                                     *
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
; This routine 'tests' the stosb/w/d instructions
; On entry:
;       nothing
; On return:
;       nothing
test_stos  proc near

           mov  si,offset TestStosStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000

           mov  al,'A'
           lea  di,TEMPBUFF
           mov  cx,24
           rep
             stosb
           call std_out
           
           mov  ax,'G'
           lea  di,TEMPBUFF
           mov  cx,21
           rep
             stosw
           call std_out

.if (HIGHEST_CPU == 3)
           mov  eax,'Z'
           lea  di,TEMPBUFF
           mov  cx,12
           rep
             stosd
           call std_out
.endif
           ret
test_stos  endp

TestStosStr db 'Test: STOSB/W/D',13,10,0

.end
