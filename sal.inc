comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: sal.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the sal instruction                                            *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*                                                                          *
* Last Updated: 22 Feb 2021                                                *
*                                                                          *
*                                                                          *
***************************************************************************|

; TODO:  the 286+ 'and's the rotate value with 1Fh

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine 'tests' the sal instruction
; On entry:
;       nothing
; On return:
;       nothing
test_sal   proc near

           mov  si,offset TestSalStr
           call display_string

           ; clear the registers
           call reset_all

           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  al,0FEh
           sal  al,1
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY | FLAGS_OVERFLOW))
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  cl,4    ;
           stc
           mov  bl,0FFh
           sal  bl,cl
           call std_out

.if (HIGHEST_CPU >= 1)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  cl,00h
           sal  cl,3
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dl,01h
           sal  dl,7
           call std_out
.endif
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  cl,3    ;
           mov  ah,7Eh
           sal  ah,cl
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  bh,7Fh
           sal  bh,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ch,80h
           sal  ch,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dh,81h
           sal  dh,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  al,MEMREF
           sal  byte MEMREF,1
           mov  ah,MEMREF
           call std_out
           
           

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ax,0FFFEh
           sal  ax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  bx,0FFFFh
           sal  bx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dx,0000h
           sal  dx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dx,0001h
           sal  dx,1
           call std_out

           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ax,7FFEh
           sal  ax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  bx,7FFFh
           sal  bx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dx,8000h
           sal  dx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dx,8001h
           sal  dx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ax,MEMREF
           sal  word MEMREF,1
           mov  bx,MEMREF
           call std_out



           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
.if (HIGHEST_CPU == 3)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  eax,0FFFFFFFEh
           sal  eax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ebx,0FFFFFFFFh
           sal  ebx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  edx,00000000h
           sal  edx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  edx,00000001h
           sal  edx,1
           call std_out

           
           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY | FLAGS_OVERFLOW))
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  cl,15    ;
           mov  eax,7FFFFFFEh
           sal  eax,cl
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ebx,7FFFFFFFh
           sal  ebx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  edx,80000000h
           sal  edx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  edx,80000001h
           sal  edx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  eax,MEMREF
           sal  dword MEMREF,1
           mov  ebx,MEMREF
           call std_out
.endif

           ret
test_sal   endp

TestSalStr db 'Test: SAL',13,10,0

.end
