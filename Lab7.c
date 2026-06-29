#include <stdio.h>
#include <string.h>

int main() {
    char prod[100], alpha[50], beta[50];
    int i, j, k;
    char non_terminal;

    printf("Enter the production (e.g., E->E+T|T): ");
    scanf("%s", prod);

    // The left-hand side non-terminal is always the first character
    non_terminal = prod[0];

    // Check for direct left recursion
    // prod[0] is LHS, prod[1] is '-', prod[2] is '>', prod[3] is first char of RHS
    if (prod[3] == non_terminal) {
        printf("\nResult: Left recursion detected.\n");

        // 1. Extract Alpha (everything after 'A->A' up to the '|')
        i = 4; // Start index of alpha
        j = 0;
        while (prod[i] != '|' && prod[i] != '\0') {
            alpha[j++] = prod[i++];
        }
        alpha[j] = '\0'; // Null-terminate the alpha string

        // 2. Extract Beta (everything after the '|')
        if (prod[i] == '|') {
            i++; // Move past the '|' character
            k = 0;
            while (prod[i] != '\0') {
                beta[k++] = prod[i++];
            }
            beta[k] = '\0'; // Null-terminate the beta string

            // 3. Print the transformed productions
            printf("Grammar without left recursion:\n");
            // Rule 1: A -> beta A'
            printf("%c -> %s%c'\n", non_terminal, beta, non_terminal);
            // Rule 2: A' -> alpha A' | #
            printf("%c' -> %s%c' | #\n", non_terminal, alpha, non_terminal);
            
        } else {
            // If there is no '|', the grammar is invalid or missing a base case
            printf("Error: No beta sequence found (missing '|').\n");
        }
    } else {
        printf("\nResult: The grammar is not left recursive.\n");
    }

    return 0;
}