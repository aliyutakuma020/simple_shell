#include "shell.h"
/**
* pel_custom_get_history_file - it gets the history of a file
* @format: the parameter struct.
*
* Return: it returns allocated string containing history file
*/
char *pel_custom_get_history_file(CustomInfo_t *format)
{
char *buffer, *d;
d = pel_custom_getenv(format, "HOME=");
if (!d)
return (NULL);
buffer = malloc(sizeof(char) * (pel_custom_strlen(d) +
			pel_custom_strlen(HISTORY_FILE) + 2));
if (!buffer)
return (NULL);
buffer[0] = 0;
pel_custom_strcpy(buffer, d);
pel_custom_strcat(buffer, "/");
pel_custom_strcat(buffer, HISTORY_FILE);
return (buffer);
}
/**
* pel_custom_write_history - writes the command history to a file
* @format: the parameter struct
*
* Return: returns 1 on success, else -1
*/
int pel_custom_write_history(CustomInfo_t *format)
{
int f;
char *filename = pel_custom_get_history_file(format);
CustomList_t *node = NULL;
if (!filename)
return (-1);
f = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (f == -1)
return (-1);
for (node = format->hist_node; node; node = node->next)
{
pel_custom_error_puts_fd(node->text, f);
pel_custom_fd_putchar('\n', f);
}
pel_custom_fd_putchar(BUFFER_FLUSH, f);
close(f);
return (1);
}
/**
* pel_custom read_history - reads history from file
* @format: the parameter struct
*
* Return: histcount on success, 0 otherwise
*/
int pel_custom_read_history(CustomInfo_t *format)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = pel_custom_get_history_file(format);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
pel_custom_build_history_list(format, buf + last, linecount++);
last = i + 1;
}
if (last != i)
pel_custom_build_history_list(format, buf + last, linecount++);
free(buf);
format->c_hist = linecount;
while (format->c_hist-- >= HISTORY_MAX)
pel_custom_delete_node_at_index(&(format->hist_node), 0);
pel_custom_renumber_history(format);
return (format->c_hist);
}
/**
* pel_custom_build_history_list - it adds entry to a history linked list.
* @format: Structure containing potential arguments. Used to maintain
* @buffer: the buffer
* @line: the history linecount, histcount
*
* Return: Always 0
*/
int pel_custom_build_history_list(CustomInfo_t *format, char *buffer, int line)
{
CustomList_t *node = NULL;
if (format->hist_node)
node = format->hist_node;
pel_custom_add_node_end(&node, buffer, line);
if (!format->hist_node)
format->hist_node = node;
return (0);
}
/**
* pel_custom_renumber_history - the renumbers the history
* linked list after changes
* @format: Structure containing potential arguments. Used to maintain
*
* Return: returns the new histcount
*/
int pel_custom_renumber_history(CustomInfo_t *format)
{
CustomList_t *node = format->hist_node;
int j = 0;
while (node)
{
node->number = j++;
node = node->next;
}
format->c_hist = j;
return (format->c_hist);
}
