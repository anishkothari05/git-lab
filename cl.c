#include <stdio.h>
#include <string.h>

// Function to return precedence of operator on the stack
int stack_precedence(char symbol) {
    switch (symbol) {
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 4;
        case '^':
        case '$': return 5;
        case '(': return 0;
        case '#': return -1;
        default: return 8; // Operand precedence
    }
}

// Function to return precedence of incoming operator
int incoming_precedence(char symbol) {
    switch (symbol) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 3;
        case '^':
        case '$': return 6;
        case '(': return 9; // High precedence to push '(' onto the stack
        case ')': return 0; // Special precedence for ')'
        default: return 7;  // Operand precedence
    }
}

// Function to convert infix expression to postfix
void infix_to_postfix(char infix[], char postfix[]) {
    int top = -1, j = 0, i;
    char stack[30]; 
    char symbol;

    stack[++top] = '#';  // Initialize stack with end symbol
    
    // Loop through each character in the infix expression
    for (i = 0; i < strlen(infix); i++) {
        symbol = infix[i];

        // Pop from stack to postfix until incoming operator has higher precedence
        while (stack_precedence(stack[top]) > incoming_precedence(symbol)) {
            postfix[j++] = stack[top--]; // Pop and add to postfix
        }

        // If symbol is not equal to the precedence of stack's top
        if (stack_precedence(stack[top]) != incoming_precedence(symbol)) {
            stack[++top] = symbol; // Push operator onto stack
        } else {
            top--; // Pop '(' for matching ')'
        }
    }

    // Pop all remaining operators from the stack
    while (stack[top] != '#') {
        postfix[j++] = stack[top--]; // Pop and add to postfix
    }

    postfix[j] = '\0'; // Null-terminate the postfix string
}

int main() {
    char infix[30], postfix[30];
    
    // Input infix expression
    printf("Enter infix expression: ");
    scanf("%s", infix);

    // Convert to postfix
    infix_to_postfix(infix, postfix);

    // Output postfix expression
    printf("Postfix expression: %s\n", postfix);

    return 0;
}
