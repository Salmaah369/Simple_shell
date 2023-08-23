/*
 *  Pseudocode
 *  Step 1: Define supported commands
 *  - setenv: to set a new environment variable
* - unsetenv: to remove an environment variable
*
* Step 2: Execute the built-in command setenv
* - Check command requirements (input size, correct format)
* - Use the setenv function to set the environment variable
*
* Step 3: Execute the built-in command unsetenv
* - Check command requirements (input size, correct format)
* - Use the unsetenv function to remove the environment variable
*
* Step 4: Execute non-built-in commands
* - Create a child process using fork
* - In the child process:
*   - Use execvp to execute the non-built-in command
*   - If execution fails, print an error message
* - In the parent process:
*   - Use waitpid to wait for the child process to finish
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/* Execute the built-in commands setenv and unsetenv */
int execute_command(char** args) {
	if (args[0] == NULL) {
		/* Empty command, nothing to execute */
		return 1;
	}
	if (strcmp(args[0], "setenv") == 0) {
	/* Execute the built-in command setenv */ 
		if(args[1] == NULL || args[2] == NULL) {
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	    return 1;
	}

	if (setenv(args[1], args[2], 1) != 0) {
		perror("setenv");
	}
	return 1;
	} else if (strcmp(args[0], "unsetenv") == 0) {
	    /* Execute the built-in command unsetenv */
	    if (args[1] == NULL) {
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	    return 1;
	}

	if (unsetenv(args[1]) != 0) {
		perror("unsetenv");
	}
	return 1;
    }

	/* Non-built-in command, execute using execvp() */
	pid_t pid = fork();
    
    if (pid == 0) {
	    /* Child process */
	    if (execvp(args[0], args) == -1) {
		perror("execvp");
	}
	exit(EXIT_FAILURE);
    } else if (pid < 0) {
	    /* Failed to create process */
	    perror("fork");
    } else {
	    /* Parent process */
	    waitpid(pid, NULL, 0);
	}
    
	return 1;
}
