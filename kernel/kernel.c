// @lakladon: Minimal shell implementation for RetOS
#include "printf.h"
#include <string.h>

// @lakladon: Shell configuration constants
#define MAX_CMD_LEN 128
#define MAX_ARGS 8

// @lakladon: Command buffer and position tracking
static char cmd_buffer[MAX_CMD_LEN];
static int cmd_pos = 0;

// @lakladon: Print the shell prompt
static void shell_print_prompt(void) {
    printf("\nretos> ");
}

// @lakladon: Clear the command buffer
static void shell_clear_buffer(void) {
    cmd_pos = 0;
    cmd_buffer[0] = '\0';
}

// @lakladon: Add a character to the command buffer
static void shell_add_char(char c) {
    if (cmd_pos < MAX_CMD_LEN - 1) {
        cmd_buffer[cmd_pos++] = c;
        cmd_buffer[cmd_pos] = '\0';
        vga_putc(c);
    }
}

// @lakladon: Handle backspace in command buffer
static void shell_backspace(void) {
    if (cmd_pos > 0) {
        cmd_pos--;
        cmd_buffer[cmd_pos] = '\0';
        printf("\b \b");
    }
}

// @lakladon: Tokenize command string into arguments
static int shell_tokenize(char* cmd, char** args) {
    int argc = 0;
    char* token = strtok(cmd, " ");
    
    while (token != NULL && argc < MAX_ARGS - 1) {
        args[argc++] = token;
        token = strtok(NULL, " ");
    }
    args[argc] = NULL;
    return argc;
}

// @lakladon: Execute shell commands
static void shell_execute_command(char** args, int argc) {
    if (argc == 0) return;
    
    if (strcmp(args[0], "help") == 0) {
        printf("\nAvailable commands:\n");
        printf("  help     - Show this help message\n");
        printf("  clear    - Clear the screen\n");
        printf("  echo     - Echo text\n");
        printf("  exit     - Exit shell\n");
    }
    else if (strcmp(args[0], "clear") == 0) {
        clear_screen();
    }
    else if (strcmp(args[0], "echo") == 0) {
        for (int i = 1; i < argc; i++) {
            printf("%s ", args[i]);
        }
        printf("\n");
    }
    else if (strcmp(args[0], "exit") == 0) {
        printf("\nGoodbye!\n");
        while(1); // Halt
    }
    else {
        printf("\nUnknown command: %s\n", args[0]);
        printf("Type 'help' for available commands.\n");
    }
}

// @lakladon: Main shell loop
static void shell_main_loop(void) {
    shell_print_prompt();
    
    while (1) {
        // Wait for keyboard input (simplified polling)
        // In a real implementation, this would use interrupts
        char c = 0;
        
        // Simple polling for demonstration
        // This is a placeholder - actual keyboard handling would be more complex
        for (volatile int i = 0; i < 100000; i++);
        
        // For now, simulate a simple command processor
        // In a real shell, this would read from keyboard buffer
        
        // This is a minimal implementation - normally you'd have proper
        // keyboard interrupt handling and input buffering
        printf("\nShell running (minimal implementation)\n");
        printf("Type 'help' for commands, 'exit' to quit\n");
        break; // Exit after one iteration for now
    }
}

// @lakladon: Main kernel entry point with shell
void kernel_main(void) {
    clear_screen();

    printf("*******************************\n");
    printf("             RETOS             \n");
    printf("        COPYRIGHT: ANDY        \n");
    printf("*******************************\n");
    
    printf("\nStarting minimal shell...\n");
    shell_main_loop();
}
