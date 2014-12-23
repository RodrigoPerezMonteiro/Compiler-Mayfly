segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
segment	.rodata
align	4
_L1:
	db	"x", 10, "Y", 9, 0, 10, 0
segment	.text
	push	dword $_L1
	call	prints
	add	esp, 4
	call	println
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
