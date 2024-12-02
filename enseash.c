#include <unistd.h>
#include <string.h>

int main() {
    char command[128]; // Buffer for user command 

    // Definition of constants that are the messages we want to display
    const char *welcome_message = "Welcome to ENSEA Tiny Shell.\n";
    const char *exit_message = "Type 'exit' to quit.\n";
    const char *prompt = "enseash % ";


    // Display of the welcome message thanks to write(STDOUT_FILENO,...)
    write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
    write(STDOUT_FILENO, exit_message, strlen(exit_message));

    while (1) {
        // Display the prompt
        write(STDOUT_FILENO, prompt, strlen(prompt));

        // Reading of the command written by the user thanks to read(STDIN_FILENO,...)
        ssize_t n = read(STDIN_FILENO, command, sizeof(command) - 1);
        if (n <= 0) { // Erreur ou fin de fichier
            break;
        }

        // Remove the newline character from the command (to really get exit without the /n when we write exit )
        command[n - 1] = '\0';

        // Exit if user write "exit"
        if (strcmp(command, "exit") == 0) {
            break;
        }

      
    }


}
