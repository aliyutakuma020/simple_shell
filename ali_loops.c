#include "shell.h"

/**
* pel_custom_shell - main shell loop
* @format: the parameter & return info struct
* @a: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int pel_custom_shell(CustomInfo_t *format, char **a)
{
ssize_t read_status = 0;
int builtin_ret = 0;

while (read_status != -1 && builtin_ret != -2)
{
pel_custom_clear_info(format);
if (pel_custom_interactive(format))
pel_custom_puts("$ ");
pel_custom_error_putchar(BUFFER_FLUSH);
read_status = pel_custom_get_input(format);
if (read_status != -1)
{
pel_custom_set_info(format, a);
builtin_ret = find_pel_custom_builtin(format);
if (builtin_ret == -1)
find_pel_custom_command(format);
}
else if (pel_custom_interactive(format))
pel_custom_putchar('\n');
pel_custom_free_info(format, 0);
}
pel_custom_write_history(format);
pel_custom_free_info(format, 1);
if (!pel_custom_interactive(format) && format->position)
exit(format->position);
if (builtin_ret == -2)
{
if (format->fig_err == -1)
exit(format->position);
exit(format->fig_err);
}
return (builtin_ret);
}

/**
* find_pel_custom_builtin - function that finds a custom builtin command.
* @format: the parameter & return info struct
*
* Return: it will return -1 if the builtin not found,
*         0 if builtin executed successfully,
*         1 if builtin found but not successful,
*         -2 if builtin signals exit()...
*/
int find_pel_custom_builtin(CustomInfo_t *format)
{
int j, builtin_ret = -1;
CustomBuiltinTable custom_builtin_tbl[] = {
{"exit", pel_custom_exit},
{"env", pel_custom_env},
{"help", pel_custom_help},
/*   {"history", pel_custom_history},*/
{"setenv", pel_custom_setenv},
{"unsetenv", pel_custom_unsetenv},
{"cd", pel_custom_cd},
/*  {"alias", pel_custom_alias},*/
{NULL, NULL}
};

for (j = 0; custom_builtin_tbl[j].builtin_type; j++)
{
if (pel_custom_strcmp(format->argv[0], custom_builtin_tbl[j].builtin_type) == 0)
{
format->count_err++;
builtin_ret = custom_builtin_tbl[j].builtin_function(format);
break;
}
}
return (builtin_ret);
}

/**
* find_pel_custom_command - it will find a command in a PATH.
* @format: the parameter.
*
* Return: void
*/
void find_pel_custom_command(CustomInfo_t *format)
{
char *path = NULL;
int i, k;

format->str_path = format->argv[0];
if (format->flagline_c == 1)
{
format->count_err++;
format->flagline_c = 0;
}
for (i = 0, k = 0; format->arg[i]; i++)
if (!pel_custom_is_delimiter(format->arg[i], " \t\n"))
k++;
if (!k)
return;

path = find_pel_custom_path(format, pel_custom_getenv(format, "PATH="), format->argv[0]);
if (path)
{
format->str_path = path;
fork_pel_custom_command(format);
}
else
{
if ((pel_custom_interactive(format) || pel_custom_getenv(format, "PATH=")
|| format->argv[0][0] == '/') && is_pel_custom_command(format, format->argv[0]))
fork_pel_custom_command(format);
else if (*(format->arg) != '\n')
{
format->position = 127;
pel_custom_print_error(format, "not found\n");
}
}
}


/**
* pel_custom_fork_cmd - forks an exec thread to run cmd
* @format: the parameter & return info struct
*
* Return: void
*/
void fork_pel_custom_command(CustomInfo_t *format)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(format->str_path, format->argv, pel_custom_get_environment(format)) == -1)
{
pel_custom_free_info(format, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(format->position));
if (WIFEXITED(format->position))
{
format->position = WEXITSTATUS(format->position);
if (format->position == 126)
pel_custom_print_error(format, "Permission denied\n");
}
}
}
