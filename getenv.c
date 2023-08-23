#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/* Function to change the current directory and update environment variables */
void change_directory(const char *path) {
	if (chdir(path) != 0)
	{
	    perror("cd");  /* Print error message if chdir fails */
	} else {
	    char *cwd = getcwd(NULL, 0);  /* Get the current working directory */
	setenv("PWD", cwd, 1);  /* Update the PWD environment variable */
	free(cwd);  /* Free the memory allocated by getcwd */
    }
}
int main(int argc, char *argv[]) {
	/* Check if no arguments are provided */
	if (argc == 1)
	{
	    const char *home = getenv("HOME");  /* Get the home directory */
	change_directory(home);  /* Change to the home directory */
	}
    /* Check if the argument is "-" */
	else if (strcmp(argv[1], "-") == 0)
	{
		const char *previous = getenv("OLDPWD");  /* Get the previous working directory */
	change_directory(previous);  /* Change to the previou working directory */
	}
    /* Otherwise, change to the specified directory */
	else
	{
		change_directory(argv[1]);  /* Change to the specified directory */
	}
	return (0);
}
