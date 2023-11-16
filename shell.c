#include "shell.h"

void print_prompt() {
    char prompt[] = "$ ";
    write(STDOUT_FILENO, prompt, _strlen(prompt));
}

void exit_shell(char *command_string) {
    if (_strcmp(command_string, "exit") == 0) {
        exit(0);  /* No exit status provided, exit with status 0 */
    } else if (_strncmp(command_string, "exit ", 5) == 0) {
        /* Extract the status argument */
        int status = atoi(command_string + 5);
        exit(status);
    }
}

/* Function to remove trailing spaces from a string */
void trim_trailing_spaces(char *str) {
    int i = _strlen(str) - 1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t')) {
        str[i] = '\0';
        i--;
    }
}

int main(int argc, char *argv[]) {
    if (isatty(STDIN_FILENO)) {
        /* Interactive mode */
        char *command_string = NULL;
        size_t command_len = 0;
        ssize_t readline;

        while (1) {
            print_prompt();

            readline = getline(&command_string, &command_len, stdin);

            if (readline == -1) {
                exit_shell(NULL); /* No exit status */
                break;
            }

            if (readline > 1) {
                if (command_string[readline - 1] == '\n') {
                    command_string[readline - 1] = '\0';
                }

              /* Trim trailing spaces before processing the command */
              trim_trailing_spaces(command_string);

                if (_strncmp(command_string, "exit", 4) == 0) {
                    exit_shell(command_string);
                    break;
              } else if (_strcmp(command_string, "env") == 0) {
                    print_environment();
                }
                else {
                    execute_command(command_string);
                }
            }
        }

        free(command_string);
    } else {
        /* Non-interactive mode */
        if (argc > 1) {
            FILE *script = fopen(argv[1], "r");
            if (script != NULL) {
              execute_non_interactive(script, argv);
                fclose(script);
            } else {
              perror("Error opening script file");
                return EXIT_FAILURE;
            }
        } else {
            /* Check if data is being piped in */
          if (!isatty(STDIN_FILENO)) {
              execute_non_interactive(stdin, argv);
          } else {
              /* No script file provided and no piped data */
            write(STDOUT_FILENO, "Usage: ", 7);
            write(STDOUT_FILENO, argv[0], _strlen(argv[0]));
            write(STDOUT_FILENO, " <script_file>\n", 15);
            return EXIT_FAILURE;
          }
        }
    }

    return 0;
}

void execute_non_interactive(FILE *script, char **argv) {
    char *line = NULL, *cleaned_line;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, script)) != -1) {
        if (is_whitespace(line)) {
            continue; /* Skip execution for empty or whitespace-only lines */
        }

        if (line[0] == '"') {
            handlePipedCommands(line);
        } else {
            if (read > 1) {
                if (line[read - 1] == '\n') {
                    line[read - 1] = '\0';
                }

                cleaned_line = remove_extra_spaces(line);
                if (cleaned_line != NULL) {
                    execute_cleaned_line(cleaned_line, argv);
                    /* free(cleaned_line); already freed in execute_cleaned line function */
                }
            }
        }
    }

    free(line);
}

void execute_cleaned_line(char *cleaned_line, char **argv) {
    char *command, **arguments;
    char *tokens[MAX_ARGS];
    int token_count = tokenize_line(cleaned_line, tokens);

    if (token_count > 0) {
        command = tokens[0];
        arguments = tokens;

        if (!handle_builtin(command)) {
            if (command[0] == '/' || command[0] == '.') {
                execute_absolute_path(command, arguments);
            } else {
                find_and_execute_command_in_path(command, arguments, argv);
            }
        }
    }
   /* Free memory allocated for cleaned_line */
   free(cleaned_line);
}

int tokenize_line(char *line, char *tokens[]) {
    int token_count = 0;
    int i = 0;

    while (line[i] != '\0' && token_count < MAX_ARGS) {
        while (line[i] == ' ') {
            i++;
        }

        if (line[i] == '\0') {
            break;
        }

        tokens[token_count] = &line[i];

        while (line[i] != ' ' && line[i] != '\0') {
            i++;
        }

        if (line[i - 1] == '\n') {
            line[i - 1] = '\0';
        } else {
            line[i] = '\0';
        }

        token_count++;
        i++;
    }

    tokens[token_count] = NULL;

    return token_count;
}

