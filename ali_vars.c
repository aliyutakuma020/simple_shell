#include "shell.h"

/**
* pel_custom_is_command_chain - test if current char
* in buffer is a chain delimiter
* @format: the parameter struct
* @buffer: the char buffer
* @p: address of current position in buf
*
* Return: 1 if chain delimiter, 0 otherwise
*/
int pel_custom_is_command_chain(CustomInfo_t *format, char *buffer, size_t *p)
{
size_t j = *p;

if (buffer[j] == '|' && buffer[j + 1] == '|')
{
buffer[j] = 0;
j++;
format->cmnd_b_type = COMMAND_OR;
}
else if (buffer[j] == '&' && buffer[j + 1] == '&')
{
buffer[j] = 0;
j++;
format->cmnd_b_type = COMMAND_AND;
}
else if (buffer[j] == ';')
{
buffer[j] = 0;
format->cmnd_b_type = COMMAND_CHAIN;
}
else
return (0);

*p = j;
return (1);
}
/**
* custom_check_cmd_chain - checks if we should continue
* chaining based on last status
* @format: the parameter struct
* @buffer: the char buffer
* @p: address of current position in buf
* @i: starting position in buf
* @l: length of buf
*
* Return: Void
*/
void custom_check_cmd_chain(CustomInfo_t *format, char *buffer,
		size_t *p, size_t i, size_t l)
{
size_t j = *p;

if (format->cmnd_b_type == COMMAND_AND)
{
if (format->position)
{
buffer[i] = 0;
j = l;
}
if (!format->position)
{
buffer[i] = 0;
j = l;
}
}
*p = j;
}
/**
* pel_custom_replace_alias - replaces an alias in the tokenized string
* @format: the parameter struct
*
* Return: returns (1) if replaced, 0 otherwise.
*/
int pel_custom_replace_alias(CustomInfo_t *format)
{
int i;
CustomList_t *node;
char *p;

for (i = 0; i < 10; i++)
{
node = pel_custom_node_starts_with(format->alias, format->argv[0], '=');
if (!node)
return (0);

free(format->argv[0]);
p = pel_custom_strchr(node->text, '=');
if (!p)
return (0);

p = pel_custom_strdup(p + 1);
if (!p)
return (0);

format->argv[0] = p;
}

return (1);
}
/**
* pel_custom_replace_variables - replaces vars in the tokenized string
* @format: the parameter struct
*
* Return: returns 1 if replaced, 0 otherwise
*/
int pel_custom_replace_variables(CustomInfo_t *format)
{
int i = 0;
CustomList_t *node;

for (i = 0; format->argv[i]; i++)
{
if (format->argv[i][0] != '$' || !format->argv[i][1])
continue;

if (!pel_custom_strcmp(format->argv[i], "$?"))
{
pel_custom_replace_string(&(format->argv[i]),
pel_custom_strdup(pel_custom_convert_number(format->position, 10, 0)));
continue;
}
if (!pel_custom_strcmp(format->argv[i], "$$"))
{
pel_custom_replace_string(&(format->argv[i]),
pel_custom_strdup(pel_custom_convert_number(getpid(), 10, 0)));
continue;
}
node = pel_custom_node_starts_with(format->linked_environ,
		&format->argv[i][1], '=');
if (node)
{
pel_custom_replace_string(&(format->argv[i]),
pel_custom_strdup(pel_custom_strchr(node->text, '=') + 1));
continue;
}
pel_custom_replace_string(&format->argv[i], pel_custom_strdup(""));
}
return (0);
}

/**
* pel_custom_replace_string - it replaces string
* @old: address of old string
* @new: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int pel_custom_replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
