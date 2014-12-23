segment	.text
align	4
global	_main:function
_main:
	push	ebp
	mov	ebp, esp
	sub	esp, 0
	push	dword 2
	pop	eax
	cmp	eax, byte 0
	je	near _L1
segment	.rodata
align	4
_L2:
	db	"KO", 0
segment	.text
	push	dword $_L2
	call	prints
	add	esp, 4
	call	println
	call	printi
	add	esp, 4
	call	println
	jmp	dword _L3
_L1:
segment	.rodata
align	4
_L4:
	db	"OK", 0
segment	.text
	push	dword $_L4
	call	prints
	add	esp, 4
	call	println
	call	printi
	add	esp, 4
	call	println
_L3:
	pop	eax
	leave
	ret
extern	readi
extern	printi
extern	printd
extern	prints
extern	println
