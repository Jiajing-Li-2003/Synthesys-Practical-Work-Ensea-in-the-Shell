#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	
    char command[128]; // Buffer for user command 
    char prompt[128];  // Buffer for the dynamic prompt
    int last_status = 0; // Variable to store the status of the last command

    // Definition of constants that are the messages we want to display
    const char *welcome_message = "Welcome to ENSEA Tiny Shell.\n";
    const char *exit_message = "Type 'exit' to quit.\n";
    const char *prompt_message = "enseash % ";
    const char *goodbye_message="Bye Bye.\n";
    const char *prompt_exit_code= "enseash [exit:%d|%dms] %% ";
	const char *prompt_signal_code= "enseash [sign:%d|%dms] %% ";


    // Display of the welcome message thanks to write(STDOUT_FILENO,...)
    write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
    write(STDOUT_FILENO, exit_message, strlen(exit_message));

    while (1)
	 {
		  // Update the prompt based on the last status
        if (WIFEXITED(last_status)) {
            // If the last command exited normally, use the exit code
            snprintf(prompt, sizeof(prompt), prompt_exit_code, WEXITSTATUS(last_status));
        } 
        else if (WIFSIGNALED(last_status)) {
            // If the last command was terminated by a signal, use the signal number
            snprintf(prompt, sizeof(prompt), prompt_signal_code, WTERMSIG(last_status));
        } 
        else {
            // Default prompt if no command has been executed yet
            strncpy(prompt, prompt_message, sizeof(prompt));
        }
	
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
		
	 // Measure the start time
       struct timespec start_time, end_time;
       clock_gettime(CLOCK_MONOTONIC, &start_time);
        
        
	// Create a child process to execute the command
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
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
            
            // Measure the end time
            clock_gettime(CLOCK_MONOTONIC, &end_time);

            // Calculate the elapsed time in milliseconds
            long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000 + ((end_time.tv_nsec - start_time.tv_nsec) / 1000000);
           
            // Save the child's status for use in the next prompt
            last_status = status;
            
            // Update the prompt to include the exit code or signal and execution time
            if (WIFEXITED(last_status)) {
                snprintf(prompt, sizeof(prompt), prompt_exit_code, WEXITSTATUS(last_status), (long)elapsed_time);
            } 
            else if (WIFSIGNALED(last_status)) {
                snprintf(prompt, sizeof(prompt), prompt_signal_code, WTERMSIG(last_status), (long)elapsed_time);
            }
        }

    }
	//Good bye message when we exit
	write(STDOUT_FILENO, goodbye_message, strlen(goodbye_message));
	return 0;
}
