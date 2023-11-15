#ifndef SHELL_H
#define SHELL_H

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

// Structure for the linked list
typedef struct list_s {
    char *str;
    unsigned int len;
    struct list_s *next;
} list_t;

// Function declarations

void print_environment(void);
list_t *add_node(list_t **head, const char *str);
list_t *linked_path(const char *name);
void handle_echo(char **arguments);
int handle_builtin(char *command, char **arguments);
void find_command_in_path(const char *command);

void nonInteractiveMode(FILE *script);
int is_executable(const char *path);
char *_getenv(const char *name);
void print_prompt();
void exit_shell(int sig);
void execute_command(char *command_string);
char **strtow(char *str, char *delimiter);

char *_strdup(const char *str);
int wordcount(char *s, char *delimiter);
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
