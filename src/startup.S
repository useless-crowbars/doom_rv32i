.text
.global _start
_start:
	li sp, 0x1FFF // 32kb
	call main
	fence
