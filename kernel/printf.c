
#include "printf.h"
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

// @lakladon: VGA text mode constants
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// @lakladon: VGA memory address
static volatile unsigned char* const VGA_MEMORY =
    (volatile unsigned char*)0xB8000;

// @lakladon: Cursor position variables
static int cursor_x = 0;
static int cursor_y = 0;
static char color = 0x0F; // white on black

// @lakladon: Put a character to VGA memory
void vga_putc(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    int index = (cursor_y * VGA_WIDTH + cursor_x) * 2;
    VGA_MEMORY[index] = c;
    VGA_MEMORY[index + 1] = color;

    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
}

// @lakladon: Clear the entire screen
void clear_screen(void) {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            int i = (y * VGA_WIDTH + x) * 2;
            VGA_MEMORY[i] = ' ';
            VGA_MEMORY[i + 1] = color;
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

// @lakladon: Print decimal number to screen
static void print_dec(int num) {
    if (num == 0) {
        vga_putc('0');
        return;
    }

    char buf[16];
    int i = 0;

    while (num > 0) {
        buf[i++] = '0' + (num % 10);
        num /= 10;
    }

    for (int j = i - 1; j >= 0; j--) {
        vga_putc(buf[j]);
    }
}

// @lakladon: String comparison function
int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// @lakladon: String tokenization function
char* strtok(char* str, const char* delimiters) {
    static char* next_token = NULL;
    char* token;
    
    if (str != NULL) {
        next_token = str;
    }
    
    if (next_token == NULL || *next_token == '\0') {
        return NULL;
    }
    
    // Skip leading delimiters
    while (*next_token && strchr(delimiters, *next_token)) {
        next_token++;
    }
    
    if (*next_token == '\0') {
        return NULL;
    }
    
    token = next_token;
    
    // Find the end of the token
    while (*next_token && !strchr(delimiters, *next_token)) {
        next_token++;
    }
    
    // Replace delimiter with null terminator and move past it
    if (*next_token) {
        *next_token = '\0';
        next_token++;
    }
    
    return token;
}

// @lakladon: Find character in string
char* strchr(const char* str, int c) {
    while (*str != (char)c) {
        if (*str == '\0') {
            return NULL;
        }
        str++;
    }
    return (char*)str;
}

// @lakladon: Formatted print function
void printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    for (int i = 0; fmt[i]; i++) {
        if (fmt[i] == '%' && fmt[i + 1]) {
            i++;
            if (fmt[i] == 'd') {
                int val = va_arg(args, int);
                print_dec(val);
            } else if (fmt[i] == 's') {
                char* str = va_arg(args, char*);
                while (*str) vga_putc(*str++);
            }
        } else {
            vga_putc(fmt[i]);
        }
    }

    va_end(args);
}
