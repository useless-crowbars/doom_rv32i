#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

char *stpcpy(char *restrict dst, const char *restrict src);
char *strcpy(char *restrict dst, const char *restrict src);
char *strncpy(char *dst, const char *restrict src, size_t dsize);
int abs(int j);
int atoi(const char *nptr);
int snprintf(char *str, size_t size, const char *restrict format, ...);
int sprintf(char *restrict str, const char *restrict format, ...);
int strcasecmp(const char *s1, const char *s2);
int strcmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
int tolower(int c);
int toupper(int c);
size_t strlen(const char *s);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *s, int c, size_t n);
char *strcat(char *restrict dst, const char *restrict src);
void *alloca(size_t size);

int abs(int j)
{
	return j;
}
#ifdef __riscv
char *stpcpy(char *restrict dst, const char *restrict src)
{
	return NULL;
}
char *strcpy(char *restrict dst, const char *restrict src)
{
	return NULL;
}
char *strncpy(char *dst, const char *restrict src, size_t dsize)
{
	return NULL;
}
int atoi(const char *nptr)
{
	return 0;
}
int snprintf(char *str, size_t size, const char *restrict format, ...)
{
	return 0;
}
int sprintf(char *restrict str, const char *restrict format, ...)
{
	return 0;
}
int strcasecmp(const char *s1, const char *s2)
{
	return 0;
}
int strcmp(const char *s1, const char *s2)
{
	return 0;
}
int strncasecmp(const char *s1, const char *s2, size_t n)
{
	return 0;
}
int tolower(int c)
{
	return 0;
}
int toupper(int c)
{
	return 0;
}
size_t strlen(const char *s)
{
	return 0;
}
void *memcpy(void *dest, const void *src, size_t n)
{
	return NULL;
}
void *memset(void *s, int c, size_t n)
{
	return NULL;
}
char *strcat(char *restrict dst, const char *restrict src)
{
	return NULL;
}

void *alloca(size_t size)
{
	return NULL;
}
#endif
