%{
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int yylex();
void yyerror(const char *s);
%}

/* Token Definitions */
%token NUMBER ID

/* Operator Precedence and Associativity */
%left '+' '-'
%left '*' '/'

/* Grammar Rules Section */
%%
statement:
    expression '\n' { 
        printf("\nResult: Valid Syntax!\n"); 
        exit(0); 
    }
    ;

expression:
      expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | '(' expression ')'
    | NUMBER
    | ID
    ;
%%

/* User Subroutines Section */
void yyerror(const char *s) {
    printf("\nResult: Invalid Syntax!\n");
    exit(1);
}

int main() {
    printf("Enter an arithmetic expression to parse:\n");
    // Start the parsing process
    yyparse();
    return 0;
}