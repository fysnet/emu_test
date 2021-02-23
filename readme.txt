x86 Instruction Test                                                v00.00.01
(C)opyright 1984-2021    fys [at] fysnet [dot] net     Forever Young Software


* Description
This utility is used to display the output of most instructions of the
80x86, 80x186, 80x286, and 80x386, when executed within an emulator.

This is not a tester.  It does not test that an instruction is executing
correctly.  It simply executes the instruction in a known state, then
prints the results.

You can then compare these results to the output of another emulator.

For example, I have made a toy x86 emulator that emulates each instruction
up to the 80x386. To test that I have implemented these instructions
correctly, I output all results to a file.  I then run the same 'test'
app on another emulator, known to be quite accurate.  If there is a difference,
I can then investigate the error.

Here is an example output of a single ADD instruction:

00023: 0000FFFF 00008000 00008101 00008202 00000000 00000000 00000000 00000084

This tells me that it is the 24th test (line 0023, zero based), prints the
register contents *after* the execution of the instruction, in the following
order:  EAX EBX ECX EDX ESI EDI EBP EFLAGS

Only the relative flags for this instruction are displayed.  All undefined
and unrelated flags are masked off.

Please see the bochs.txt file for an example output when ran under BOCHS.

If I take this 'test' to another emulator, it should produce the same line
for the same instruction.  If it does not, one (or both) of the emulators is 
in error.

* Requirments
This 'test' can be ran two ways:

Option 0 will create a 1.44meg bootable floppy image.
   Advantage:  Boots almost anywhere a floppy disk is emulated.
               Can use the BIOS to print to the screen.
Disadvantage:  The BIOS has already been loaded and could possibly be in the way.

Option 1 will create a 64k ROM BIOS image.
    Advatage:  Since nothing was previously loaded, nothing is in the way.
Disadvantage:  You must be able to specify the BIOS ROM image to use.
               You cannot use the BIOS to print to the screen.

The test is coded to print all output to either the screen using the BIOS 
(option 0 only) or to the non-existant IO Port 0xE9.  As long as your emulator
can 'catch' either of these techniques, you can redirect to a file for comparison.

It is recommended that if you use one option on one emulator, that you use the
same option on the other emulator(s).  As of this writing, all instructions will
produce the same output when the tests are ran using different options, *except*
for the MOV instruction.  The MOV instruction reads from memory and this memory
cannot be consistant due to the fact that on the ROM BIOS option, writing to
the ROM memory is forbidden.  Therefore, the values cannot be pre-written before
the test performs the instruction.
(yes, all tests for this instruction could use a lower address, but currently the
 test is written so it does not...Something to remedy in the future)

Since each processor performed differently with some instructions, the 'test' 
will allow you to specify what CPU you wish to test.
  0 = 80x86
  1 = 80x186
  2 = 80x286
  3 = 80x386

However, please note that the emulator you are 'testing' must be told to emulate
that version of the processor for the test to be accurate.  You cannot tell
this test to use the 80x186, yet have the emulator emulate a 80x386.  The test
will fail.

Also, please note that if you have the test and emulator each set for 80x186
(for example), and you use the BIOS option, the loaded BIOS must not use any
instructions above the 80x186.  Hence, use the ROM option.

* To build the images
The images are built using the NBASM assembler found at:
            http://www.fysnet/newbasic.htm
                 NBASM ver 00.26.77

Simply use the following command line:
  nbasm emu_test

To specify which option to assemble, use the 
  
   OPTION      equ   1

equate in the emu_test.asm file, setting to either 0 or 1.

* Notes:
Please note that this is a pre-release, or beta release.  Each instruction 'tested'
is mostly just some random instruction formats, for each instruction.
Many of the instruction 'tests' can be much improved.  For example, the ADD
instruction currently does the following:

  mov  ax,7FFFh
  add  ax,1

and then prints the result.  Since 7FFFh is not yet signed, adding 1 should now
set the sign bit.  This is a simple test.  A much more detailed test can be made
for each instruction.

With this in mind, (mostly) each instruction has its own include file, named
for the instruction.  The ADD instruction is in the add.inc file.

