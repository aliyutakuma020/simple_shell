#include "shell.h"

/**
 * pel_custom_get_environment - returns the string array copy of the environment
 * @info: Structure containing potential arguments.
 * Return: String array containing the environment variables.
 */
char **pel_custom_get_environment(CustomInfo_t *format)
{
    if (!format->custom_environ || format->new_environ_changed)
    {
        format->custom_environ = pel_custom_list_to_strings(format->linked_environ);
        format->new_environ_changed = 0;
    }

    return format->custom_environ;
}
/**
 * pel_custom_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int pel_custom_unset_environment(CustomInfo_t *format, char *v)
{
    CustomList_t *node = format->linked_environ;
    size_t i = 0;
    char *t;

    if (!node || !v)
        return 0;

    while (node)
    {
        t = pel_custom_starts_with(node->text, v);
        if (t && *t == '=')
        {
            format->new_environ_changed = pel_custom_delete_node_at_index(&(format->linked_environ), i);
            i = 0;
            node = format->linked_environ;
            continue;
        }
        node = node->next;
        i++;
    }

    return format->new_environ_changed;
}
/**
 * pel_custom_setenv - it Initializes a new environment variable.
 * @format: Structure containing potential arguments.
 * @value: string  property
 * @v: string value
 * Return: Always 0
 */
int pel_custom_set_environment(CustomInfo_t *format, char *v, char *value)
{
    char *buffer = NULL;
    CustomList_t *node;
    char *p;

    if (!v || !value)
        return 0;

    buffer = malloc(pel_custom_strlen(v) + pel_custom_strlen(value) + 2);
    if (!buffer)
        return (1);

    pel_custom_strcpy(buffer, v);
    pel_custom_strcat(buffer, "=");
    pel_custom_strcat(buffer, value);

    node = format->linked_environ;
    while (node)
    {
        p = pel_custom_starts_with(node->text, v);
        if (p && *p == '=')
        {
            free(node->text);
            node->text = buffer;
            format->new_environ_changed = 1;
            return 0;
        }
        node = node->next;
    }

    pel_custom_add_node_end(&(format->linked_environ), buffer, 0);
    free(buffer);
    format->new_environ_changed = 1;
    return (0);
}
