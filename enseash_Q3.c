#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[128]; // Buffer for user command 

    // Definition of constants that are the messages we want to display
    const char *welcome_message = "Welcome to ENSEA Tiny Shell.\n";
    const char *exit_message = "Type 'exit' to quit.\n";
    const char *prompt = "enseash % ";
    const char *goodbye_message="Bye Bye.\n";


    // Display of the welcome message thanks to write(STDOUT_FILENO,...)
    write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
    write(STDOUT_FILENO, exit_message, strlen(exit_message));

    while (1)
	 {
	
        // Display the prompt
        write(STDOUT_FILENO, prompt, strlen(prompt));
   	
	 // Reading of the command written by the user thanks to read(STDIN_FILENO,...)
        ssize_t n = read(STDIN_FILENO, command, sizeof(command) - 1);

        // Handle Ctrl+D or error
        if (n == 0 || n == -1) {
            
            break;
        }

        // Remove the newline character from the command (to really get exit without the /n when we write exit )
        command[n - 1] = '\0';

        // Exit if user write "exit"
        if (strcmp(command, "exit") == 0) {
		
            break;
		}
	// Create a child process to execute the command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            continue;
        }
	if (pid == 0) {
            // Code for the child process 
            execlp(command, command, NULL);
            // If execlp fails (if the command isn't installed)
            perror("execlp");
            exit(EXIT_FAILURE);
       		 } 
        else {
            // Code for the parent process
            int status;
            wait(&status); // Wait for the child process to finish
        	}

       	}
	//Good bye message when we exit
	write(STDOUT_FILENO, goodbye_message, strlen(goodbye_message));
	return 0;
}