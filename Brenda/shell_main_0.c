#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Data structure to represent the command line interface
struct command {
    char *name;
    char *args[10];
};

// Function to tokenize the command line input
void tokenize(char *input, char **tokens) {
    char *ptr = input;
    int i = 0;
    while (*ptr != '\0') {
        // Split the input into tokens using spaces or tabs as delimiters
        if (*ptr == ' ' || *ptr == '\t') {
            // Add the token to the list
            tokens[i++] = ptr;
            // Advance the pointer past the token
            ptr += strlen(ptr);
        }
    }
    // Add the final token to the list
    tokens[i++] = ptr;
}

// Function to parse the tokens into a command and its arguments
struct command *parse(char **tokens) {
    // Initialize the command struct
    struct command *cmd = malloc(sizeof(struct command));
    cmd->name = tokens[0];
    cmd->args[0] = NULL;
    int i = 1;
    // Parse the tokens into arguments
    while (tokens[i] != NULL) {
        cmd->args[i-1] = tokens[i];
        i++;
    }
    return cmd;
}

// Function to execute the command
void execute(struct command *cmd) {
    // Implement the command execution logic here
    // For example, if the command is "ls", list the files and directories in the current directory
    if (strcmp(cmd->name, "ls") == 0) {
        // List the files and directories in the current directory
        printf("Current directory: \n");
        char *dir = ".";
        DIR *d;
        struct dirent *de;
        d = opendir(dir);
        if (d == NULL) {
            perror("Error opening directory");
            return;
        }
        while ((de = readdir(d)) != NULL) {
            printf("%s\n", de->d_name);
        }
        closedir(d);
    }
}

// Function to print the output
void print(struct command *cmd) {
    // Implement the output printing logic here
    // For example, if the command is "ls", print the list of files and directories
    if (strcmp(cmd->name, "ls") == 0) {
        printf("Files and directories in the current directory:\n");
        char *dir = ".";
        DIR *d;
        struct dirent *de;
        d = opendir(dir);
        if (d == NULL) {
            perror("Error opening directory");
            return;
        }
        while ((de = readdir(d)) != NULL) {
            printf("%s\n", de->d_name);
        }
        closedir(d);
    }
}

int main() {
    // Read input from the user
    char input[1024];
    printf("$ ");
    fgets(input, 1024, stdin);
    // Tokenize the input
    char *tokens[10];
    tokenize(input, tokens);
    // Parse the tokens into a command and its arguments
    struct command *cmd = parse(tokens);
    // Execute the command
    execute(cmd);
    // Print the output
    print(cmd);
    // Free the command struct
    free(cmd);
    return 0;
}