void find_and_execute_command_in_path(char *command, char **arguments, char **argv) {
    list_t *path_directories = linked_path("PATH");
    list_t *current_directory = path_directories;
  int command_found;

    if (arguments == NULL) {
        arguments = (char **)malloc(2 * sizeof(char *));
        if (arguments == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        arguments[0] = command;
        arguments[1] = NULL;
    }

  command_found = 0;  /* Flag to check if the command is found */

    while (current_directory != NULL) {
        char *full_path = construct_path(current_directory->str, command);

        if (full_path != NULL && access(full_path, X_OK) == 0) {
            execute_absolute_path(full_path, arguments);
            free(full_path);
            command_found = 1;
            break;
        }

        free(full_path);
        current_directory = current_directory->next;
    }
  
  /* Check if the command was not found in any directory */
  if (!command_found) {
    /* Print the program name and error message to stderr */
    write(2, argv[0], _strlen(argv[0]));
    write(2, ": 1: ", 5);
    write(2, command, _strlen(command));  /* Write command name */
    write(2, ": not found\n", 12);  /* Write error message */
  }

    /* Free memory at the end */
    free_list_and_strings(path_directories);
}



void print_path_directories(const char *path) {
    const char *directory = path;
    const char *current_char = path;
    int length;

    while (*current_char != '\0') {
        if (*current_char == ':') {
            /* If ':' is found, write the directory */
            length = current_char - directory;
            write(STDOUT_FILENO, directory, length);
            write(STDOUT_FILENO, "\n", 1);
            directory = current_char + 1;
        }
        current_char++;
    }

    /* Write the last directory after the loop */
    write(STDOUT_FILENO, directory, current_char - directory);
}

void print_environment()
{
  extern char **environ;

  char **env = environ;
    while (*env) {
        write(STDOUT_FILENO, *env, _strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
        env++;
    }
}

void handlePipedCommands(const char *command) {
  char *extracted_command = NULL, *cleaned_command;
    size_t command_len = 0;
    int command_start = -1;
    int command_end = -1, i;


    for (i = 0; command[i] != '\0'; i++) {
        if (command[i] == '"') {
            if (command_start == -1) {
                command_start = i + 1;
            } else {
                command_end = i; 
                break;
            }
        }
    }

    if (command_start != -1 && command_end != -1) {
        command_len = command_end - command_start;
        extracted_command = safe_malloc(command_len + 1);
        if (extracted_command != NULL) {
            strncpy(extracted_command, &command[command_start], command_len);
            extracted_command[command_len] = '\0';


            cleaned_command = remove_extra_spaces(extracted_command);
            if (cleaned_command != NULL) {
                if (is_executable(cleaned_command)) {
                    execute_command(cleaned_command);
                }
                free(cleaned_command);
            }
        }
    }
    if (extracted_command != NULL) {
        free(extracted_command);
    }
}

int is_executable(const char *path) {
    struct stat st;

    if (path == NULL || *path == '\0') {
        return 0;
    }

    if (stat(path, &st) == 0) {
        if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) {
            return 1; /* Executable file */
        }
    }

    return 0; /* Not an executable file */
}
int is_whitespace(const char *str) {
    while (*str) {
        if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r') {
            return 0;
        }
        str++;
    }
    return 1; /* Only contains whitespace characters */
}

char* remove_extra_spaces(const char* line)
{
  int i, j;
  int space_flag;
  char* cleaned_line;
    if (line == NULL || *line == '\0') {
        return NULL;
    }

    cleaned_line = safe_malloc(strlen(line) + 1);
    if (cleaned_line == NULL) {
        return NULL;
    }

    space_flag = 0; /* Flag to handle multiple spaces */

    for (i = 0, j = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ') {
            cleaned_line[j++] = line[i];
            space_flag = 0; 
        } else {
            if (space_flag == 0) {
                cleaned_line[j++] = line[i];
            }
            space_flag = 1;
        }
    }

    cleaned_line[j] = '\0';
    return cleaned_line;
}

