comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: rcl.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the rcl instruction                                            *
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
; This routine 'tests' the rcl instruction
; On entry:
;       nothing
; On return:
;       nothing
test_rcl   proc near

           mov  si,offset TestRclStr
           call display_string

           ; clear the registers
           call reset_all

           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  al,0FEh
           rcl  al,1
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY | FLAGS_OVERFLOW))
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           mov  cl,4    ;
           stc
           mov  bl,0FFh
           rcl  bl,cl
           call std_out

.if (HIGHEST_CPU >= 1)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  cl,00h
           rcl  cl,3
           call std_out
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dl,01h
           rcl  dl,7
           call std_out
.endif
           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  cl,3    ;
           mov  ah,7Eh
           rcl  ah,cl
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  bh,7Fh
           rcl  bh,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ch,80h
           rcl  ch,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dh,81h
           rcl  dh,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  al,MEMREF
           rcl  byte MEMREF,1
           mov  ah,MEMREF
           call std_out
           
           

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ax,0FFFEh
           rcl  ax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  bx,0FFFFh
           rcl  bx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dx,0000h
           rcl  dx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dx,0001h
           rcl  dx,1
           call std_out

           
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ax,7FFEh
           rcl  ax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  bx,7FFFh
           rcl  bx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dx,8000h
           rcl  dx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  dx,8001h
           rcl  dx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ax,MEMREF
           rcl  word MEMREF,1
           mov  bx,MEMREF
           call std_out



           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
.if (HIGHEST_CPU == 3)
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  eax,0FFFFFFFEh
           rcl  eax,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ebx,0FFFFFFFFh
           rcl  ebx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  edx,00000000h
           rcl  edx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  edx,00000001h
           rcl  edx,1
           call std_out

           
           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY | FLAGS_OVERFLOW))
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  cl,15    ;
           mov  eax,7FFFFFFEh
           rcl  eax,cl
           call std_out

           mov  word UNDEFINED_FLAGS,(~(FLAGS_SIGN | FLAGS_ZERO | FLAGS_AUXILIARY | FLAGS_PARITY))
           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  ebx,7FFFFFFFh
           rcl  ebx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  edx,80000000h
           rcl  edx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  edx,80000001h
           rcl  edx,1
           call std_out

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc
           mov  eax,MEMREF
           rcl  dword MEMREF,1
           mov  ebx,MEMREF
           call std_out
.endif

           ret
test_rcl   endp

TestRclStr db 'Test: RCL',13,10,0

.end
