#include "shell.h"
char **custom_environ;
/**
 * pel_custom_env - prints the current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int pel_custom_env(CustomInfo_t *format)
{
    pel_custom_print_list_str(format->linked_environ);
    return (0);
}

/**
 * pel_custom_getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @n: env var name
 *
 * Return: the value
 */
char *pel_custom_getenv(CustomInfo_t *format, const char *n)
{
    CustomList_t *node = format->linked_environ;
    char *p;

    while (node)
    {
        p = pel_custom_starts_with(node->text, n);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * pel_custom_setenv - Initialize a new environment variable or modify an existing one
 * @format: Structure containing potential arguments.
 * Return: 0 on success, 1 on error.
 */
int pel_custom_setenv(CustomInfo_t *format)
{
    if (format->argc != 3)
    {
        pel_custom_error_puts("Incorrect number of arguments\n");
        return 1;
    }

    if (pel_custom_set_environment(format, format->argv[1], format->argv[2]))
        return (0);

    return (1);
}


/**
 * pel_custom_unsetenv - Remove an environment variable
 * @format: Structure containing potential arguments.
 * Return: Always 0
 */
int pel_custom_unsetenv(CustomInfo_t *format)
{
    int j;

    if (format->argc == 1)
    {
        pel_custom_error_puts("Too few arguments.\n");
        return 1;
    }
    
    for (j = 1; j <= format->argc; j++)
    {
        pel_custom_unset_environment(format, format->argv[j]);
    }

    return 0;
}

/**
 * pel_custom_populate_environment_list - populates env linked list
 * @format: Structure containing potential arguments.
 * Return: Always 0
 */
int pel_custom_populate_environment_list(CustomInfo_t *format)
{
    extern char **custom_environ;
    CustomList_t *node = NULL;
    size_t i;

    for (i = 0; custom_environ[i]; i++)
    {
	    pel_custom_add_node_end(&node, custom_environ[i], 0);
    }
    format->linked_environ = node;
    return 0;
}
