comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: setcc.inc                                                          *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the setcc instructions                                         *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 19 Feb 2021                                                *
*                                                                          *
*                                                                          *
***************************************************************************|

.if (HIGHEST_CPU >= 3)

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine 'tests' the setcc instructions
; On entry:
;       nothing
; On return:
;       nothing
test_setcc proc near

           mov  si,offset TestSetccStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; flags are not affected

           xor  ax,ax      ; set the flags in a known state (Carry = 0, Parity = Even, Aux = 0, Zero = 1, OF = 0)
           seta  al
           setna bl
           setb  cl
           setnb dl
           setc  ah
           setnc bh
           sete  ch
           setne dh
           call std_out
           
           setg  al
           setng bl
           setl  cl
           setnl dl
           setge ah
           setnge bh
           setle ch
           setnle dh
           call std_out

           seto  al
           setno bl
           setp  cl
           setnp dl
           sets  ah
           setns bh
           setz  ch
           setnz dh
           call std_out

           setz  BYTE0
           setnz BYTE1
           mov   al,BYTE0
           mov   ah,BYTE0
           setc  BYTE0
           setnc BYTE1
           mov   bl,BYTE0
           mov   bh,BYTE0
           call std_out

           ret
test_setcc endp

TestSetccStr db 'Test: SETcc',13,10,0

.endif

.end
