#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

#define N 100 // Maximum length for input command
#define K 1000 // Maximum length for path

void main() {
    char sh[N], pathcopy[N];    // Arrays to store input command and path copy
    char* path;                 // Pointer to store system PATH
    int pid, stat;              // Variables for process ID and status
    path = getenv("PATH");      // Get the system PATH environment variable
    strcpy(pathcopy, path);     // Copy the PATH to pathcopy to avoid modifying the original PATH
    while (1) 
    {
        printf("Enter command: > ");    // Prompt user for command
        fgets(sh, N-1, stdin);          // Read command from standard input
        sh[strlen(sh)-1] = '\0';        // Remove newline character from input

        // If the command is "leave", exit the shell
        if (strcmp(sh, "leave") == 0) 
        {
            exit(0);
        }

        // Create a new process using fork
        if ((pid = fork()) == 0) 
        {
            char* params[N] = {NULL};   // Array to store command parameters
            char* token;                // Pointer for tokenizing the input
            char run[K];                // Array to store the executable path

            // Tokenize the input command and store each part in params array
            token = strtok(sh, " ");
            int i = 0;
            while (token) 
            {
                params[i++] = token;
                token = strtok(NULL, " ");
            }

             // Tokenize the PATH and search for the command executable
            token = strtok(pathcopy, ":");
            while (token) 
            {
                run[0] = '\0';          // Reset the run array
                strcat(run, token);     // Append the path token
                strcat(run, "/");
                strcat(run, params[0]); // Append the command name

                // Check if the executable is accessible and run it
                if (access(run, X_OK) == 0) 
                {
                    execv(run, params);
                }
                token = strtok(NULL, ":");
            }

            // If the command is not found, print an error message
            printf("Error while running: %s\n", sh);
            exit(1);
        } 
        else 
        {
            wait(&stat);    // Parent process waits for the child to finish
        }
    }
}
