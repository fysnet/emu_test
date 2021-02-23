comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: add.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the add instruction                                            *
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
; This routine 'tests' the add instruction
; On entry:
;       nothing
; On return:
;       nothing
test_add   proc near

           mov  si,offset TestAddStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0xFFFF   ; all flags affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  al,0FEh
           add  al,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  bl,0FFh
           add  bl,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  cl,00h
           add  cl,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  dl,01h
           add  dl,1
           call std_out

           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ah,7Eh
           add  ah,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  bh,7Fh
           add  bh,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ch,80h
           add  ch,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  dh,81h
           add  dh,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  al,MEMREF
           add  byte MEMREF,1
           mov  ah,MEMREF
           call std_out
           
           

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ax,0FFFEh
           add  ax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  bx,0FFFFh
           add  bx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  cx,0000h
           add  cx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  dx,0001h
           add  dx,1
           call std_out

           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ax,7FFEh
           add  ax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  bx,7FFFh
           add  bx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  cx,8000h
           add  cx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  dx,8001h
           add  dx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ax,MEMREF
           add  word MEMREF,1
           mov  bx,MEMREF
           call std_out



           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
.if (HIGHEST_CPU == 3)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  eax,0FFFFFFFEh
           add  eax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ebx,0FFFFFFFFh
           add  ebx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ecx,00000000h
           add  ecx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  edx,00000001h
           add  edx,1
           call std_out

           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  eax,7FFFFFFEh
           add  eax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ebx,7FFFFFFFh
           add  ebx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ecx,80000000h
           add  ecx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  edx,80000001h
           add  edx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  eax,MEMREF
           add  dword MEMREF,1
           mov  ebx,MEMREF
           call std_out
.endif

           ret
test_add   endp

TestAddStr db 'Test: ADD',13,10,0

.end
