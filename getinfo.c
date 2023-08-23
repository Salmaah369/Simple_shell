#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* This program allows the user to enter multiple commands separated by semicolons (;) */
/* Each command is executed sequentially, and the program waits for each command to finish before proceeding to the next one. */

int main(){
	char input[100];
	char *command;
    /* Enter the main loop that repeatedly prompts the user for input */
	while (1)
    {
	    printf("Enter a command: ");
	fgets(input, sizeof(input), stdin);
	/* Remove the trailing newline character from the input */
	input[strcspn(input, "\n")] = '\0';
	/* Split the input into separate commands using the semicolon delimiter (;) */
	command = strtok(input, ";");
	/* Process each command */
	while (command != NULL)
	{
		/* Create a child process to execute the command */
		int pid = fork();
	if (pid == 0)
	{
		    /* Child process */

		    /* Tokenize the command into individual arguments */
		    char *args[10];
		char *arg;
		int i = 0;
		/* Split the command using the space delimiter (" ") */
		arg = strtok(command, " ");
		while (arg != NULL)
		{
			args[i] = arg;
		    i++;
			    arg = strtok(NULL, " ");
		}
		args[i] = NULL;

		/* Execute the command in the child process */
		execvp(args[0], args);
		exit(0);
	} else if (pid > 0)
	{
		    /* Parent process */

		    /* Wait for the child process to finish execution */
		    wait(NULL);
	} else
	{
		    /* Fork failed */
		    perror("fork");
		exit(1);
	}

	    /* Move to the next command */
	    command = strtok(NULL, ";");
	}
    }
return 0;
}
