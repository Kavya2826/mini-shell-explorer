
#include <stdio.h>
#include <string.h>
#include <windows.h>

int main(void){
  char command[100];

  printf("=================================\n");
  printf("       MINI SHELL EXPLORER\n");
  printf("=================================\n");

  while (1){
    printf("MSE> ");

    if (fgets(command, sizeof(command), stdin) == NULL){
      break;
    }

    command[strcspn(command, "\n")] = '\0';

    // Ignore leading spaces and tabs
    char *input = command;

    while (*input == ' ' || *input == '\t'){
      input++;
    }

    // Ignore empty input
    if (*input == '\0'){
      continue;
    }

    // Separate the command from its arguments
    char *argument = NULL;
    char *separator = input;

    while (*separator != '\0' && *separator != ' ' && *separator != '\t'){
      separator++;
    }

    if (*separator != '\0'){
      *separator = '\0';
      argument = separator + 1;

      while (*argument == ' ' || *argument == '\t'){
        argument++;
      }

      // Remove trailing spaces and tabs from the argument
      size_t length = strlen(argument);

      while (length > 0 && (argument[length - 1] == ' ' || argument[length - 1] == '\t')){
        argument[--length] = '\0';
      }

      if (*argument == '\0'){
        argument = NULL;
      }
    }

    // Built-in command: exit
    if (strcmp(input, "exit") == 0){
      printf("Goodbye!\n");
      break;
    }

    // Built-in command: pwd
    else if (strcmp(input, "pwd") == 0){
      char currentDirectory[MAX_PATH];

      DWORD length = GetCurrentDirectoryA(MAX_PATH, currentDirectory);

      if (length == 0){
        printf("Error: Unable to get current directory.\n");
      }
      else if (length >= MAX_PATH){
        printf("Error: Current directory path is too long.\n");
      }
      else{
        printf("%s\n", currentDirectory);
      }
    }

    // Built-in command: cd
    else if (strcmp(input, "cd") == 0){
      if (argument == NULL){
        printf("Usage: cd <directory>\n");
      }
      else if (SetCurrentDirectoryA(argument) == 0){
        printf("Error: Unable to change directory.\n");
      }
    }

    // Unknown command for now
    else{
      printf("Unknown command: %s\n", input);
    }
  }

  return 0;
}