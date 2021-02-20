comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: bswap.inc                                                          *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the bswap instruction                                          *
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
; This routine 'tests' the bswap instruction
; On entry:
;       nothing
; On return:
;       nothing
test_bswap proc near

           mov  si,offset TestBswapStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; flags are not affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)

           mov  eax,0A55AA55Ah
           bsr  eax,eax
           call std_out

           mov  eax,12345678h
           bsr  ebx,ebx
           call std_out

           mov  eax,87654321h
           bsr  ecx,ecx
           call std_out

           ret
test_bswap endp

TestBswapStr db 'Test: BSWAP',13,10,0

.endif

.end
