segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword 1
	push	dword 2
	pop	eax
	add	dword [esp], eax
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
