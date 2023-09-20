#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100                      // Define the maximum size of the stack

typedef struct {
    int stack[STACK_SIZE];                 // Define an array to store the stack elements
    int top;                              // Keep track of the top of the stack
} MontyStack;                              // Create a structure to represent the Monty stack





void push(MontyStack* stack, int value)
{
    if (stack->top < STACK_SIZE - 1)             // Check if the stack is not full
    {
        stack->top++;                          // Move the top of the stack up
        stack->stack[stack->top] = value;      // Push the value onto the stack
    } 
    else 
    {
        fprintf(stderr, "Error: Stack overflow\n");
        exit(EXIT_FAILURE);                     // Exit the program with an error message if the stack is full
    }
}






int pop(MontyStack* stack)                     // Check if the stack is not empty
{
    if (stack->top >= 0) 
    {
        int value = stack->stack[stack->top];  // Pop the value from the top of the stack
        stack->top--;                          // Move the top of the stack down
        return value;                          // Return the popped value
    } 
    else 
    {
        fprintf(stderr, "Error: Stack underflow\n");
        exit(EXIT_FAILURE);                  // Exit the program with an error message if the stack is empty
    }
}







void add(MontyStack* stack) 
{
    if (stack->top >= 1)                    // Check if there are at least two operands on the stack 
    {
        int a = pop(stack);  // Pop the top operand
        int b = pop(stack);  // Pop the next operand
        push(stack, a + b);  // Push the result of addition onto the stack
    } 
    else 
    {
        fprintf(stderr, "Error: Not enough operands for addition\n");
        exit(EXIT_FAILURE);                  // Exit the program with an error message if there are not enough operands
    }
}







void sub(MontyStack* stack) 
{
    if (stack->top >= 1)                     // Check if there are at least two operands on the stack 
    {
        
        int a = pop(stack);                 // Pop the top operand
        int b = pop(stack);                 // Pop the next operand
        push(stack, b - a);  // Push the result of subtraction onto the stack
    } 
    else 
    {
        fprintf(stderr, "Error: Not enough operands for subtraction\n");
        exit(EXIT_FAILURE);                  // Exit the program with an error message if there are not enough operands
    }
}






void execute(MontyStack* stack, const char* bytecode_file) 
{
    FILE* file = fopen(bytecode_file, "r");  // Open the Monty ByteCode file for reading
    if (!file) 
    {
        fprintf(stderr, "Error: Unable to open bytecode file\n");
        exit(EXIT_FAILURE);                  // Exit the program with an error message if the file cannot be opened
    }

    char line[256];                          // Create a buffer to read lines from the file
    while (fgets(line, sizeof(line), file)) 
    {
        if (line[0] == '\n' || line[0] == '#') 
        {
            continue;                      // Ignore empty lines and comments
        }

        char opcode[16];                      // Create a buffer to store the opcode (instruction)
        int arg;                              // Create a variable to store the argument (if any)
        sscanf(line, "%15s %d", opcode, &arg);  // Parse the line for opcode and argument

        if (strcmp(opcode, "push") == 0) 
        {
            push(stack, arg);                  // Execute the "push" operation with the argument
        } 
        else if (strcmp(opcode, "pop") == 0) 
        {
            pop(stack);                      // Execute the "pop" operation
        } 
        else if (strcmp(opcode, "add") == 0) 
        {
            add(stack);                      // Execute the "add" operation
        } 
        else if (strcmp(opcode, "sub") == 0) 
        {
            sub(stack);                      // Execute the "sub" operation
        } 
        else 
        {
            fprintf(stderr, "Error: Unknown opcode %s\n", opcode);
            exit(EXIT_FAILURE);              // Exit the program with an error message for unknown opcodes
        }
    }

    fclose(file);                            // Close the Monty ByteCode file
}





int main(int argc, char* argv[]) 
{
    if (argc != 2) 
    {
        fprintf(stderr, "Usage: %s <bytecode_file>\n", argv[0]);
        return EXIT_FAILURE;                // Exit the program with an error message if the command-line arguments are incorrect
    }

    MontyStack stack;
    stack.top = -1;                          // Initialize the stack with an empty state

    execute(&stack, argv[1]);              // Execute the Monty ByteCode instructions

    int result = pop(&stack);              // Pop the final result from the stack
    printf("Result: %d\n", result);        // Print the result

    return EXIT_SUCCESS;                  // Exit the program successfully
}
