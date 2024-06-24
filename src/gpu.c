#include "gpu.h"
bool end = false;
char key_changed;
bool key_pressed;
bool change_ack = true;


#ifdef __riscv
void init_window() {}
void init_screen() {}
void write_screen(int x, int y, uint32_t color) {}
void update_screen() {}
void poll_keyboard() {}
void cleanup() {}

double __divdf3 (double a, double b) { return 0; }
double __floatsidf (int i) { return 0; }
double __muldf3 (double a, double b) { return 0; }
int __divsi3(int a, int b) { return 0; }
int __fixdfsi (double a) { return 0; }
int __gedf2 (double a, double b) { return 0; }
int __ltdf2 (double a, double b) { return 0; }
int __modsi3(int a, int b) { return 0; }
int __mulsi3(int a, int b) { return 0; }
long __muldi3 (long a, long b) { return 0; }
unsigned int __udivsi3 (unsigned int a, unsigned int b) { return 0; }

char *stpcpy(char *restrict dst, const char *restrict src) { return NULL; }
char *strcpy(char *restrict dst, const char *restrict src) { return NULL; }
char *strncpy(char* dst, const char *restrict src, size_t dsize) { return NULL; }
int abs(int j) { return j; }
int atoi(const char *nptr) { return 0; }
int snprintf(char* str, size_t size, const char *restrict format, ...) { return 0; }
int sprintf(char *restrict str, const char *restrict format, ...) { return 0; }
int strcasecmp(const char *s1, const char *s2) { return 0; }
int strcmp(const char *s1, const char *s2) { return 0; }
int strncasecmp(const char* s1, const char* s2, size_t n) { return 0; }
int tolower(int c) { return 0; }
int toupper(int c) { return 0; }
size_t strlen(const char *s) { return 0; }
void *memcpy(void* dest, const void* src, size_t n) { }
void *memset(void* s, int c, size_t n) { }
char *strcat(char *restrict dst, const char *restrict src) { return NULL; }


typedef void FILE;
typedef uint32_t useconds_t;
void *alloca(size_t size) { return NULL; }
void exit(int status) { }
int fclose(FILE *stream) { return 0; }
int fprintf(FILE *restrict stream, const char *restrict format, ...) { return 0; }
int printf(const char *restrict format, ...) { return 0; }
void *malloc(size_t size) { return 0; }
int getc(FILE *stream) { return 0; }
int getchar(void) { return 0; }
int usleep(useconds_t usec) { return 0; }

#else

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>


GLFWwindow *window;
uint32_t *screen;
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);


void init_window()
{
	if (!glfwInit()) {
		exit(1);
	}

	window = glfwCreateWindow(GPU_SCREEN_WIDTH, GPU_SCREEN_HEIGHT, "Simple GPU Simulation", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
}

void init_screen()
{
	init_window();

	screen = (uint32_t *)malloc(GPU_SCREEN_WIDTH * GPU_SCREEN_HEIGHT * sizeof(uint32_t));
	if (!screen) {
		exit(1);
	}

	for (int y = 0; y < GPU_SCREEN_HEIGHT; y++) {
		for (int x = 0; x < GPU_SCREEN_WIDTH; x++) {
			screen[y * GPU_SCREEN_WIDTH + x] = 0xFFFF0000;
		}
	}
}

void write_screen(int x, int y, uint32_t color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	for (int j = 0; j < SCALE; j++) {
		for (int i = 0; i < SCALE; i++) {
			screen[(y * SCALE + j) * GPU_SCREEN_WIDTH + x * SCALE + i] = color;
		}
	}
}

void update_screen()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(GPU_SCREEN_WIDTH, GPU_SCREEN_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screen);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void poll_keyboard()
{
	glfwPollEvents();
}

void cleanup()
{
	glfwTerminate();
	free(screen);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		end = true;
	}

	if (!change_ack) {
		return;
	}

	switch (key) {
	case GLFW_KEY_A:
	case GLFW_KEY_LEFT:
		key_changed = LEFT;
		break;
	case GLFW_KEY_D:
	case GLFW_KEY_RIGHT:
		key_changed  = RIGHT;
		break;
	case GLFW_KEY_W:
	case GLFW_KEY_UP:
		key_changed  = UP;
		break;
	case GLFW_KEY_S:
	case GLFW_KEY_DOWN:
		key_changed  = DOWN;
		break;
	case GLFW_KEY_SPACE:
		key_changed  = SPACE;
		break;
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_RIGHT_CONTROL:
		key_changed  = CTRL;
		break;
	default:
		break;
	}

	key_pressed = (action == GLFW_PRESS);
	change_ack = false;
}

#endif
