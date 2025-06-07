
# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------


	.section .data	# this part / code section is related to initialised data 
	.equ N, 1000	# constant N (with the value 1000) is defined 
S:	.long 0		# long integer variable S is declared
Msg:	.ascii "The sum from 11 to %d is %d\n\0"


	.section .text	# this part / code section is related to executable instructions
.globl main
main:	
	pushl %ebp	# ebp register's value is stored into the stack
	movl %esp, %ebp	# address stack pointer contains is copied into ebp register

 	# initialize
        movl $N, %ebx	# value of constant N is copied into ebx register

 	# compute sum
L1:
	addl %ebx, S	# adds ebx register's value to S and stores it into S
	decl %ebx       # decrements the value stored into the ebx register by 1
	cmpl $10, %ebx  # compares ebx register's value wuth number 10 
	jle  L2		# jumps to loop L2 if ebx register's value is less than or equal to number 10
        movl $L1, %eax	# else, copies address of L1 label into register eax
        jmp *%eax	# jumps to the address where eax register points to

L2:
	# print result
	pushl S		# S's value is stored into the stack
	pushl $N	# address of constant N is stored into the stack
	pushl $Msg	# address of message string 'Msg' is stored into the stack
	call printf	# calls printf function that takes 'Msg', N and S as its parameters
	popl %eax	# pops the top value from the stack into eax register
	popl %eax	# pops the top value from the stack into eax register 
	popl %eax	# pops the top value from the stack into eax register

	# exit
	movl $0, %eax  	# sets the return value of main function to 0
        leave		# tears down the stack frame of function main 
			# (movl %ebp, %esp  //  popl %ebp) 

 	ret		# returns control to the calling function
