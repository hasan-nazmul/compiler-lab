%{
// Definitions Section
#include <stdio.h>
%}

/* Rules Section */
%%
"int"|"float"|"char"|"double"|"if"|"else"|"while"|"do"|"for"|"return"|"void"|"main" { 
    printf("%-20s %-20s\n", yytext, "Keyword"); 
}

[a-zA-Z_][a-zA-Z0-9_]* { 
    printf("%-20s %-20s\n", yytext, "Identifier"); 
}

[0-9]+(\.[0-9]+)? { 
    printf("%-20s %-20s\n", yytext, "Constant"); 
}

"+"|"-"|"*"|"/"|"="|"<"|">"|"!"|"&"|"|" { 
    printf("%-20s %-20s\n", yytext, "Operator"); 
}

"("|")"|"{"|"}"|"["|"]"|";"|"," { 
    printf("%-20s %-20s\n", yytext, "Special Symbol"); 
}

[ \t\n]+ { 
    /* Ignore spaces, tabs, and newlines */ 
}

. { 
    printf("%-20s %-20s\n", yytext, "Unrecognized"); 
}
%%

/* User Subroutines Section */
int yywrap() {
    // Returns 1 to indicate the end of input
    return 1;
}

int main() {
    printf("Enter C code to tokenize (Press Ctrl+D to stop):\n");
    printf("\n%-20s %-20s\n", "LEXEME", "TOKEN TYPE");
    printf("-----------------------------------------\n");
    
    // yylex() starts the lexical analysis process
    yylex();
    
    return 0;
}