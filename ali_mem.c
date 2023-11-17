#include "shell.h"

/**
 * bfree - initializes a pointer and sets its location to NULL
 * @ptr: where empty ptr is
 *
 * Return:1 if success, 0 fail
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
