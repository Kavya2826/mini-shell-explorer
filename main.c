#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define HISTORY_LIMIT 50

int main(void){
  char command[100];
  char history[HISTORY_LIMIT][100];
  int historyCount = 0;

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

    // Preserve the complete command before parsing it
    char fullCommand[sizeof(command)];
    strcpy(fullCommand, input);

    // Save the command in history
    if (historyCount < HISTORY_LIMIT){
      strcpy(history[historyCount], input);
      historyCount++;
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

    // Built-in command: help
    else if (strcmp(input, "help") == 0){
      printf("Available commands:\n");
      printf("  pwd       - Show current directory\n");
      printf("  cd        - Change current directory\n");
      printf("  mkdir     - Create a directory\n");
      printf("  rmdir     - Remove an empty directory\n");
      printf("  echo      - Display a message\n");
      printf("  cls       - Clear the screen\n");
      printf("  history   - Show previously entered commands\n");
      printf("  help      - Show this help message\n");
      printf("  exit      - Exit Mini Shell Explorer\n");
    }

    // Built-in command: cls
    else if (strcmp(input, "cls") == 0){
      system("cls");
    }

    // Built-in command: mkdir
    else if (strcmp(input, "mkdir") == 0){
      if (argument == NULL){
        printf("Usage: mkdir <directory>\n");
      }
      else if (CreateDirectoryA(argument, NULL) == 0){
        printf("Error: Unable to create directory.\n");
      }
      else{
        printf("Directory created successfully.\n");
      }
    }

    // Built-in command: rmdir
    else if (strcmp(input, "rmdir") == 0){
      if (argument == NULL){
        printf("Usage: rmdir <directory>\n");
      }
      else if (RemoveDirectoryA(argument) == 0){
        printf("Error: Unable to remove directory. It may not exist or may not be empty.\n");
      }
      else{
        printf("Directory removed successfully.\n");
      }
    }

    // Built-in command: echo
    else if (strcmp(input, "echo") == 0){
      if (argument == NULL){
        printf("\n");
      }
      else{
        printf("%s\n", argument);
      }
    }

    // Built-in command: history
    else if (strcmp(input, "history") == 0){
      for (int i = 0; i < historyCount; i++){
        printf("%d  %s\n", i + 1, history[i]);
      }

      if (historyCount == HISTORY_LIMIT){
        printf("Note: History limit reached; newer commands are not being saved.\n");
      }
    }

    // Execute external Windows commands
    else{
      int result = system(fullCommand);

      if (result == -1){
        printf("Error: Unable to start Windows command processor.\n");
      }
    }  }

  return 0;
}