To create a more detailed 'test', simple add to the add.inc file and re-build. 
No other modification is needed.

A note about the MOV instruction, or any other instruction that will read from
memory:  

Each line is given so that you can test that instruction sequence.  Therefore,
the example below shows two tests.  Placing a large value in EBX, then reading
from a memory reference.

    mov  ebx,0123456789ABCDEFh
    mov  eax,[ebx]

However, unless you have *a lot* of memory, the second sequence will fault the
processor.  Take care in what each register's contents will be throughout the
test, when writing instructions for test.

I will improve this set of tests as time permits and as the process or my
emulator evolves.

For now, you can use the included two image files to test your emulator, or
simply for fun, test an already made emulator, such as Bochs.

  test_emu0.img   uses OPTION 0, floppy disk boot  (1.44M image)
  test_emu1.img   uses OPTION 1, ROM BIOS  (64k image)

For an example, when running within BOCHS, use the following:

  floppya: 1_44=emu_test0.img, status=inserted

with a standard BIOS of your choosing, being sure to boot to the floppy.

If you wish to use the ROM version, use the following:

  romimage: file=emu_test1.img

which will boot directly to the ROM image.

Please note, that if you use the FLOPPY option, you can see the results on the
BOCHS montitor window.  To get them to a file, simply redirect.

  bochs > bochs0.txt

However, when redirection is used, *or* the ROM option is used, you cannot
tell when the test is done.  Simply give it a few seconds, 60 or so, and then
stop the emulation.  If the test was successfull and went to the end, the
file will have 'Done.' as the last line.

Of course, you are more than welcome to improve each and any instruction.
Simply do so, then send me your results and I will post them here.

Here is an example source file, which prints the results for the CLC, STC,
and CMC instructions:

; =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; This routine 'tests' the clc/stc/cmc instructions
; On entry:
;       nothing
; On return:
;       nothing
test_clc   proc near

           ; these two lines simply print the instruction we are currently 'testing'.
           mov  si,offset TestClcStr
           call display_string

           ; clear the registers:
           ;  this clears all the registers used, so that
           ;   we have a known state before we execute the
           ;   instruction.
           call reset_all
           
           ; since each emulator (processor) can and will have different
           ; values for the undefined flags of an instruction, we specify
           ; these undefined flags here so that they are masked off when
           ; the results are printed.
           ; for example, if the instruction had the CARRY flag as undefined,
           ; we would use the following line:
           ;  mov  word UNDEFINED_FLAGS,(~(FLAGS_CARRY))
           ; how about the Zero & Parity flags as undefined?
           ;  mov  word UNDEFINED_FLAGS,(~(FLAGS_ZERO | FLAGS_PARITY))
           ; if we want to print all associated flags, simply use 0xFFFF
           ; like we do here.
           mov  word UNDEFINED_FLAGS,0xFFFF   ; all other flags are not affected
           
           xor  ax,ax   ; set the flags to a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc          ; set the carry (hard code it here)
           clc          ; clear it
           call std_out ; now print the results, in this case, only the FLAGS field is modified.

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           stc          ; set it,
           call std_out ;  printing the results again.

           xor  ax,ax   ; set the flags in a known state (Carry = 0, Parity = Even, Aux = ?, Zero = 1, OF = 0)
           cmc          ; compliment it,
           call std_out ;  printing the results one more time.

           ret
test_clc   endp

TestClcStr db 'Test: CLC/STC/CMC',13,10,0

.end

Each instruction can have its own file as the one above and have as many or
as few 'tests' as you wish.  No need to modify any other file, except add
the file and the 'call' to the emu_test.asm file.

Again, to be accurate, this code does not actually test the instruction for
accuracy.  It simply executes the instruction and prints the state of the
machine so that it can be compared to another emulator.

In fact, if something was added to the CHAR_OUT.INC file, such as a serial_out
routine, this could actually be ran on real hardware, as long as you were
able to 'catch' the serial stream on another machine.  However, currently 
this is coded for emulators, not real hardware.

Ben