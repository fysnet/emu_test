comment |*******************************************************************
*  Copyright (c) 1984-2021    Forever Young Software  Benjamin David Lunt  *
*                                                                          *
*                            FYS OS version 2.0                            *
* FILE: read_chs.inc                                                       *
*                                                                          *
* DESCRIPTION:                                                             *
*   Read Sectors using CHS                                                 *
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
; if we have included this after the first sector, we are in error...
.ifa $, 200h
%error 1, 'This must be in the first sector of the code...'
.endif

.if (_VER < 2673h)
%error 1, 'This source requires NBASM version 00.26.73 or higher'
.endif

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine reads in CX sectors using the bios interrupt 13h service
; Since we don't know if the current bios can span heads and cylinders,
;  with multiple counts in CX, we will read one sector at a time, manually
;  updating DH, and CX as we go.
; On entry:
;      AX =  starting sector in LBA format
;   ES:BX -> physical address to read to
;      CX =  count of sectors to read
; On return:
;   carry set if error
;   carry clear if successfull
read_sectors proc near uses ax bx cx dx es
read_loop: push ax
           push cx
           push bx
           
           call lba_to_chs         ; ax(lba) -> (ax/cx/dx)(chs)
           mov  ax,0003h           ; three try's
chck_loop: push ax
           mov  dl,0               ; dl = drive
           mov  ax,0201h
           int  13h                ; do the read/write
           pop  ax
           jnc  short int13_no_error
           push cx
           push dx
           xor  ah,ah
           int  13h                ; reset disk
           pop  dx
           pop  cx
           dec  ax
           jnz  short chck_loop    ; try again
           
           stc
           ret
           
int13_no_error:
           ; calculate next position
           pop  bx
           add  bx,512             ; assumes all sectors are 512 bytes each
           
           pop  cx                 ; restore sector count
           pop  ax                 ; restore current LBA
           inc  ax                 ; inc to next LBA sector
           loop read_loop          ; decrement counter, read another one
           
           clc
           ret
read_sectors endp

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine converts LBA (AX) to CHS
; Sector   = (LBA mod SPT)+1
; Head     = (LBA  /  SPT) mod Heads
; Cylinder = (LBA  /  SPT)  /  Heads
;    (SPT = Sectors per Track)
; on entry:
;  ax = LBA
; on return
;  DX and CX = BIOS formatted CHS values
;   cl = sector (1 based) (lower 6 bits)
;   ch = cyl (high 2 bits of cl also)
;   dh = head
; assumptions:
;   ax <= 0x7FFF (i.e.: bit 15 = clear)
;   (0x7FFF = 32,767 sectors)
lba_to_chs proc near
           ; dx:ax = LBA
           xor  dx,dx
           
           mov  cx,18              ; sectors per track
           div  cx                 ; ax = dx:ax / cx  with dx = remdr.
           ; ax = (LBA / SPT)
           ; dx = remainder (zero based sector)
           
           push dx                 ; save zero based sector
           
           xor  dx,dx
           ; dx:ax = (LBA / SPT)
           
           mov  cx,2               ; heads per cylinder
           div  cx                 ; ax = dx:ax / cx  with dx = remdr.
           ; ax = cylinder
           ; dx = head
           
           mov  dh,dl              ; save head number in dh
           ; dh = head
           
           pop  cx                 ; cx = zero based sector
           inc  cx                 ; sectors are one (1) based
           ; cx = 1 based sector
           
           ; ax = cylinder
           mov  ch,al
           shl  ah,1               ; we are not a 80x186 yet, so must use six 1's
           shl  ah,1
           shl  ah,1
           shl  ah,1
           shl  ah,1
           shl  ah,1
           or   cl,ah
           ; cx = LLLLLLLLHHSSSSSS  (L = low cyl 8 bits, H = high 2 bits, S = 1 based sector number)
           
           ret
lba_to_chs endp

diskerrorS    db  13,10,'Error reading disk or non-system disk.',0

.end
