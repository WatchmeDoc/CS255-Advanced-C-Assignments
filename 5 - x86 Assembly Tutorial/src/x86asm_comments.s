# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------

	.section .data	# Constants declaration section 
N:	.long 1000	    # Program calculates the sum up to this number.
S:	.long 0		    # Starting number from which the calculation of the sum will begin
Msg:	.ascii "The sum from 0 to %d is %d\n\0"


	.section .text	# Code section
.globl main
main:	
	pushl %ebp	    # Save old ebp value in stack
	movl %esp, %ebp	# Change ebp into the base of main's stack frame

 	# initialize
    movl N, %ebx	# Save N value in a general-purpose register for faster accessing

 	# compute sum
L1:
	addl %ebx, S	# S = S + %ebx
	decl %ebx       # %ebx = %ebx - 1
	cmpl $0, %ebx   # %ebx == 0 ?
	jng  L2	    	# Jump to L2 Tag
    movl $L1, %eax	# Save in %eax register the address of L1 tag
    jmp *%eax   	# Jump to where %eax register points at.

L2:
	# print result
	pushl S	    	# Save S's contents in stack
	pushl N	        # Save N's contents in stack
	pushl $Msg  	# Save Msg string in stack
	call printf 	# Call printf, where args were pushed in stack (the last push is the 1st arg)
	popl %eax   	# Pop from stack and save in register %eax
	popl %eax   	# Pop from stack and save in register %eax
	popl %eax   	# Pop from stack and save in register %eax

	# exit
	movl $0, %eax  	# %eax = 0;
    leave	    	# Restore stack pointer and base pointer (as program will exit)
 	ret             # ... and return to the address saved in the top of the stack.
