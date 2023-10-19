#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"

/**
 * execute_command - Execute a command in the simple shell.
 * @command: The command to execute.
 */
void execute_command(const char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execlp(command, command, (char *)NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}

		if (WIFEXITED(status))
		{
			printf("Command executed with exit status %d\n", WEXITSTATUS(status));
		}
		else
		{
			printf("Command terminated abnormally\n");
		}
	}
}
