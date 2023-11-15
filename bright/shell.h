#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 1024
#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/
#include <unistd.h>
#include <limits.h>
#include <string.h>

extern char **environ;

/* Structure for the linked list */
typedef struct list_s {
    char *str;
    unsigned int len;
    struct list_s *next;
} list_t;

//added by bright
void trim_trailing_spaces(char *str);
int find_command_in_path(char *command, char **arguments);
void *safe_malloc(size_t size);
void *safe_realloc(void *ptr, size_t size);
void find_and_execute_command_in_path(char *command, char **arguments);
int tokenize_line(char *line, char *tokens[]);
void execute_cleaned_line(char *cleaned_line);
void execute_non_interactive(FILE *script);
void free_list_and_strings(list_t *head);

int wordcount(char *s, char *delimiter);
char **strtow(char *str, char *delimiter);

void handlePipedCommands(const char *command);
void execute_command(char *command_string);
int handle_builtin(char *command);
void execute_absolute_path(char *command, char **arguments);

char *remove_extra_spaces(const char *input);
int is_whitespace(const char *str);
void free_list(list_t *head);
list_t *add_node(list_t **head, const char *str);
list_t *linked_path(const char *name);
//void find_command_in_path(char *command, char **arguments);
char *construct_path(const char *directory, const char *command);
int is_executable(const char *path);
void nonInteractiveMode(FILE *script);
void print_path_directories(const char *path);
void print_environment();
void print_prompt();
void exit_shell(char *command_string);
char *_getenv(const char *name);

char *_strdup(const char *str);
int _putchar(char c);
int _strlen(char *s);
void _puts(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, int n);
char *_strncpy(char *dest, char *src, int n);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, char *accept);
char *_strstr(char *haystack, char *needle);

#endif
