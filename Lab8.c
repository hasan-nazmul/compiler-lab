#include <stdio.h>
#include <string.h>

int main() {
    char prod[100];
    char part1[50], part2[50];
    char prefix[50], beta1[50], beta2[50];
    char non_terminal;
    int i, j = 0, k = 0, split_idx = 0;

    printf("Enter the production (e.g., S->iEtS|iEtSeA): ");
    scanf("%s", prod);

    // The left-hand side non-terminal is always the first character
    non_terminal = prod[0];

    // 1. Find the '|' to split the RHS into part1 and part2
    for (i = 3; prod[i] != '\0'; i++) {
        if (prod[i] == '|') {
            split_idx = i;
            break;
        }
    }

    if (split_idx == 0) {
        printf("Error: No alternative production found (missing '|').\n");
        return 1;
    }

    // 2. Extract part1 (from index 3 up to the '|')
    for (i = 3; i < split_idx; i++) {
        part1[j++] = prod[i];
    }
    part1[j] = '\0';

    // 3. Extract part2 (from after '|' to the end of the string)
    for (i = split_idx + 1; prod[i] != '\0'; i++) {
        part2[k++] = prod[i];
    }
    part2[k] = '\0';

    // 4. Find the common prefix (Alpha)
    i = 0;
    while (part1[i] == part2[i] && part1[i] != '\0' && part2[i] != '\0') {
        prefix[i] = part1[i];
        i++;
    }
    prefix[i] = '\0';

    // Check if a common prefix actually exists
    if (i == 0) {
        printf("\nResult: No common prefix found. Left factoring not required.\n");
        return 0;
    }

    // 5. Extract Beta 1 (the remainder of part1)
    j = 0;
    for (k = i; part1[k] != '\0'; k++) {
        beta1[j++] = part1[k];
    }
    beta1[j] = '\0';
    // If nothing is left, beta1 is epsilon (#)
    if (strlen(beta1) == 0) strcpy(beta1, "#"); 

    // 6. Extract Beta 2 (the remainder of part2)
    j = 0;
    for (k = i; part2[k] != '\0'; k++) {
        beta2[j++] = part2[k];
    }
    beta2[j] = '\0';
    // If nothing is left, beta2 is epsilon (#)
    if (strlen(beta2) == 0) strcpy(beta2, "#");

    // 7. Print the transformed productions
    printf("\nResult: Left factoring required.\n");
    printf("Grammar after left factoring:\n");
    
    // Rule 1: A -> alpha A'
    printf("%c -> %s%c'\n", non_terminal, prefix, non_terminal);
    
    // Rule 2: A' -> beta1 | beta2
    printf("%c' -> %s | %s\n", non_terminal, beta1, beta2);

    return 0;
}