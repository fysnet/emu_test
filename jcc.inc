comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: jcc.inc                                                            *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the jcc instructions                                           *
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
; This routine 'tests' the jcc instructions
; On entry:
;       nothing
; On return:
;       nothing
test_jcc   proc near

           mov  si,offset TestJccStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; flags are not affected

           mov  dx,1234h   ; 
           mov  bx,0001h   ; or'ing bit
           mov  cx,5555h   ; so we can test the jcxz instruction
           xor  ax,ax      ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           jc   short @f
           jpo  short @f
           jnz  short @f
           jo   short @f
           
           ; we should have gotten here (passed test)
           or   ax,bx

           ; now let's check jCXz
@@:        shl  bx,1       ; shift to next bit position/next test
           jcxz short @f

           ; we should have gotten here (passed test)
           or   ax,bx

@@:        shl  bx,1       ; shift to next bit position/next test
           mov  cx,0000h
           jcxz short jcxzpassed
           jmp  short @f
jcxzpassed:
           ; we should have gotten here (passed test)
           or   ax,bx

           ; test zero, sign, & carry
@@:        shl  bx,1       ; shift to next bit position/next test
           cmp  dx,1234h
           jnz  short @f
           ja   short @f
           jb   short @f
           jl   short @f
           jg   short @f
           js   short @f

           ; we should have gotten here (passed test)
           or   ax,bx

           ; test zero, sign, & carry
@@:        shl  bx,1       ; shift to next bit position/next test
           cmp  dx,4321h
           jz   short @f
           ja   short @f
           jnb  short @f
           jge  short @f
           jnle short @f
           jns  short @f

           ; we should have gotten here (passed test)
           or   ax,bx

@@:        shl  bx,1       ; shift to next bit position/next test
           cmp  dx,1111h
           jz   short @f
           jb   short @f
           jna  short @f
           jnge short @f
           jle  short @f
           js   short @f

           ; we should have gotten here (passed test)
           or   ax,bx

@@:        shl  bx,1       ; shift to next bit position/next test
           
           
           
           ; now print out the registers (specifically ax)
           ;  each bit in ax specifies that it passed that test
           call std_out

           ret
test_jcc   endp

TestJccStr db 'Test: Jcc',13,10,0

.end
