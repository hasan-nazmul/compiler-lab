#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Function to check if a string is a C keyword
bool isKeyword(const char* str) {
    const char* keywords[] = {
        "int", "float", "char", "double", "if", "else", "while", 
        "do", "for", "return", "void", "main", "include"
    };
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to check if a character is an operator
bool isOperator(char ch) {
    char operators[] = "+-*/=<>!&|";
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i]) return true;
    }
    return false;
}

// Function to check if a character is a special symbol
bool isSpecialSymbol(char ch) {
    char symbols[] = "(){}[],;:";
    for (int i = 0; i < strlen(symbols); i++) {
        if (ch == symbols[i]) return true;
    }
    return false;
}

// Main tokenizer function
void tokenize(const char* str) {
    int i = 0;
    int len = strlen(str);
    char buffer[100];
    int bufIndex = 0;

    printf("\n%-20s %-20s\n", "LEXEME", "TOKEN TYPE");
    printf("-----------------------------------------\n");

    while (i < len) {
        // Skip whitespaces
        if (isspace(str[i])) {
            i++;
            continue;
        }

        // Check for Identifiers or Keywords
        if (isalpha(str[i]) || str[i] == '_') {
            bufIndex = 0;
            while (isalnum(str[i]) || str[i] == '_') {
                buffer[bufIndex++] = str[i++];
            }
            buffer[bufIndex] = '\0'; // Null terminate the string

            if (isKeyword(buffer)) {
                printf("%-20s %-20s\n", buffer, "Keyword");
            } else {
                printf("%-20s %-20s\n", buffer, "Identifier");
            }
            continue;
        }

        // Check for Constants (Numbers)
        if (isdigit(str[i])) {
            bufIndex = 0;
            while (isdigit(str[i]) || str[i] == '.') {
                buffer[bufIndex++] = str[i++];
            }
            buffer[bufIndex] = '\0';
            printf("%-20s %-20s\n", buffer, "Constant");
            continue;
        }

        // Check for Operators
        if (isOperator(str[i])) {
            printf("%-20c %-20s\n", str[i], "Operator");
            i++;
            continue;
        }

        // Check for Special Symbols (Punctuation)
        if (isSpecialSymbol(str[i])) {
            printf("%-20c %-20s\n", str[i], "Special Symbol");
            i++;
            continue;
        }

        // Unrecognized character
        printf("%-20c %-20s\n", str[i], "Unrecognized");
        i++;
    }
}

int main() {
    char sourceCode[256];

    printf("Enter a C statement to tokenize: ");
    if (fgets(sourceCode, sizeof(sourceCode), stdin) != NULL) {
        // Remove trailing newline character left by fgets
        sourceCode[strcspn(sourceCode, "\n")] = '\0';
        tokenize(sourceCode);
    }

    return 0;
}