void nonInteractiveMode(FILE *script) {
  char *line = NULL, *cleaned_line;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, script)) != -1) {
        if (is_whitespace(line)) {
            return; /* Skip execution for empty or whitespace-only lines */
        }
        if (line[0] == '"') {
            handlePipedCommands(line);
        } else {
            if (read > 1) {
                if (line[read - 1] == '\n') {
                    line[read - 1] = '\0';
                }

                cleaned_line = remove_extra_spaces(line);
                if (cleaned_line != NULL) {
                    if (is_executable(cleaned_line)) {
                        execute_command(cleaned_line);
                    }
                    free(cleaned_line);
                }
            }
        }
    }

    free(line);
}

list_t *linked_path(const char *name)
{
    char *path = _getenv(name);
    list_t *head = NULL;
    char *directory = path;
    char *current_char = path;

    if (path == NULL)
    {
      return (NULL);
    }

    while (*current_char != '\0') {
        if (*current_char == ':') {
            *current_char = '\0'; /* Change ':' to '\0' temporarily */
            add_node(&head, directory);
            directory = current_char + 1;
        }
        current_char++;
    }

    add_node(&head, directory); /* Add the last directory */

  /* Restore the original value of the modified string */
  *current_char = '=';

    return head;
}

int find_command_in_path(char *command, char **arguments) {
    list_t *path_directories = linked_path("PATH");
    list_t *current_directory = path_directories;

    while (current_directory != NULL) {
        char *full_path = construct_path(current_directory->str, command);

        if (full_path != NULL && access(full_path, X_OK) == 0) {
            execute_absolute_path(full_path, arguments);
            free(full_path);
            return 1;
        }

        free(full_path);
        current_directory = current_directory->next;
    }

    /* Free memory at the end */
    free_list(path_directories);
    return 0;
}

char *construct_path(const char *directory, const char *command) {
    size_t path_length = strlen(directory) + strlen(command) + 2; /* +2 for '/' and null terminator */
    char *full_path = (char *)malloc(path_length);

    if (full_path == NULL) {
        return NULL;
    }

    strcpy(full_path, directory);
    strcat(full_path, "/");
    strcat(full_path, command);

    return full_path;
}

void free_list(list_t *head) {
    while (head != NULL) {
        list_t *temp = head;
        head = head->next;
        free(temp->str);
        free(temp);
    }
}

list_t *add_node(list_t **head, const char *str) {
    list_t *new_node;
    unsigned int dup_len = 0;
    char *dup;

    new_node = malloc(sizeof(list_t));
    if (new_node == NULL)
        return (NULL);

    dup = _strdup(str);
    if (dup == NULL) {
        free(new_node);
        return (NULL);
    }

    while (dup[dup_len] != '\0')
        dup_len++;

    new_node->str = dup;
    new_node->len = dup_len;
    new_node->next = *head;
    *head = new_node;

    return (new_node);
}

int handle_builtin(char *command)
{
    if (_strcmp(command, "env") == 0)
    {
        print_environment();
        return (1); /* Return 1 to indicate that it's a built-in command */
    }

    return (0); /* Return 0 for non-built-in commands */
}

void execute_command(char *command_string) {

    char *command, **arguments;
    char *tokens[MAX_ARGS];
    int token_count = 0;
    int i = 0;

    /* Tokenizing the command string based on spaces */
    while (command_string[i] != '\0' && token_count < MAX_ARGS) {
        while (command_string[i] == ' ') {
                /* Skip over multiple spaces until a non-space character is found */
            i++;
        }

        if (command_string[i] == '\0') {
                /* Handle empty command (only spaces) */
        return;
    }
            tokens[token_count] = &command_string[i];

        while (command_string[i] != ' ' && command_string[i] != '\0') {
            i++;
        }
        if (command_string[i - 1] == '\n') {
            command_string[i - 1] = '\0';
        } else {
            command_string[i] = '\0';
        }
        token_count++;
        i++;
    }

    tokens[token_count] = NULL;

    if (token_count == 0) {
        return; /* If no tokens were found, just return without an error message */
    }

    command = tokens[0];
    arguments = tokens;

  if (_strcmp(command, "setenv") == 0) {
    /* Check if setenv command and call your setenv function */
    if (token_count == 3) {
        _setenv(arguments[1], arguments[2], 1);
    } else {
        /* Print error message to stderr */
        write(2, "setenv: Invalid number of arguments\n", 36);
    }
    return;
  } else if (_strcmp(command, "unsetenv") == 0) {
    /* Check if unsetenv command and call your unsetenv function */
    if (token_count == 2) {
        _unsetenv(arguments[1]);
    } else {
        /* Print error message to stderr */
        write(2, "unsetenv: Invalid number of arguments\n", 38);
    }
    return;
  } else if (handle_builtin(command)) {
    return; /* If it's a built-in command (other than setenv/unsetenv), return without forking */
  }

    /* Check if it's an absolute path or in the current directory */
    if (command[0] == '/' || command[0] == '.') {
        execute_absolute_path(command, arguments);
        return;
    }

  /* If not an absolute path or known command, search in the directories specified in the PATH */
  if (!find_command_in_path(command, arguments) && !is_executable(command)) {
  /* If control reaches here, the command was not found */
    /* Print the program name and error message to stderr */
    write(2, command, _strlen(command));  /* Write command name */
    write(2, ": command not found\n", 20);  /* Write error message */
  }
}

