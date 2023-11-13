#include "shell.h"

/**
* is_pel_custom_command - it determines if a file is an executable command
* @format: the CustomInfo_t struct
* @custom_path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int is_pel_custom_command(CustomInfo_t *format, char *custom_path)
{
struct stat custom_stat;

(void)format;

if (!custom_path || stat(custom_path, &custom_stat))
return (0);

if (custom_stat.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* pel_custom_dup_chars - function to duplicates characters.
* @path_str: the PATH string.
* @start: the starting index.
* @stop: the stopping index
* Return: pointer to new buffer
*/
char *pel_custom_dup_chars(char *path_str, int start, int stop)
{
static char buffer[1024];
int j = 0, k = 0;

for (k = 0, j = start; j < stop; j++)
{
if (path_str[j] != ':')
{
buffer[k++] = path_str[j];
}
}

buffer[k] = '\0';
return (buffer);
}

/**
* find_pel_custom_path - finds this cmd in the PATH string
* @format: the info struct
* @path_str: the PATH string
* @c: cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *find_pel_custom_path(CustomInfo_t *format, char *path_str, char *c)
{
int i = 0, c_pos = 0;
char *path;

if (!path_str)
return (NULL);

if ((pel_custom_strlen(c) > 2) && pel_custom_starts_with(c, "./"))
{
if (is_pel_custom_command(format, c))
return (c);
}

while (1)
{
if (!path_str[i] || path_str[i] == ':')
{
path = pel_custom_dup_chars(path_str, c_pos, i);

if (!*path)
pel_custom_strcat(path, c);
else
{
pel_custom_strcat(path, "/");
pel_custom_strcat(path, c);
}

if (is_pel_custom_command(format, path))
return (path);

if (!path_str[i])
break;

c_pos = i;
}

i++;
}

return (NULL);
}
