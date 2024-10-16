#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// #define VIDEO_MEMORY (char*) 0xb8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define WHITE_ON_BLACK 0x07

char *VIDEO_MEMORY = (char*) 0xb8000;
void clear_screen() {
    for (int i = 0; i < SCREEN_WIDTH * 25 * 2; i += 2) {
        VIDEO_MEMORY[i] = ' ';
        VIDEO_MEMORY[i + 1] = WHITE_ON_BLACK;
    }
}

void print_at(const char *message, int x, int y) {
    int i = 0;
    while (message[i] != '\0') {
        int pos = ((y * SCREEN_WIDTH) + x + i) * 2;
        if (pos < SCREEN_WIDTH * 25 * 2) {
            VIDEO_MEMORY[pos] = message[i];
            VIDEO_MEMORY[pos + 1] = WHITE_ON_BLACK;
        }
        i++;
    }
}

void delay() {
    for (volatile int i = 0; i < 10000000; i++);
}

void kernel_main() {
    const char *ascii_art[] = {
        " __    __   ______         __         ______          ",
        "/  |  /  | /      \\       /  |       /      \\        ",
        "$$ |  $$ |/$$$$$$  |      $$ |   __ /$$$$$$  |_______ ",
        "$$ |__$$ |$$____$$ |      $$ |  /  |$$ |_ $$//       |",
        "$$    $$ | /    $$/       $$ |_/$$/ $$   |  /$$$$$$$/ ",
        "$$$$$$$$ |/$$$$$$/        $$   $$<  $$$$/   $$      \\ ",
        "      $$ |$$ |_____       $$$$$$  \\ $$ |     $$$$$$  |",
        "      $$ |$$       |      $$ | $$  |$$ |    /     $$/ ",
        "      $$/ $$$$$$$$/       $$/   $$/ $$/     $$$$$$$/  "
    };
    int num_lines = 9;
    int max_length = 58; // The longest line in ASCII art
    
    while (1) {
        for (int x = 0; x < SCREEN_WIDTH - max_length; x++) {
            clear_screen();
            for (int y = 0; y < num_lines; y++) {
                print_at(ascii_art[y], x, y);
            }
            delay();
        }
    }
}
