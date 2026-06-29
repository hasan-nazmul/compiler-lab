#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Global variables for simplicity
int count, n = 0;
char calc_first[10], calc_follow[10];
int m = 0;
char production[10][10];

// Function prototypes
void find_first(char c);
void find_follow(char c);
void add_to_result(char result[], char val);

int main() {
    int i;
    char c;
    
    printf("Enter the number of productions: ");
    scanf("%d", &count);
    
    printf("Enter the productions (e.g., S=AB, use '#' for epsilon):\n");
    for (i = 0; i < count; i++) {
        scanf("%s", production[i]);
    }
    
    // Find FIRST and FOLLOW for each Non-Terminal
    for (i = 0; i < count; i++) {
        c = production[i][0];
        
        // Reset output arrays
        memset(calc_first, '\0', sizeof(calc_first));
        memset(calc_follow, '\0', sizeof(calc_follow));
        n = 0; 
        m = 0;
        
        // Calculate FIRST
        find_first(c);
        printf("FIRST(%c) = { ", c);
        for (int j = 0; j < n; j++) printf("%c ", calc_first[j]);
        printf("}\n");
        
        // Calculate FOLLOW
        find_follow(c);
        printf("FOLLOW(%c) = { ", c);
        for (int j = 0; j < m; j++) printf("%c ", calc_follow[j]);
        printf("}\n\n");
    }
    
    return 0;
}

// Helper to avoid duplicate characters in the sets
void add_to_result(char result[], char val) {
    int k;
    int len = strlen(result);
    for (k = 0; k < len; k++) {
        if (result[k] == val) return; // Already exists
    }
    result[len] = val;
    result[len + 1] = '\0';
}

void find_first(char c) {
    int j;
    // If it's a terminal or epsilon (#), it is its own FIRST
    if (!(isupper(c))) {
        add_to_result(calc_first, c);
        n++;
        return;
    }
    
    // Look through all productions to find rules for non-terminal 'c'
    for (j = 0; j < count; j++) {
        if (production[j][0] == c) {
            if (production[j][2] == '#') {
                // If it derives epsilon, add epsilon to FIRST
                add_to_result(calc_first, '#');
                n++;
            } else if (islower(production[j][2])) {
                // If the right side starts with a terminal, add it
                add_to_result(calc_first, production[j][2]);
                n++;
            } else {
                // If the right side starts with a Non-Terminal, recurse
                find_first(production[j][2]);
            }
        }
    }
}

void find_follow(char c) {
    int i, j;
    
    // Rule 1: Place '$' in FOLLOW of the start symbol
    if (production[0][0] == c) {
        add_to_result(calc_follow, '$');
        m++;
    }
    
    // Look through all right-hand sides of all productions
    for (i = 0; i < count; i++) {
        for (j = 2; j < strlen(production[i]); j++) {
            if (production[i][j] == c) {
                // If 'c' is the last symbol, apply Rule 3 (FOLLOW of LHS)
                if (production[i][j+1] == '\0' && c != production[i][0]) {
                    find_follow(production[i][0]);
                } 
                // Rule 2: If there is a symbol after 'c'
                else if (production[i][j+1] != '\0') {
                    // If the next symbol is a terminal, add it to FOLLOW
                    if (!isupper(production[i][j+1])) {
                        add_to_result(calc_follow, production[i][j+1]);
                        m++;
                    } else {
                        // If the next symbol is a Non-Terminal, find its FIRST
                        char temp_first[10];
                        memset(temp_first, '\0', sizeof(temp_first));
                        
                        // Temporarily store global calc_first state
                        char backup_first[10];
                        strcpy(backup_first, calc_first);
                        memset(calc_first, '\0', sizeof(calc_first));
                        n = 0;
                        
                        find_first(production[i][j+1]);
                        
                        // Add FIRST of next symbol to FOLLOW of c (excluding epsilon)
                        int has_epsilon = 0;
                        for (int k = 0; k < strlen(calc_first); k++) {
                            if (calc_first[k] == '#') {
                                has_epsilon = 1;
                            } else {
                                add_to_result(calc_follow, calc_first[k]);
                                m++;
                            }
                        }
                        
                        // Restore FIRST array
                        strcpy(calc_first, backup_first);
                        n = strlen(calc_first);
                        
                        // If FIRST of the next symbol had epsilon, apply Rule 3
                        if (has_epsilon && c != production[i][0]) {
                            find_follow(production[i][0]);
                        }
                    }
                }
            }
        }
    }
}