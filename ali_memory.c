#include "shell.h"

/**
* pel_custom_bfree - it frees a pointer and all the NULLs to the address.
* @ptr: the address of the pointer to free
*
* Return: 1 freed, otherwise 0.
*/
int pel_custom_bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
