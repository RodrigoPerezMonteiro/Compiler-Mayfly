segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword 3
	call	printi
	add	esp, 4
	call	println
	pop	eax
	leave
	ret
extern	readi
extern	printi
extern	printd
extern	prints
extern	println
