#include "shell.h"
/**
* pel_custom_clear_info - it initializes CustomInfo_t struct
* @format: the struct address
*/
void pel_custom_clear_info(CustomInfo_t *format)
{
format->arg = NULL;
format->argv = NULL;
format->str_path = NULL;
format->argc = 0;
}
/**
* pel_custom_set_info - it initializes the CustomInfo_t struct
* @format: the struct address
* @a: the argument vector
*/
void pel_custom_set_info(CustomInfo_t *format, char **a)
{
int i = 0;
format->prg_fname = a[0];
if (format->arg)
{
format->argv = pel_custom_strtow(format->arg, " \t");
if (!format->argv)
{
format->argv = malloc(sizeof(char *) * 2);
if (format->argv)
{
format->argv[0] = pel_custom_strdup(format->arg);
format->argv[1] = NULL;
}
}
for (i = 0; format->argv && format->argv[i]; i++)
;
format->argc = i;
pel_custom_replace_alias(format);
pel_custom_replace_variables(format);
}
}
/**
* pel_custom_free_info - it frees CustomInfo_t struct fields.
* @format: the struct address.
* @a: returns true if freeing all fields.
*/
void pel_custom_free_info(CustomInfo_t *format, int a)
{
    pel_custom_free(format->argv);
    format->argv = NULL;
    format->str_path = NULL;
    if (a)
    {
        if (!format->command_buffer)
            free(format->arg);
        if (format->linked_environ)
            pel_custom_free_list(&(format->linked_environ));
        if (format->hist_node)
            pel_custom_free_list(&(format->hist_node));
        if (format->alias)
            pel_custom_free_list(&(format->alias));
        pel_custom_free(format->custom_environ);
        format->custom_environ = NULL;
	pel_custom_bfree((void **)&(format->command_buffer));
        if (format->r_fd > 2)
            close(format->r_fd);
        pel_custom_putchar(BUFFER_FLUSH);
    }
}