void execute_absolute_path(char *command, char **arguments)
{
    if (access(command, X_OK) == 0) {
        pid_t child_pid = fork();
        if (child_pid == -1) {
            return;
        }

        if (child_pid == 0) {

            if (execve(command, arguments, environ) == -1) {
                exit(1);
            }
        } else {
          int status;
          waitpid(child_pid, &status, 0);
/*
          if (WIFEXITED(status)) {
              int exit_status = WEXITSTATUS(status);
               You can use 'exit_status' as needed 
          }
  */        
        }
    }
}

int _putchar(char c)
{
  return (write(1, &c, 1));
}

int _strlen(const char *s)
{
  int i;

  for (i = 0; s[i] != '\0'; i++)
  {
    continue;
  }

  return (i);
}

void _puts(char *str)
{
  int a;

  for (a = 0; str[a] != '\0'; a++)
  {
    _putchar(str[a]);
  }
  _putchar('\n');
}

char *_strcpy(char *dest, char *src)
{
  int i = 0;

  while (src[i])
  {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return (dest);
}

char *_strdup(const char *str)
{
  int len = 0, i = 0;
  char *duplicate;

  if (str == NULL)
    return (NULL);

  while (str[len] != '\0')
    (len++);

  duplicate = safe_malloc((len + 1) * sizeof(char));
  if (duplicate == NULL)
    return (NULL);

  for (i = 0; i <= len; i++)
  {
    duplicate[i] = str[i];
  }

  return (duplicate); /* Return the duplicated string */
}

char *_strcat(char *dest, char *src)
{
  char *ptr = dest;

  while (*dest != '\0')
  {
    dest++;
  }
  while (*src != '\0')
  {
    *dest = *src;
    dest++;
    src++;
  }
  *dest = '\0';

  return (ptr);
}

char *_strncat(char *dest, char *src, int n)
{
  int i = 0, len = 0;

  while (dest[i++])
    len++;

  for (i = 0; src[i] && i < n; i++)
    dest[len++] = src[i];

  return (dest);
}

char *_strncpy(char *dest, char *src, int n)
{
  int i = 0, len = 0;

  while (src[i++])
    len++;

  for (i = 0; i < n && src[i]; i++)
    dest[i] = src[i];

  for (i = len; n > i; i++)
    dest[i] = '\0';

  return (dest);
}

int _strcmp(char *s1, char *s2)
{
  while (*s1 && *s2 && *s1 == *s2)
  {
    s1++;
    s2++;
  }
  return (*s1 - *s2);
}

char *_strchr(char *s, char c)
{
  int i;

  for (i = 0; s[i] >= '\0'; i++)
  {
    if (s[i] == c)
      return (s + i);
  }

  return ('\0');
}

unsigned int _strspn(char *s, char *accept)
{
  int i, j;

  for (i = 0; s[i]; i++)
  {
    for (j = 0; accept[j]; j++)
    {
      if (s[i] == accept[j])
        break;
    }
    if (!accept[j])
      break;
  }
  return (i);
}

char *_strpbrk(char *s, char *accept)
{
  int i;

  while (*s)
  {
    for (i = 0; accept[i]; i++)
    {
      if (*s == accept[i])
        return (s);
    }

    s++;
  }

  return ('\0');
}

char *_strstr(char *haystack, char *needle)
{
  char *start;
  char *sub;

  while (*haystack != '\0')
  {
    start = haystack;
    sub = needle;

    while (*sub == *haystack && *haystack != 0 && *sub != 0)
    {
      haystack++;
      sub++;
    }
    if (*sub == 0)
      return (start);
    haystack = start + 1;
  }
  return (0);
}

void set_string(char **s, char *to)
{
  *s = to;
}

int wordcount(char *s, char *delimiter) {
    int i;
    int count = 0;
    int in_word = 0;

    for (i = 0; s[i]; i++) {
        if (_strchr(delimiter, s[i])) {
            if (in_word) {
                in_word = 0;
                count++;
            }
        } else {
            in_word = 1;
        }
    }

    if (in_word) {
        count++;
    }

    return count;
}

char **strtow(char *str, char *delimiter) {
    int i, j, k, l, count, m;
    char **word;
    int in_word = 0;

    if (str == NULL || *str == '\0') {
        return NULL;
    }

    count = wordcount(str, delimiter);
    if (count == 1) {
        return NULL;
    }

    word = malloc(count * sizeof(char *));
    if (word == NULL) {
        return NULL;
    }

    word[count - 1] = NULL;
    m = 0;

    for (i = 0; str[i]; i++) {
        if (_strchr(delimiter, str[i])) {
            if (in_word) {
                for (j = 1; str[i + j] != '\0' && !_strchr(delimiter, str[i + j]); j++)
                    ;
                j++;
                word[m] = malloc(j * sizeof(char));
                j--;

                if (word[m] == NULL) {
                    for (k = 0; k < m; k++) {
                        free(word[k]);
                    }

                    free(word[count - 1]);
                    free(word);
                    return NULL;
                }

                for (l = 0; l < j; l++) {
                    word[m][l] = str[i + l];
                }

                word[m][l] = '\0';
                m++;
                i += j;
            }
        } else {
            in_word = 1;
        }
    }

    if (in_word) {
        for (j = 1; str[i + j] != '\0'; j++)
            ;
        j++;
        word[m] = malloc(j * sizeof(char));
        j--;

        if (word[m] == NULL) {
            for (k = 0; k < m; k++) {
                free(word[k]);
            }

            free(word[count - 1]);
            free(word);
            return NULL;
        }

        for (l = 0; l < j; l++) {
            word[m][l] = str[i + l];
        }

        word[m][l] = '\0';
        m++;
    }

    return word;
}

void *safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *safe_realloc(void *ptr, size_t old_size, size_t new_size) {
  void *new_ptr;
  size_t copy_size;
  
    if (new_size == 0) {
        /* If new size is 0, treat it as a free operation */
        free(ptr);
        return NULL;
    }

    new_ptr = malloc(new_size);
    if (new_ptr == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    /* Copy data from the old block to the new one */
    copy_size = (old_size < new_size) ? old_size : new_size;
    _memcpy(new_ptr, ptr, copy_size);

    /* Free the old block */
    free(ptr);

    return new_ptr;
}


void free_list_and_strings(list_t *head) {
    while (head != NULL) {
        list_t *temp = head;
        head = head->next;
        free(temp->str);
        free(temp);
    }
}

char *_memcpy(char *dest, char *src, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
    {
        *(dest + i) = *(src + i);
    }

    return (dest);
}


/* Implementation of the _getline function */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream) {
  int ch;
  size_t i;
  static size_t buffer_size = BUFFER_SIZE;
    if (*lineptr == NULL || *n == 0) {
        /* Allocate initial buffer if not provided */
        *n = buffer_size;
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            return -1;  /* Memory allocation failure */
        }
    }

    i = 0;

    /* Read characters until a newline or EOF is encountered */
    while ((ch = _fgetc(stream)) != EOF && ch != '\n') {
        /* Check if more space is needed */
        if (i == *n - 1) {
            *n *= 2;
            *lineptr = safe_realloc(*lineptr, i, *n);
        }

        /* Store the character */
        (*lineptr)[i++] = (char)ch;
    }

    /* Check if any characters were read */
    if (i == 0 && ch == EOF) {
        return 0;  /* End of file reached */
    }

    /* Null-terminate the string */
    (*lineptr)[i] = '\0';

    return i;  /* Number of characters read */
}


