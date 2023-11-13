#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1


#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* Flags */
#define LOWERCASE_CONVERSION 1
#define UNSIGNED_CONVERSION 2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".custom_shell_history"
#define HISTORY_MAX 4096

extern char **custom_environ;

/**
* struct CustomList - linked list
* @number: Number
* @text: the string.
* @next: points to subsequent node
*/

typedef struct CustomList
{
int number;
char *text;
struct CustomList *next;
} CustomList_t;

/**
* struct CustomInfo - contains pseudo-arguments to pass into a function
*@arg: string that has arguments
*@argv: array of strings
*@str_path: string path for active command
*@argc: count
*@count_err: check for error
*@fig_err: code error
*@flagline_c: on count
*@prg_fname: file name of the program
*@linked_environ: copy from environment
*@hist_node: history node
*@alias: alias
*@new_environ: this is on if the environment has changed
*@position: return state of command last executed
*@command_buffer: address of pointer to the command buffer
*@cmnd_b_type: type
*@r_fd: read fd
*@c_hist: history count
*@new_environ_changed: new eviron
*/

typedef struct CustomInfo
{
char *arg;
char **argv;
char *str_path;
int argc;
unsigned int count_err;
int fig_err;
int flagline_c;
char *prg_fname;
CustomList_t *linked_environ;
CustomList_t *hist_node;
CustomList_t *alias;
char **new_environ;
int new_environ_changed;
int position;
char *command_buffer;
int cmnd_b_type;
int r_fd;
int c_hist;
} CustomInfo_t;

#define CUSTOM_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}
/**
* struct CustomBuiltin - contains a builtin string and related function
* @builtin_type: the builtin command flag
* @builtin_function: the function
*/
typedef struct CustomBuiltin
{
char *builtin_type;
int (*builtin_function)(CustomInfo_t *);
} CustomBuiltinTable;


int pel_custom_shell(CustomInfo_t, char *);
int find_pel_custom_builtin(CustomInfo_t *);
void find_pel_custom_command(CustomInfo_t *);
void fork_pel_custom_command(CustomInfo_t *);


int is_pel_custom_command(CustomInfo_t *, char *);
char *duplicate_pel_characters(char *, int, int);
char *find_pel_custom_path(CustomInfo_t *, char *, char *);


int pel_custom_loophsh(char **);


void pel_custom_error_puts(char *);
int pel_custom_error_putchar(char);
int pel_custom_fd_putchar(char c, int fd);
int pel_custom_error_puts_fd(char *s, int fd);

int pel_custom_strlen(char *);
int pel_custom_strcmp(char *, char *);
char *pel_custom_starts_with(const char *, const char *);
char *pel_custom_strcat(char *, char *);

char *pel_custom_strcpy(char *, char *);
char *pel_custom_strdup(const char *);
void pel_custom_puts(char *);
int pel_custom_putchar(char);


char *pel_custom_strncpy(char *, char *, int);
char *pel_custom_strncat(char *, char *, int);
char *pel_custom_strchr(char *, char);

char **pel_custom_strtow(char *, char *);
char **pel_custom_strtow2(char *, char);

char *pel_custom_memset(char *, char, unsigned int);
void pel_custom_free(char **);
void *pel_custom_realloc(void *, unsigned int, unsigned int);

int pel_custom_bfree(void **);

int pel_custom_interactive(CustomInfo_t *);
int pel_custom_is_delimiter(char, char *);
int pel_custom_is_alpha(int);
int pel_custom_atoi(char *);

int pel_custom_error_atoi(char *);
void pel_custom_print_error(CustomInfo_t *, char *);
int pel_custom_print_d(int, int);
char *pel_custom_convert_number(long int, int, int);
void pel_custom_remove_comments(char *);

int pel_custom_exit(CustomInfo_t *);
int pel_custom_cd(CustomInfo_t *);
int pel_custom_help(CustomInfo_t *);

int pel_custom_history(CustomInfo_t *);
int pel_custom_alias(CustomInfo_t *);

ssize_t pel_custom_get_input(CustomInfo_t *);
int pel_custom_getline(CustomInfo_t, char *, size_t *);
void pel_custom_sigint_handler(int);

void pel_custom_clear_info(CustomInfo_t *);
void pel_custom_set_info(CustomInfo_t, char *);
void pel_custom_free_info(CustomInfo_t *, int);

char *pel_custom_getenv(CustomInfo_t *, const char *);
int pel_custom_env(CustomInfo_t *);
int pel_custom_setenv(CustomInfo_t *);
int pel_custom_unsetenv(CustomInfo_t *);
int pel_custom_populate_environment_list(CustomInfo_t *);

char **pel_custom_get_environment(CustomInfo_t *);
int pel_custom_unset_environment(CustomInfo_t *, char *);
int pel_custom_set_environment(CustomInfo_t *, char *, char *);

char *pel_custom_get_history_file(CustomInfo_t *format);
int pel_custom_write_history(CustomInfo_t *);
int pel_custom_read_history(CustomInfo_t *);
int pel_custom_build_history_list(CustomInfo_t *, char *, int);
int pel_custom_renumber_history(CustomInfo_t *);

CustomList_t pel_custom_add_node(CustomList_t *, const char *, int);
CustomList_t pel_custom_add_node_end(CustomList_t *, const char *, int);
size_t pel_custom_print_list_str(const CustomList_t *);
int pel_custom_delete_node_at_index(CustomList_t **, unsigned int);
void pel_custom_free_list(CustomList_t **);

size_t pel_custom_list_length(const CustomList_t *);
char **pel_custom_list_to_strings(CustomList_t *);
size_t pel_custom_print_list(const CustomList_t *);
CustomList_t *pel_custom_node_starts_with(CustomList_t *, char *, char);
ssize_t pel_custom_get_node_index(CustomList_t *, CustomList_t *);

int pel_custom_is_command_chain(CustomInfo_t *, char *, size_t *);
void custom_check_cmd_chain(CustomInfo_t *, char *, size_t *, size_t, size_t);
int pel_custom_replace_alias(CustomInfo_t *);
int pel_custom_replace_variables(CustomInfo_t *);
int pel_custom_replace_string(char **, char *);

#endif /* SHELL_H */
