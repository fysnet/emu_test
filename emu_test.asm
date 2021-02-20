comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: emu_test.asm                                                       *
*                                                                          *
* This code is freeware, not public domain.  Please use respectfully.      *
*                                                                          *
* You may:                                                                 *
*  - use this code for learning purposes only.                             *
*  - use this code in your own Operating System development.               *
*  - distribute any code that you produce pertaining to this code          *
*    as long as it is for learning purposes only, not for profit,          *
*    and you give credit where credit is due.                              *
*                                                                          *
* You may NOT:                                                             *
*  - distribute this code for any purpose other than listed above.         *
*  - distribute this code for profit.                                      *
*                                                                          *
* You MUST:                                                                *
*  - include this whole comment block at the top of this file.             *
*  - include contact information to where the original source is located.  *
*            https://github.com/fysnet/FYSOS                               *
*                                                                          *
* DESCRIPTION:                                                             *
*  This code will execute most all instructions of the 80x386 and then     *
*    log the results to be compared with the same results from another     *
*    emulator to compare the accuracy of each.                             *
*                                                                          *
* Option 0:                                                                *
*  This code creates a 1.44Meg floppy disk, ready to boot from your        *
*    emulator, sending the log to port 0xE9.                               *
*                                                                          *
* Option 1:                                                                *
*  This code creates a 64k ROM image read for your emulator to boot,       *
*    sending the log to port 0xE9.                                         *
*                                                                          *
*  In Bochs, redirect the output to a file:                                *
*     bochs > output.txt                                                   *
*                                                                          *
* BUILT WITH:   NewBasic Assembler                                         *
*                 http://www.fysnet/newbasic.htm                           *
*               NBASM ver 00.26.77                                         *
*          Command line: nbasm emu_test<enter>                             *
*                                                                          *
* Last Updated: 19 Feb 2021                                                *
*                                                                          *
****************************************************************************
* Notes:                                                                   *
*                                                                          *
* **** Be sure to read the README file for requirements ****               *
*                                                                          *
* Option 0:                                                                *
*   *** Assumes this is for a 1.44meg floppy drive ***                     *
*                                                                          *
* This bootsector does not have a file system on it. It simply boots,      *
*  loads any remaining sectors needed, then starts the tests.              *
*                                                                          *
* Hardware Requirements:                                                   *
*  This code uses commands that are valid for a 80x86 or later Intel x86   *
*  or compatible CPU up to the 80x386.                                     *
*                                                                          *
***************************************************************************|

.model tiny

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; Option 0:  floppy disk
; Option 1:  64k Rom
OPTION      equ   0


; Bochs/Windows prints a CR for every LF value it finds.
; i.e:  if a line contains 0D 0A in it, and you redirect to a file,
;  Bochs/Windows will place and extra 0D (0D 0D 0A).
; Therefore, set this to 1 if you plan on using Bochs as one of the test reports.
; Be sure to change it back for others.
IGNORECR    equ    0    ; set to 1 when using Bochs

HIGHEST_CPU equ    3    ; 0 = 8086, 1 = 186, 2 = 286, 3 = 386

.if (HIGHEST_CPU == 1)
.186
.endif

.if (HIGHEST_CPU == 2)
.286
.endif

.if (HIGHEST_CPU == 3)
.386
.endif

; image file we will use
.if (OPTION == 0) ; FLOPPY
outfile 'emu_test0.img'
.else
outfile 'emu_test1.img'
.endif

FLAGS_CARRY         equ  0x0001
FLAGS_ALWAYS_SET    equ  0x0002
FLAGS_PARITY        equ  0x0004
FLAGS_AUXILIARY     equ  0x0010
FLAGS_ZERO          equ  0x0040
FLAGS_SIGN          equ  0x0080
FLAGS_TRAP          equ  0x0100
FLAGS_INT_ENABLE    equ  0x0200
FLAGS_DIRECTION     equ  0x0400
FLAGS_OVERFLOW      equ  0x0800

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; we cannot write access to any memory in the ROM (if option 1 is given)
;  therefore, we need to use low memory for any write accesses
.if (OPTION == 1) ; ROM
; these will start at 0x8000:0000
TEMP             equ  ss:[0x0000]   ; temp word at 0x0000
MEMREF           equ  ss:[0x0002]   ; dword sized: an unused address for memref tests
UNDEFINED_FLAGS  equ  ss:[0x0006]   ; the undefined flags for the current test
BYTE0            equ  ss:[0x0008]   ; temp word location
BYTE1            equ  ss:[0x0009]   ; temp word location
WORD0            equ  ss:[0x000A]   ; temp word location
WORD1            equ  ss:[0x000C]   ; temp word location
DWORD0           equ  ss:[0x0010]   ; temp dword location
DWORD1           equ  ss:[0x0014]   ; temp dword location

LINENUM          equ  ss:[0x0020]   ; word sized: line number
TEMPBUFF         equ     [0x0022]   ; temp buffer (128 bytes)
.endif