int _fgetc(FILE *stream) {
  char c;
  ssize_t bytesRead;

    /* Ensure that the stream is not NULL */
    if (stream == NULL) {
        return EOF;
    }

    bytesRead = read(fileno(stream), &c, 1);

    if (bytesRead == 1) {
        return (unsigned char)c;
    } else {
        return EOF; /* End of file or error */
    }
}

int _strncmp(const char *s1, const char *s2, size_t n) {
  size_t i;
  
    for (i = 0; i < n; ++i) {
        if (s1[i] != s2[i]) {
            return (unsigned char)s1[i] - (unsigned char)s2[i];
        }

        /* If either string ends before n characters, break the loop */
        if (s1[i] == '\0' || s2[i] == '\0') {
            break;
        }
    }

    return 0;  /* Strings are equal up to the first n characters */
}

char *_getenv(const char *name) {
  char **env;
  
    if (name == NULL || *name == '\0') {
        return NULL /* Invalid input */ ;
    }

    /* Iterate through the environment variables */
    for (env = environ; *env != NULL; env++) {
        /* Check if the current environment variable starts with the specified name */
        if (_strncmp(*env, name, _strlen(name)) == 0 && (*env)[_strlen(name)] == '=') {
            /* Return the value part of the environment variable */
            return *env + _strlen(name) + 1;
        }
    }

    return NULL /* Variable not found */ ;
}

