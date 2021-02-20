comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: push.inc                                                           *
*                                                                          *
* DESCRIPTION:                                                             *
*   'tests' the push/pop/pusha/popa/pushf/popf instructions                *
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
; This routine 'tests' the push/pop/pusha/popa/pushf/popf instructions
; On entry:
;       nothing
; On return:
;       nothing
test_push  proc near

           mov  si,offset TestPushStr
           call display_string

           ; clear the registers
           call reset_all
           mov  word UNDEFINED_FLAGS,0x0000   ; flags are not affected (except pushf/popf)

.if (HIGHEST_CPU >= 1)
           mov  WORD0,sp
           push 1234h
           push 4321h
           push 2222h
           push 4444h
           push word WORD0
           push 0AAAAh
           push 0CCCCh
           push 0FFFFh
           popa
           call std_out

           mov  WORD0,sp
           push ax
           push cx
           push dx
           push bx
           push word WORD0
           push bp
           push si
           push di
           popa
           call std_out
           
           pusha
           pop  di
           pop  si
           pop  bp
           add  sp,2
           pop  bx
           pop  dx
           pop  cx
           pop  ax
           call std_out
.endif
           
           pushf
           pop  ax
           push ax
           popf
           call std_out
           
.if (HIGHEST_CPU == 3)
           
           mov  DWORD0,esp
           push dword 12345678h
           push dword 87654321h
           push dword 22222222h
           push dword 44444444h
           push dword dWORD0
           push dword 0AAAAAAAAh
           push dword 0CCCCCCCCh
           push dword 0FFFFFFFFh
           popad
           call std_out
           
           mov  DWORD0,esp
           push eax
           push ecx
           push edx
           push ebx
           push dword DWORD0
           push ebp
           push esi
           push edi
           popad
           call std_out
           
           pushad
           pop  edi
           pop  esi
           pop  ebp
           add  esp,4
           pop  ebx
           pop  edx
           pop  ecx
           pop  eax
           call std_out
           
           pushfd
           pop  eax
           push eax
           popfd
           call std_out
           
.endif           
           
           ret
test_push  endp

TestPushStr db 'Test: PUSHx/POPx',13,10,0

.end
