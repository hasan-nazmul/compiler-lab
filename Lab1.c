#include <stdio.h>

int main() {
    // State Definitions
    // 0: Normal code
    // 1: Single-line comment
    // 2: Multi-line comment
    // 3: Inside a string literal
    int state = 0; 
    int c, next_c;

    while ((c = getchar()) != EOF) {
        if (state == 0) {
            // Normal code state
            if (c == '/') {
                next_c = getchar();
                if (next_c == '/') {
                    state = 1; // Enter single-line comment
                } else if (next_c == '*') {
                    state = 2; // Enter multi-line comment
                } else {
                    putchar(c);
                    if (next_c != EOF) ungetc(next_c, stdin);
                }
            } else if (c == '"') {
                state = 3; // Enter string literal
                putchar(c);
            } else {
                putchar(c);
            }
        } 
        else if (state == 1) {
            // Single-line comment state
            if (c == '\n') {
                state = 0; // Exit single-line comment
                putchar(c);
            }
        } 
        else if (state == 2) {
            // Multi-line comment state
            if (c == '*') {
                next_c = getchar();
                if (next_c == '/') {
                    state = 0; // Exit multi-line comment
                } else {
                    if (next_c != EOF) ungetc(next_c, stdin);
                }
            }
        } 
        else if (state == 3) {
            // String literal state
            putchar(c);
            if (c == '\\') {
                // Handle escaped characters inside strings (e.g., \")
                next_c = getchar();
                if (next_c != EOF) putchar(next_c);
            } else if (c == '"') {
                state = 0; // Exit string literal
            }
        }
    }
    return 0;
}