#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 100  // Define the maximum size for the stack and expressions

// Stack to hold characters during the conversion
char stack[MAX];
int top = -1;  // Top of the stack

// Function to push a character onto the stack
void push(char ch) {
    if (top >= MAX - 1) {  // Check for stack overflow
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = ch;  // Add the character to the stack
}

// Function to pop a character from the stack
char pop() {
    if (top == -1) {  // Check for stack underflow
        printf("Stack underflow\n");
        return '\0';  // Return null character if stack is empty
    }
    return stack[top--];  // Return the top element and decrement the top index
}

// Function to peek (view) the top element of the stack without removing it
char peek() {
    if (top == -1) return '\0';  // Return null if stack is empty
    return stack[top];  // Return the top element
}

// Function to check the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;  // Lowest precedence
    if (op == '*' || op == '/') return 2;  // Higher precedence
    if (op == '^') return 3;  // Highest precedence
    return 0;  // Return 0 for non-operators
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to convert an infix expression to a prefix expression
void infixToPrefix(char* infix, char* prefix) {
    int len = strlen(infix);  // Get the length of the infix expression
    char reversed[MAX], temp[MAX];  // Temporary arrays to hold reversed and intermediate results
    int k = 0;  // Index for the intermediate result

    // Step 1: Reverse the infix expression and adjust parentheses
    for (int i = 0; i < len; i++) {
        if (infix[len - i - 1] == '(')
            reversed[i] = ')';  // Change '(' to ')'
        else if (infix[len - i - 1] == ')')
            reversed[i] = '(';  // Change ')' to '('
        else
            reversed[i] = infix[len - i - 1];  // Copy other characters as is
    }
    reversed[len] = '\0';  // Null-terminate the reversed expression

    // Step 2: Process the reversed infix expression
    for (int i = 0; i < len; i++) {
        char ch = reversed[i];

        if (isalnum(ch)) {  // If the character is an operand (number or variable)
            temp[k++] = ch;  // Add it directly to the result
        } else if (ch == '(') {  // If the character is a left parenthesis
            push(ch);  // Push it onto the stack
        } else if (ch == ')') {  // If the character is a right parenthesis
            // Pop from the stack until a left parenthesis is encountered
            while (top != -1 && peek() != '(') {
                temp[k++] = pop();
            }
            pop();  // Remove the left parenthesis from the stack
        } else if (isOperator(ch)) {  // If the character is an operator
            // Pop operators with higher or equal precedence from the stack
            while (top != -1 && precedence(peek()) >= precedence(ch)) {
                temp[k++] = pop();
            }
            push(ch);  // Push the current operator onto the stack
        }
    }

    // Step 3: Pop any remaining operators from the stack
    while (top != -1) {
        temp[k++] = pop();
    }
    temp[k] = '\0';  // Null-terminate the intermediate result

    // Step 4: Reverse the intermediate result to get the prefix expression
    for (int i = 0; i < k; i++) {
        prefix[i] = temp[k - i - 1];
    }
    prefix[k] = '\0';  // Null-terminate the prefix expression
}

int main() {
    char infix[MAX], prefix[MAX];

    // Input the infix expression from the user
    printf("Enter infix notation: ");
    scanf("%[^\n]%*c", infix);  // Read input including spaces

    printf("Infix notation: %s\n", infix);  // Display the original infix expression

    // Convert the infix expression to prefix and display the result
    infixToPrefix(infix, prefix);
    printf("Prefix notation: %s\n", prefix);  // Display the resulting prefix expression

    return 0;
}

