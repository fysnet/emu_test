comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: adc.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the adc instruction                                            *
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
; This routine 'tests' the adc instruction
; On entry:
;       nothing
; On return:
;       nothing
test_adc   proc near

           mov  si,offset TestAdcStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0FFFFh   ; all flags affected

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  al,0FDh
           adc  al,1
           
           call std_out
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  al,0FEh
           adc  al,1
           call std_out
           
           call std_out
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  al,0FEh
           adc  al,1
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  bl,0FFh
           adc  bl,1
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  cl,00h
           adc  cl,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dl,01h
           adc  dl,1
           call std_out

           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ah,7Eh
           adc  ah,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  bh,7Fh
           adc  bh,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ch,80h
           adc  ch,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dh,81h
           adc  dh,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  al,MEMREF
           adc  byte MEMREF,1
           mov  ah,MEMREF
           call std_out
           
           

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  ax,0FFFEh
           adc  ax,1
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ax,0FFFEh
           adc  ax,1
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  bx,0FFFFh
           adc  bx,1
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  cx,0000h
           adc  cx,1
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dx,0001h
           adc  dx,1
           call std_out

           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ax,7FFEh
           adc  ax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  bx,7FFFh
           adc  bx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  cx,8000h
           adc  cx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dx,8001h
           adc  dx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ax,MEMREF
           adc  word MEMREF,1
           mov  bx,MEMREF
           call std_out
           
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
.if (HIGHEST_CPU == 3)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  eax,0FFFFFFFEh
           adc  eax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ebx,0FFFFFFFFh
           adc  ebx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ecx,00000000h
           adc  ecx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  edx,00000001h
           adc  edx,1
           call std_out

           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  eax,7FFFFFFEh
           adc  eax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ebx,7FFFFFFFh
           adc  ebx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ecx,80000000h
           adc  ecx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  edx,80000001h
           adc  edx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  eax,MEMREF
           adc  dword MEMREF,1
           mov  ebx,MEMREF
           call std_out
.endif

           ret
test_adc   endp

TestAdcStr db 'Test: ADC',13,10,0

.end
