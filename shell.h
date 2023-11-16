#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 1024
#define BUFSIZ 1024

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

extern char **environ;

/**
 * struct list_s - singly linked list
 * @str: string data in the node
 * @len: length of the string
 * @next: points to the next node in the list
 *
 * Description: A structure for creating singly linked lists.
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

int execute_external_command(char *command, char **arguments);
void print_error(const char *program_name, const char *message);
int wordcount(char *s, char *delimiter);
char **strtow(char *str, char *delimiter);
int _atoi(char *s);
void change_directory(char **arguments);
void exit_shell(char **arguments);
void execute_command(char *command_string);
int handle_builtin(char *command, char **arguments, char *command_string);
int execute_absolute_path(char *command, char **arguments);

char *remove_extra_spaces(const char *input);
int is_whitespace(const char ch);
void free_list(list_t *head);
list_t *add_node(list_t **head, const char *str);
list_t *linked_path(char *name);
void find_command_in_path(char *command, char **arguments);
char *construct_path(char *directory, char *command);
int is_executable(const char *path);
void nonInteractiveMode(FILE *script);
void print_path_directories(const char *path);
void print_environment(void);
void print_prompt(void);
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
