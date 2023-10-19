#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	printf("simple_shell$ ");
}

/**
 * main - Entry point for the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		display_prompt();

		/* Read a line of input */
		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			/* Handle end of file condition (Ctrl+D) */
			printf("\n");
			break;
		}

		/* Remove the newline character at the end */
		command[strcspn(command, "\n")] = '\0';

		/* Fork a new process */
		pid_t pid = fork();

		if (pid == -1)
		{
			/* Handle fork error */
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* Child process */
			execlp(command, command, (char *)NULL);

			/* If exec fails, print an error message */
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
		else
		{
			/* Parent process */
			/* Wait for the child process to complete */
			wait(NULL);
		}
	}

	return (0);
}