.if (OPTION == 0) ; floppy disk
; these will start at 0x07C0:0000
TEMP             equ  es:[0x0000]   ; temp word at 0x0000
MEMREF           equ  es:[0x0002]   ; dword sized: an unused address for memref tests
UNDEFINED_FLAGS  equ  es:[0x0006]   ; the undefined flags for the current test
BYTE0            equ  es:[0x0008]   ; temp word location
BYTE1            equ  es:[0x0009]   ; temp word location
WORD0            equ  es:[0x000A]   ; temp word location
WORD1            equ  es:[0x000C]   ; temp word location
DWORD0           equ  es:[0x0010]   ; temp dword location
DWORD1           equ  es:[0x0014]   ; temp dword location

LINENUM          equ  es:[0x0020]   ; word sized: line number
TEMPBUFF         equ     [0x0022]   ; temp buffer (128 bytes)
.endif

.code                              ;
.rmode                             ; bios starts with (un)real mode

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; option zero is a 1.44 meg floppy
.if (OPTION == 0)
           org  00h                ; 07C0:0000h

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; so that a BIOS will load our sector, we have the 'ever known' three bytes
;  of the common FAT BPB as the first of our code.
           jmp  short start        ; There should always be 3 bytes of code
           nop                     ;  followed by the start of the data.

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; we start out with the BIOS having loaded us to 0x07C00.
; we then turn off interrupts (cli) so that we will not be interrupted.
; we set a stack to use the space under 0x07C00.
; we will also modify each of the exception handlers to call ours.
;
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ;  setup the stack and seg registers (real mode)
start:     cli                     ; don't allow interrupts

           ; our stack
           xor  ax,ax              ; 0000:7C00h = 0x07C00
           mov  ss,ax              ; start of stack segment (07C0h)
           mov  sp,7C00h           ; first push at 0000:7BFEh

           ; our segment registers
           mov  ax,07C0h           ;
           mov  ds,ax              ;
           mov  es,ax              ;
           
           sti                     ; allow interrupts again (breifly)
           
           ; jump over the included code that must be in the first sector
           jmp  read_remaining

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

; include the disk read service(s), (must be within the first sector of our code)
include read_sect.inc

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; 
read_remaining:
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; reset the disk services to be sure we are ready
           ;xor  ax,ax
           ;mov  dl,0
           ;int  13h
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; read up to 127 more sectors to 0x7E00
           mov  ax,1               ; LBA 1
           mov  cx,127             ; 127 more sectors
           mov  bx,512             ; es:bx -> 07C0:0200h -> 0x07E00
           call read_sectors       ; 
           jc   short @f
           jmp  read_okay
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; an error reading from the disk
@@:        mov  si,offset diskerrorS
           call display_string
           jmp  halt
.endif

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; Option 1 is a 64k BIOS ROM
.if (OPTION == 1)
           org  00h                ; F000:0000

bios_option_start:
           mov  ax,0F000h
           mov  ds,ax
           mov  es,ax

           mov  ax,8000h           ; We can't write to a ROM (address > 0xC0000),
           mov  ss,ax              ;  so we have to place our stack in real memory
           mov  sp,0FFFEh          ; 8FFFE will do.
           
           jmp  read_okay
.endif

; include the char out services
include char_out.inc               ; include the display_char and display_string functions

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; read all of the needed sectors, so print the welcome string and start
;  testing instructions.
read_okay:
           mov  si,offset WelcomeStr
           call display_string

.if (OPTION == 0)           
           ; let the BIOS turn off the floppy drive
           mov  byte ss:[0440h],1
@@:        mov  al,ss:[0440h]
           or   al,al
           jnz  short @b
.endif

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; reset all of the exception handlers to call ours instead.
           cli                     ; don't allow interrupts
           call reset_handlers

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; test for each processor type, so that we test that process as well
.if (HIGHEST_CPU >= 1)
           call check_186
           jc   short halt
.endif

.if (HIGHEST_CPU >= 2)
           call check_286
           jc   short halt
.endif

.if (HIGHEST_CPU == 3)
           call check_386
           jc   short halt
.endif

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; skip over the 'junk' and start the tests
           jmp   start_tests

halt:      hlt
           jmp  short halt
           
; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;  Pad out to fill 512 bytes, including final word 0xAA55
;%print (200h-$-2)                  ; ~6 / ~171 bytes free in this area
           org (200h-2)
           dw  0AA55h

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; some string data

WelcomeStr db  13,10
           db  'x86 Instruction Test                                               v00.00.01',13,10
           db  '(C)opyright 1984-2021                                 Forever Young Software',13,10,0

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; here is where we start calling each routine to 'test' each instruction.
; be sure to set the CPU equates above so we test 80x86, 186, 286, etc.
start_tests:
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; make sure we start with line number 0
           mov  word LINENUM,0

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; make sure the values at our scratch area, are known values
.if (HIGHEST_CPU == 3)
           mov  dword MEMREF,0x12345678
           mov  dword DWORD0,0x87654321
           mov  dword DWORD1,0x0ABCDEF0
