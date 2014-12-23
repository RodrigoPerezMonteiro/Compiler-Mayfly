segment	.text
align	4
global	f:function
f:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	pop	eax
	leave
	ret
extern	readi
extern	printi
extern	printd
extern	prints
extern	println
