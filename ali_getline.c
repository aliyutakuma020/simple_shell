#include "shell.h"

/**
 * input_buf - the  buffers chained commands
 * @format: parameter struct
 * @buffer: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t pel_custom_input_buf(CustomInfo_t *format, char **buffer, size_t *len)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*len) 
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, pel_custom_sigint_handler);
#if USE_GETLINE
        r = getline(buffer, &len_p, stdin);
#else
        r = pel_custom_getline(format, buffer, &len_p);
#endif
        if (r > 0)
        {
            if ((*buffer)[r - 1] == '\n')
            {
                (*buffer)[r - 1] = '\0'; 
                r--;
            }
            format->flagline_c = 1;
            pel_custom_remove_comments(*buffer);
            pel_custom_build_history_list(format, *buffer, format->c_hist++);
            {
                *len = r;
                format->command_buffer = buffer;
            }
        }
    }
    return (r);
}
/**
 * pel_custom_get_input - it gets a line minus the newline.
 * @format: the parameter struct.
 *
 * Return: returns bytes read
 */
ssize_t pel_custom_get_input(CustomInfo_t *format)
{
    char *buf = NULL; /* dynamic allocation for buffer */
    size_t i = 0, j = 0, len = 0;
    ssize_t r = 0;
    char **buf_p = &(format->arg), *p;

    pel_custom_putchar(BUFFER_FLUSH);
    r = pel_custom_getline(format, &buf, &len);
    if (r == -1) /* EOF */
    {
        pel_custom_free(&buf);
        return -1;
    }

    if (len) /* we have commands left in the chain buffer */
    {
        j = i;      /* init new iterator to current buf position */
        p = buf + i; /* get pointer for return */

        custom_check_cmd_chain(format, buf, &j, i, len);
        while (j < len) /* iterate to semicolon or end */
        {
            if (pel_custom_is_command_chain(format, buf, &j))
                break;
            j++;
        }

        i = j + 1; /* increment past nulled ';' */
        if (i >= len) /* reached end of buffer? */
        {
            i = len = 0; /* reset position and length */
            format->cmnd_b_type = COMMAND_NORMAL;
        }

        *buf_p = p; /* pass back pointer to current command position */
        pel_custom_free(&buf); /* free allocated memory before returning */
        return pel_custom_strlen(p); /* return length of current command */
    }

    *buf_p = buf; /* else not a chain, pass back buffer from pel_custom_getline() */
    return (r);
}
/**
 * pel_custom_read_buf - it reads a buffer.
 * @format: parameter to the struct
 * @buffer: buffer
 * @i: the size
 *
 * Return: r
 */
ssize_t pel_custom_read_buf(CustomInfo_t *format, char *buffer, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return 0;

    r = read(format->r_fd, buffer, READ_BUFFER_SIZE);
    if (r >= 0)
        *i = (size_t)r;

    return (r);
}
/**
 * pel_custom_getline - it gets the next line of input from the STDIN
 * @format: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int pel_custom_getline(CustomInfo_t *format, char **ptr, size_t *length)
{
    static char buf[READ_BUFFER_SIZE];
    static size_t i, len;
    size_t y;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = pel_custom_read_buf(format, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = pel_custom_strchr(buf + i, '\n');
    y = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = pel_custom_realloc(p, s, s ? s + y : y + 1);
    if (!new_p) /* MALLOC FAILURE! */
        return (p ? free(p), -1 : -1);

    if (s)
        pel_custom_strncat(new_p, buf + i, y - i);
    else
        pel_custom_strncpy(new_p, buf + i, y - i + 1);

    s += y - i;
    i = y;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return s;
}
/**
 * pel_custom_sigintHandler - it handles blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: returns  void
 */
void pel_custom_sigint_handler(__attribute__((unused))int sig_num)
{
    pel_custom_puts("\n");
    pel_custom_puts("$ ");
    pel_custom_putchar(BUFFER_FLUSH);
}