int _setenv(const char *name, const char *value, int overwrite) {
   char *existingValue;
  size_t envVarLength;
  char *newEnvVar;
  int envSize;
  char **newEnviron;
  int i;
  char *name_clone = _strdup(name);
  
    if (name == NULL || *name == '\0' || _strchr(name_clone, '=') != NULL) {
        return -1 /* Invalid input */ ;
    }

    /* Check if the variable already exists */
    existingValue = _getenv(name);

    /* If the variable exists and overwrite is 0, do nothing */
    if (existingValue != NULL && !overwrite) {
        return 0;
    }

    /* Concatenate name=value into a single string */
    envVarLength = _strlen(name) + _strlen(value) + 2 /* +2 for '=' and null terminator */ ;
    newEnvVar = (char *)malloc(envVarLength);
    if (newEnvVar == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }
    snprintf(newEnvVar, envVarLength, "%s=%s", name, value);

    /* Update the environment by reallocating and copying */
    envSize = 0;
    while (environ[envSize] != NULL) {
        envSize++;
    }

    newEnviron = (char **)malloc((envSize + 2) * sizeof(char *));
    if (newEnviron == NULL) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    /* Copy existing environment variables */
    for (i = 0; i < envSize; i++) {
        newEnviron[i] = environ[i];
    }

    /* Add the new environment variable */
    newEnviron[envSize] = newEnvVar;
    newEnviron[envSize + 1] = NULL;

    /* Update the global environ pointer */
    environ = newEnviron;

    return 0;
}

int _unsetenv(const char *name) {
  char *existingValue;
  char **env;
  char **next;
   char *name_clone = _strdup(name);
  
    if (name == NULL || *name == '\0' || _strchr(name_clone, '=') != NULL) {
        return -1 /* Invalid input */ ;
    }
    /* Check if the variable exists */
    existingValue = _getenv(name);

    /* If the variable does not exist, do nothing */
    if (existingValue == NULL) {
        return 0;
    }

    /* Iterate through the environment variables to find the variable */

    for (env = environ; *env != NULL; env++) {
        /* Check if the current environment variable starts with the specified name */
        if (_strncmp(*env, name, _strlen(name)) == 0 && (*env)[_strlen(name)] == '=') {
            /* Free the memory allocated for the environment variable */
            free(*env);

            /* Shift the remaining environment variables down to fill the gap */
            next = env + 1;
            while (*next != NULL) {
                *env++ = *next++;
            }
            *env = NULL;

            return 0;
        }
    }

    return -1 /* Variable not found */ ;
}