.else
           mov  word MEMREF,0x1234
.endif
           mov  byte TEMP,0x77
           mov  byte BYTE0,0x12
           mov  byte BYTE1,0x34
           mov  word WORD0,0x5678
           mov  word WORD1,0x9ABC
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; these are mostly in alphabetical order, though liked
           ;  instructions are grouped together.
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; aaa/aad
           call  test_aaa
           call  test_aad
           call  test_aas
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; add/adc/sub/sbb
           call  test_add
           call  test_adc
           call  test_sub
           call  test_sbb
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; and/or/test/xor
           call  test_and
           call  test_or
           call  test_test
           call  test_xor

.if (HIGHEST_CPU == 3)
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; bound
           call  test_bound
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; bsf/bsr/bt/btc/btr/bts
           call  test_bsf
           call  test_bsr
           call  test_bt
           call  test_btc
           call  test_btr
           call  test_bts

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; bswap
           call  test_bswap
.endif

           ; TODO:  call

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; cbw
           call  test_cbw
           call  test_cwd
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; clc/stc/cmc & cld/std
           call  test_clc
           call  test_cld

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; TODO:  cmovcc
           call  test_jcc

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; cmp
           call  test_cmp

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; cmpsb/w/d
           call  test_cmps
           call  test_lods
           call  test_scas
           call  test_stos

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; dec/inc
           call  test_dec
           call  test_inc

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; div
           call  test_div
           call  test_idiv

           ; TODO: Enter

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; imul
           call  test_imul
           call  test_mul

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; lahf/sahf
           call  test_lahf

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; lea
           call  test_lea

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; loop and loopcc
           call  test_loopcc
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; mov
           call  test_mov

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; neg/not
           call  test_neg
           call  test_not

.if (HIGHEST_CPU >= 3)
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; pause
           call  test_pause
.endif
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; pushx/popx
           call  test_push

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; rcl/rcr/rol/ror
           call  test_rcl
           call  test_rcr
           call  test_rol
           call  test_ror

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; sal/sar/shl/shr
           call  test_sal
           call  test_sar
           call  test_shl
           call  test_shr
           
.if (HIGHEST_CPU >= 3)
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; setcc
           call  test_setcc
           
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; shld/shrd
           call  test_shld
           call  test_shrd
.endif
           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; xlat
           call  test_ud2

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; xchg
           call  test_xchg

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ; xlat
           call  test_xlat

           mov  si,offset DoneStr
           call display_string
           
; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;  we are done, so halt
end_halt:  hlt
           jmp  short end_halt

DoneStr    db  'Done.',13,10,0
           
; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; include any helper functions
include    test_proc.inc

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; include all of the instruction test code
include    aaa.inc
include    aad.inc
include    aas.inc

include    add.inc
include    adc.inc
include    sub.inc
include    sbb.inc

include    and.inc
include    or.inc
include    test.inc
include    xor.inc

include    bound.inc

include    bsf.inc
include    bsr.inc
include    bt.inc
include    btc.inc
include    btr.inc
include    bts.inc

include    bswap.inc

include    cbw.inc
include    cwd.inc

include    clc.inc
include    cld.inc

include    jcc.inc

include    cmp.inc

include    cmps.inc
include    lods.inc
include    scas.inc
include    stos.inc

include    dec.inc
include    inc.inc

include    div.inc
include    idiv.inc

include    imul.inc
include    mul.inc

include    lahf.inc

include    lea.inc

include    loopcc.inc

include    mov.inc

include    neg.inc
include    not.inc

.if (HIGHEST_CPU >= 3)
include    pause.inc
.endif

include    push.inc
           
include    rcl.inc
include    rcr.inc
include    rol.inc
include    ror.inc

include    sal.inc
include    sar.inc
include    shl.inc
include    shr.inc

include    setcc.inc

.if (HIGHEST_CPU == 3)
include    shld.inc
include    shrd.inc
.endif

include    ud2.inc

include    xchg.inc

include    xlat.inc


           
; %print (65536 - $)                 ; count of bytes left in this segment

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; option 0 needs 2880 sectors
.if (OPTION == 0)

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
;  End of code. Pad out to fill 1.44Meg disk
.pmode     ; this is so NBASM won't give us the 'segment is near 64k' error
           org (2880 * 512)
.endif

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; option 1 needs 64k bytes
.if (OPTION == 1)
.pmode     ; this is so NBASM won't give us the 'segment is near 64k' error
           ; however, remember that NBASM now thinks you are in pmode and will
           ;  assemble the instructions accordingly.

           ; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
           ;  we need to be at 0xFFFFFFF0
           ;  which in 16-bit mode (20-bit adresses) is 0x000FFFF0
           org (65536 - 16)
           
           db  0EAh
           dw  offset bios_option_start
           dw  0F000h
           
           dup 11,0
.endif

.end
