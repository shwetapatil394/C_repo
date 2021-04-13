.section .rodata
	msg:
	.string	"x.a = %d, x.b = %d, x.c = %d, x.d = %d, x.e = %d\n, x.f = %d, x.g = %d\n" 

.section .bss
	.comm	x, 28, 4 

.section .text 
.globl	main 
.type	main, @function 
main: 
	# PROLOGUE 
	pushl	%ebp
	movl	%esp, %ebp 
	
	movl	$x, %eax
	movl	$10, (%eax) 
	movl	$20, 4(%eax) 
	movl	$30, 8(%eax) 
	movl	$40, 12(%eax) 
	movl	$50, 16(%eax) 
	movl	$60, 20(%eax)
	movl	$70, 24(%eax) 
	
# printf("x.a=%d, x.b=%d, x.c=%d, x.d=%d, x.e=%d, x.f=%d, x.g=%d\n", 
# 		x.a, x.b, x.c, x.d, x.e, x.f, x.g); 

	movl	$x, %eax 
	movl	24(%eax), %edx 
	pushl	%edx 
	movl	20(%eax), %edx 
	pushl	%edx 
	movl	16(%eax), %edx 
	pushl	%edx 
	movl	12(%eax), %edx 
	pushl	%edx 
	movl	8(%eax), %edx 
	pushl	%edx 
	movl	4(%eax), %edx 
	pushl	%edx 
	movl	(%eax), %edx 
	pushl	%edx 
	pushl	$msg 
	call	printf
	addl	$32, %esp 

	pushl	$0 
	call	exit 

