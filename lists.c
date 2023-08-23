#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIASES 100
#define MAX_ALIAS_LENGTH 50

typedef struct
{
    char name[MAX_ALIAS_LENGTH];
    char value[MAX_ALIAS_LENGTH];
} Alias;

Alias aliases[MAX_ALIASES];
int numAliases = 0;

/* Function to print all aliases */
void printAliases()
{
    /* Iterate over the aliases array */
    for (int i = 0; i < numAliases; i++)
    {
        /* Print the name and value of each alias */
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

/* Function to print a specific alias */
void printAlias(char *name)
{
    /* Iterate over the aliases array */
    for (int i = 0; i < numAliases; i++)
    {
        /* Check if the current alias matches the given name */
        if (strcmp(aliases[i].name, name) == 0)
        {
            /* Print the name and value of the matching alias */
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            return;
        }
    }
}

/* Function to set an alias */
void setAlias(char *name, char *value)
{
    /* Iterate over the aliases array */
    for (int i = 0; i < numAliases; i++)
    {
        /* Check if the current alias matches the given name */
        if (strcmp(aliases[i].name, name) == 0)
        {
            /* Update the value of the matching alias */
            strcpy(aliases[i].value, value);
            return;
        }
    }
    /* If the alias doesn't exist, add it to the aliases array */
    if (numAliases < MAX_ALIASES)
    {
        strcpy(aliases[numAliases].name, name);
        strcpy(aliases[numAliases].value, value);
        numAliases++;
    }
}

int main()
{
    char input[100];
    char *token;

    /* Start of the shell program */
    while (1)
    {
        printf("Enter a command: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; /* Remove trailing newline character */

        token = strtok(input, " ");

        /* Check the command entered */
        if (strcmp(token, "alias") == 0)
        {
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                /* If no argument provided, print all aliases */
                printAliases();
            } else
            {
                if (strchr(token, '=') != NULL)
                {
                    /* If argument contains '=', set an alias */
                    char *name = strtok(token, "=");
                    char *value = strtok(NULL, "=");
                    setAlias(name, value);
                } else
                {
                    /* If argument doesn't contain '=', print specific alias */
                    printAlias(token);
                }
            }
        } else
        {
            /* Handle other commands... */
        }
    }

    return (0);
}
