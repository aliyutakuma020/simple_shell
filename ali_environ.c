#include "shell.h"
/**
* pel_custom_exit - Exit the custom shell.
* @format: CustomInfo_t structure.
*
* Return: 0 if the command is successful, -1 on error.
*/
int pel_custom_exit(CustomInfo_t *format)
{
int exitcheck = 0;
if (format->argv[1])  /* If there is an exit argument */
{
exitcheck = pel_custom_atoi(format->argv[1]);
if (exitcheck == -1)
{
format->position = 2;
pel_custom_print_error(format, "Illegal number: ");
pel_custom_error_puts(format->argv[1]);
pel_custom_error_putchar('\n');
return (1);
}
format->fig_err = exitcheck;
return (-2);
}
format->fig_err = -1;
return (-2);
}
/**
* pel_custom_cd - Change the current directory of a process.
* @format: Structure containing potential arguments.
*
* Return: Returns 0.
*/
int pel_custom_cd(CustomInfo_t *format)
{
char *dir, buffer[1024];
int chdir_ret;
char *s = getcwd(buffer, 1024);
if (!s)
{
pel_custom_puts("TODO: >>getcwd failure emsg here<<\n");
}
dir = format->argv[1] ? format->argv[1] : pel_custom_getenv(format, "HOME=");
chdir_ret = chdir(dir ? dir : "/");
if (pel_custom_strcmp(format->argv[1], "-") == 0)
{
if (!pel_custom_getenv(format, "OLDPWD="))
{
pel_custom_puts(s);
pel_custom_putchar('\n');
return (1);
}
dir = pel_custom_getenv(format, "OLDPWD=");
pel_custom_puts(dir);
pel_custom_putchar('\n');
chdir_ret = chdir(dir ? dir : "/");
}
else
{
chdir_ret = chdir(format->argv[1]);
}
if (chdir_ret == -1)
{
pel_custom_print_error(format, "can't cd to ");
pel_custom_error_puts(format->argv[1]);
pel_custom_error_putchar('\n');
}
else
{
pel_custom_set_environment(format, "OLDPWD",
pel_custom_getenv(format, "PWD="));
pel_custom_set_environment(format, "PWD", getcwd(buffer, 1024));
}
return (0);
}
/**
* pel_custom_help - Help function.
* @format: Structure containing potential arguments.
* Return: Always returns 0.
*/
int pel_custom_help(CustomInfo_t *format __attribute__((unused)))
{
/*implementation for the help function*/
pel_custom_puts("Help call works. Function not yet implemented\n");
return (0);
}
