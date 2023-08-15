#include <stdio.h>           // Include standard input-output library
#include <stdlib.h>          // Include standard library
#include <string.h>          // Include string manipulation functions
#include <unistd.h>          // Include UNIX standard library
#include <sys/types.h>       // Include data types used in system calls
#include <sys/wait.h>        // Include wait-related functions

#define MAX_INPUT_LENGTH 1024  // Define a constant for maximum input length

void run_command(char *command) 
{
    pid_t pid;                 // Declare a variable to store process ID
    int status;                // Declare a variable to store process status

    pid = fork();              // Create a new process (child) using fork()

    if (pid == 0) // If this is the child process
    {
        char *args[] = {"/bin/sh", "-c", command, NULL}; // Command arguments

        execvp("/bin/sh", args);  // Replace the child process with the command
        perror("Exec failed");    // Print an error message if execvp fails
        exit(EXIT_FAILURE);       // Exit the child process with a failure status
    } 
    else if (pid < 0)  // If fork failed
    {  
        perror("Fork failed");   // Print an error message
    } 
    else // Parent process
    {
        waitpid(pid, &status, 0);  // Wait for the child process to complete
    }
}



int main() 
{
    char input[MAX_INPUT_LENGTH];  // Declare an array to store user input

    while (1) // Infinite loop for shell interaction
    {
        printf("$ ");               // Print the shell prompt
        fflush(stdout);             // Flush the standard output buffer

        if (fgets(input, sizeof(input), stdin) == NULL) 
	{
            break;                  // Break the loop if there's no more input
        }

        input[strcspn(input, "\n")] = '\0';  // Remove the newline character from the input

        if (strcmp(input, "exit") == 0) 
	{
            break;                  // Break the loop if the user types "exit"
        }

        run_command(input);         // Call the function to run the command
    }

    return 0;                      // Return 0 to indicate successful completion
}
