#include "shell.h"

/**
 * main - the entry point
 * @ac: arg count.
 * @av: arg vector.
 *
 * Return: returns 0 on success, 1 on error
 */
int main(int ac, char **av)
{
    CustomInfo_t format [] = { CUSTOM_INFO_INIT };
    int fd = 2;

    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fd)
        : "r" (fd));

    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                pel_custom_error_puts(av[0]);
                pel_custom_error_puts(": 0: Can't open ");
                pel_custom_error_puts(av[1]);
                pel_custom_error_putchar('\n');
                pel_custom_error_putchar(BUFFER_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        format->r_fd = fd;
    }
    
    pel_custom_populate_environment_list(format);
    pel_custom_read_history(format);
    pel_custom_shell(format, av);
    
    return (EXIT_SUCCESS);
}
