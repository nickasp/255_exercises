	.file	"x86sum2.c"
	.text
	.globl	i
	.data
	.align 4
	.type	i, @object
	.size	i, 4
i:
	.long	1000
	.globl	S
	.bss
	.align 4
	.type	S, @object
	.size	S, 4
S:
	.zero	4
	.section	.rodata
.LC0:
	.string	"The sum from 11 to %d is %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$4, %esp
#APP
# 12 "x86sum2.c" 1
	movl i, %ebx
L1:
	addl %ebx, S
	decl %ebx;cmpl $10, %ebx
	jle  L2
	movl $L1, %eax
	jmp *%eax
L2:
# 0 "" 2
#NO_APP
	movl	S, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$1000
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
