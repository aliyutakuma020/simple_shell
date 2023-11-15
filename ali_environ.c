#include "shell.h"

/**
 * _myenv - displays the current situation
 * @format:Argument structure that could be used.
 * Return: Always 0
 */
int pel_custom_env(CustomInfo_t *format)
{
	pel_custom_print_list_str(format->linked_environ);
	return (0);
}

/**
 * pel_custom_getenv - retrieves an environ variable
 * @format: Potential argument structure. Used for maintenance
 * @name: env var name
 *
 * Return: the value
 */
char *pel_custom_getenv(CustomInfo_t *format, const char *name)
{
	CustomList_t *node = format->linked_environ;
	char *p;

	while (node)
	{
		p = pel_custom_starts_with(node->text, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * pel_custom_setenv - Set a new context variable,
 * @format: Potential argument structure.
 *  Return: Always 0
 */
int pel_custom_setenv(CustomInfo_t *format)
{
	if (format->argc != 3)
	{
		pel_custom_error_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (pel_custom_set_environment(format, format->argv[1], format->argv[2]))
		return (0);
	return (1);
}

/**
 * pel_custom_unsetenv - Delete an environment variable
 * @format: Potential argument structure.
 *  Return: Always 0
 */
int pel_custom_unsetenv(CustomInfo_t *format)
{
	int i;

	if (format->argc == 1)
	{
		pel_custom_error_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= format->argc; i++)
		pel_custom_unset_environment(format, format->argv[i]);

	return (0);
}

/**
 * pel_custom_populate_environment_list - Creates the env linked list.
 * @format: Potential argument structure. Used for maintenance
 * Return: Always 0
 */
int pel_custom_populate_environment_list(CustomInfo_t *format)
{
	CustomList_t *node = NULL;
	size_t i;

	for (i = 0; custom_environ[i]; i++)
		pel_custom_add_node_end(&node, custom_environ[i], 0);
	format->linked_environ = node;
	return (0);
}
