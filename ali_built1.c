#include "shell.h"

/**
 * pel_custom_history - history commands are listd.
 * @format: Argument structure that could be used
 *  Return: Always 0
 */
int pel_custom_history(CustomInfo_t *format)
{
	pel_custom_print_list(format->hist_node);
	return (0);
}
/**
 * pel_custom_unset_alias - uses string alias
 * @format: parameter struct
 * @str: A string alias
 *
 * Return: Always 0 on thriving, 1 on mistake.
 */
int pel_custom_unset_alias(CustomInfo_t *format, char *str)
{
	char *p, c;
	int ret;

	p = pel_custom_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = pel_custom_delete_node_at_index(&(format->alias),
	pel_custom_get_node_index(format->alias,
	pel_custom_node_starts_with(format->alias, str, -1)));
	*p = c;
	return (ret);
}
/**
 * pel_custom_set_alias - uses string alias
 * @format: parameter struct
 * @str: A string alias
 *
 * Return: Always 0 on thriving, 1 on mistake.
 */
int pel_custom_set_alias(CustomInfo_t *format, char *str)
{
	char *p;

	p = pel_custom_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (pel_custom_unset_alias(format, str));

	pel_custom_unset_alias(format, str);
	return (pel_custom_add_node_end(&(format->alias), str, 0) == NULL);
}
/**
 * pel_custom_print_alias - returns the alias string
 * @node: alias node
 *
 * Return: Always 0 on thriving, 1 on mistake.
 */
int pel_custom_print_alias(CustomList_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = pel_custom_strchr(node->text, '=');
		for (a = node->text; a <= p; a++)
			pel_custom_putchar(*a);
		pel_custom_putchar('\'');
		pel_custom_puts(p + 1);
		pel_custom_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * pel_custom_alias - imitation of guy alias.
 * @format: Potential argument structure.
 *  Return: Always 0
 */
int pel_custom_alias(CustomInfo_t *format)
{
	int i = 0;
	char *p = NULL;
	CustomList_t *node = NULL;

	if (format->argc == 1)
	{
		node = format->alias;
		while (node)
		{
			pel_custom_print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; format->argv[i]; i++)
	{
		p = pel_custom_strchr(format->argv[i], '=');
		if (p)
			pel_custom_set_alias(format, format->argv[i]);
		else
			pel_custom_print_alias(pel_custom_node_starts_with
			(format->alias, format->argv[i], '='));
	}

	return (0);
}
