#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int execute_command(char *command)
{
    int pid = fork();

    if (pid == 0)
    {
        /* Child process */
        execlp(command, command, NULL);
        exit(0);
    } else if (pid > 0)
    {
        /* Parent process */
        int status;
        wait(&status);
        return WEXITSTATUS(status);
    } else
    {
        /* Fork failed */
        perror("fork");
        exit(1);
    }
}

int main(){
    char input[100];
    char *command;

    while (1)
    {
        printf("Enter a command: ");
        fgets(input, sizeof(input), stdin);

        /* Remove trailing newline character */
        input[strcspn(input, "\n")] = '\0';

        /* Split commands using ";" */
        command = strtok(input, ";");

        while (command != NULL)
        {
            /* Split command using "&&" or "||" */
            char *subcommand = strtok(command, "&&||");
/* Previous command exit status */
            int prev_status = 0; 

            while (subcommand != NULL)
            {
                /* Execute subcommand */
                int status = execute_command(subcommand);

                /* Check if subcommand contains "&&" or "||" */
                char *operator = strchr(subcommand, '&');

                if (operator != NULL && *(operator + 1) == '&')
                {
                    /* "&&" operator */
                    if (prev_status == 0 && status == 0)
                    {
                        /* Previous command succeeded and current command succeeded */
                        prev_status = 0;
                    } else
                    {
                        /* Previous command failed or current */ command failed
                        prev_status = 1;
                        break;
                    }
                } else if (operator != NULL && *(operator + 1) == '|')
                {
                    /* "||" operator */
                    if (prev_status != 0 && status != 0)
                    {
                        /* Previous command failed and current command failed */
                        prev_status = 1;
                    } else
                    {
                        /* Previous command succeeded or current command succeeded */
                        prev_status = 0;
                        break;
                    }
                } else
                {
                    /* No operator, single command */
                    prev_status = status;
                }

                subcommand = strtok(NULL, "&&||");
            }

            command = strtok(NULL, ";");
        }
    }

    return (0);
}
