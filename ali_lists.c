#include "shell.h"

/**
* add_node - it dds a node to the start of the list
* @head: address of the pointer to head node
* @s: s is the field of node
* @n: the node index used by history
*
* Return: returns pointer to the new head of the list
*/
CustomList_t *pel_custom_add_node(CustomList_t **head,
		const char *s, int n)
{
CustomList_t *new;

if (!head)
return (NULL);

new = malloc(sizeof(CustomList_t));
if (!new)
return (NULL);

pel_custom_memset((void *)new, 0, sizeof(CustomList_t));
new->number = n;

if (s)
{
new->text = pel_custom_strdup(s);
if (!new->text)
{
free(new);
return (NULL);
}
}
new->next = *head;
*head = new;
return (new);
}
/**
* pel_custom_add_node_end - it adds a node to the end of the list.
* @head: the address of pointer to head node.
* @s: a text field of node
* @n: the  node index used by history
*
* Return: returns size of list
*/
CustomList_t *pel_custom_add_node_end(CustomList_t **head,
		const char *s, int n)
{
CustomList_t *new_node, *node;

if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(CustomList_t));
if (!new_node)
return (NULL);

pel_custom_memset((void *)new_node, 0, sizeof(CustomList_t));
new_node->number = n;

if (s)
{
new_node->text = pel_custom_strdup(s);
if (!new_node->text)
{
free(new_node);
return (NULL);
}
}

if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}

/**
* pel_custom_print_list_str - the prints only the text element
* of a CustomList_t linked list
* @high: the pointer to first node.
*
* Return: returns the size of list
*/
size_t pel_custom_print_list_str(const CustomList_t *high)
{
size_t i = 0;

while (high)
{
pel_custom_puts(high->text ? high->text : "(nil)");
pel_custom_puts("\n");
high = high->next;
i++;
}
return (i);
}
/**
* pel_custom_delete_node_at_index - deletes node at given index
* @head: address of pointer to first node
* @index: index of node to delete
*
* Return: 1 on success, 0 on failure
*/
int pel_custom_delete_node_at_index(CustomList_t **head, unsigned int index)
{
CustomList_t *node, *p_node;
unsigned int k = 0;

if (!head || !*head)
return (0);

if (!index)
{
node = *head;
*head = (*head)->next;
free(node->text);
free(node);
return (1);
}

node = *head;
while (node)
{
if (k == index)
{
p_node->next = node->next;
free(node->text);
free(node);
return (1);
}
k++;
p_node = node;
node = node->next;
}
return (0);
}
/**
* pel_custom_free_list - it frees all nodes of a list
* @h_ptr: the address of pointer to head node.
*
* Return: returns void.
*/
void pel_custom_free_list(CustomList_t **h_ptr)
{
CustomList_t *node, *n_node, *head;

if (!h_ptr || !*h_ptr)
return;

head = *h_ptr;
node = head;
while (node)
{
n_node = node->next;
free(node->text);
free(node);
node = n_node;
}
*h_ptr = (NULL);
}
