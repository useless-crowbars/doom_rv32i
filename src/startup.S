.text
.global _start
_start:
	li sp, 0x2000 // 32kb
	call main
	fence
