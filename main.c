
#include <stdio.h>
#include <string.h>

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

    if (strcmp(command, "exit") == 0){
      printf("Goodbye!\n");
      break;
    }

    if (command[0] == '\0'){
      continue;
    }

    printf("You entered: %s\n", command);
  }
  return 0;
}
