#include "shell.h"
/**
 * execute - Executes a command
 * @cmd: The command to be executed
 *
 * This function checks if the command is a built-in command.
 * If it is, it handles it accordingly.
 * if it is not, it forks a child process to execute the external command.
 */
void execute(char *cmd)
{
	char **argv = tokenize(cmd);

	if (argv[0] == NULL)
	{
		free_tokens(argv);
		return;
	}

	if (is_builtin(argv[0]))
	{
		execute_builtin(argv);
	}
	else
	{
		execute_external(argv);
	}

	free_tokens(argv);
}

/**
 * is_builtin - checks if a command is a built-in command
 * @cmd: the command to check
 *
 * Return: 1 if it is a built-in command, 0 otherwise
 */

int is_builtin(char *cmd)
{
	char *builtins[] = {"cd", "exit", "env", "setenv", "unsetenv", "alias", NULL};

	for (int i = 0; builtins[i]; i++)
	{
		if (strcmp(cmd, builtins[i]) == 0)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * execute_builtin - Executes a built-in command
 * @argv: The command and its arguments
 *
 */
void execute_builtin(char **argv)
{
	if (strcmp(argv[0], "cd") == 0)
	{
		handle_cd(argv);
	}
	else if (strcmp(argv[0], "exit") == 0)
	{
		handle_exit(argv);
	}
	else if (strcmp(argv[0], "env") == 0)
	{
		handle_env();
	}
	else if (strcmp(argv[0], "setenv") == 0)
	{
		handle_setenv(argv);
	}
	else if (strcmp(argv[0], "unsetenv") == 0)
	{
		handle_unsetenv(argv);
	}
	else if (strcmp(argv[0], "alias") == 0)
	{
		handle_alias(argv);
	}
}

/**
 * execute_external - Forks and execute an external command
 * @argv: The command nad its arguments
 *
 */
void execute_external(char **argv)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror("shell");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("shell");
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}


/**
 * execute_line - splits and executes multiple commands separated by semicolons
 * @line: The line containing one or more commands
 *
 */

void execute_line(char *line)
{
	char *cmd;
	char *rest = line;

	while ((cmd = strtok_r(rest, ";", &rest)))
	{
		execute(cmd);
	}
}
