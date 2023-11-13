#include "shell.h"
/**
 * pel_custom_list_len - it determines length of linked list
 * @high: A pointer to first node.
 *
 * Return: returns size of list
 */
size_t pel_custom_list_length(const CustomList_t *high)
{
    size_t k = 0;

    while (high)
    {
        high = high->next;
        k++;
    }
    return (k);
}
/**
 * pel_custom_list_to_strings - it returns an array of strings of list->text.
 * @head: the pointer to first node.
 *
 * Return: array of strings
 */
char **pel_custom_list_to_strings(CustomList_t *head)
{
    CustomList_t *node = head;
    size_t i = pel_custom_list_length(head), j;
    char **strs, *s;

    if (!head || !i)
        return (NULL);
    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);
    for (i = 0; node; node = node->next, i++)
    {
        s = malloc(pel_custom_strlen(node->text) + 1);
        if (!s)
        {
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        s = pel_custom_strcpy(s, node->text);
        strs[i] = s;
    }
    strs[i] = NULL;
    return (strs);
}

/**
 * pel_custom_print_list_str - it only prints the text element of a CustomList_t linked list.
 * @high: pointer to first node
 *
 * Return: returns the size of list
 */
size_t pel_custom_print_list(const CustomList_t *high)
{
    size_t i = 0;

    while (high)
    {
        pel_custom_puts(pel_custom_convert_number(high->number, 10, 0));
        pel_custom_putchar(':');
        pel_custom_putchar(' ');
        pel_custom_puts(high->text ? high->text : "(nil)");
        pel_custom_puts("\n");
        high = high->next;
        i++;
    }
    return (i);
}

/**
 * pel_custom_node_starts_with - rit returns the  node whose string starts with prefix
 * @node: pointer to CustomList_t head
 * @ptr: the string to match
 * @ch: the next character after prefix to match
 *
 * Return: returns match node or null
 */
CustomList_t *pel_custom_node_starts_with(CustomList_t *node, char *ptr, char ch)
{
    char *p = NULL;

    while (node)
    {
        p = pel_custom_starts_with(node->text, ptr);
        if (p && ((ch == -1) || (*p == ch)))
            return (node);
        node = node->next;
    }
    return (NULL);
}

/**
 * pel_custom_get_node_index - it gets the index of a node
 * @head: the pointer to CustomList_t head.
 * @node: the pointer to the node
 *
 * Return: returns index of node or -1
 */
ssize_t pel_custom_get_node_index(CustomList_t *head, CustomList_t *node)
{
    size_t k = 0;

    while (head)
    {
        if (head == node)
            return (k);
        head = head->next;
        k++;
    }
    return (-1);
}
