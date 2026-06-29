#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Function to check if the given string is a valid number
bool isNumber(const char* str) {
    int len = strlen(str);
    int decimalCount = 0;
    
    if (len == 0) return false;

    for (int i = 0; i < len; i++) {
        // Allow optional + or - at the very beginning
        if (i == 0 && (str[i] == '+' || str[i] == '-')) {
            if (len == 1) return false; // "+" or "-" alone is not a number
            continue;
        }
        
        if (str[i] == '.') {
            decimalCount++;
            if (decimalCount > 1) return false; // More than one decimal point
        } else if (!isdigit(str[i])) {
            return false; // Contains a non-digit character
        }
    }
    return true;
}

// Function to check if the given string is a valid C identifier
bool isIdentifier(const char* str) {
    int len = strlen(str);
    
    if (len == 0) return false;

    // Rule 1: First character must be a letter or underscore
    if (!isalpha(str[0]) && str[0] != '_') {
        return false;
    }

    // Rule 2: Subsequent characters must be alphanumeric or underscore
    for (int i = 1; i < len; i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return false;
        }
    }
    return true;
}

int main() {
    char input[100];

    printf("Enter a string to check: ");
    // Read input, preventing buffer overflow and removing the newline character
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0; 
        
        if (strlen(input) == 0) {
            printf("Empty input.\n");
        } else if (isNumber(input)) {
            printf("\"%s\" is a valid NUMBER.\n", input);
        } else if (isIdentifier(input)) {
            printf("\"%s\" is a valid IDENTIFIER.\n", input);
        } else {
            printf("\"%s\" is NEITHER a valid identifier nor a valid number.\n", input);
        }
    }

    return 0;
}