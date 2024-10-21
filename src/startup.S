.text
.global _start
_start:
	li sp, 0x3000 // 32kb
	call main
	fence
