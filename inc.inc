comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: inc.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the inc instruction                                            *
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
; This routine 'tests' the inc instruction
; On entry:
;       nothing
; On return:
;       nothing
test_inc   proc near

           mov  si,offset TestIncStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0xFFFF   ; 

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  al,7Fh
           inc  al
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  bl,01h
           inc  bl
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  cl,00h
           inc  cl
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  dl,0FFh
           inc  dl
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ah,0FEh
           inc  ah
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  bh,81h
           inc  bh
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ch,80h
           inc  ch
           call std_out


           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ax,7FFFh
           inc  ax
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  bx,0001h
           inc  bx
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  cx,0000h
           inc  cx
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  dx,0FFFFh
           inc  dx
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  si,0FFFEh
           inc  si
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  di,8001h
           inc  di
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  bp,8000h
           inc  bp
           call std_out


.if (HIGHEST_CPU == 3)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  eax,7FFFFFFFh
           inc  eax
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ebx,00000001h
           inc  ebx
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ecx,00000000h
           inc  ecx
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  edx,0FFFFFFFFh
           inc  edx
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  esi,0FFFFFFFEh
           inc  esi
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  edi,80000001h
           inc  edi
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ebp,80000000h
           inc  ebp
           call std_out
.endif

           ret
test_inc   endp

TestIncStr db 'Test: INC',13,10,0

.end
