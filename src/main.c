#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cmd.h"

#define LASH_BUFFER_SIZE 1024
#define LASH_TOEKN_BUFFER_SIZE 60
#define DELIMITER_TOKEN_SAMPLE " \t\r\n\a"

//#define RUN_CMD(string var) (cmd_##var());

void jash_loop(void);
char* jash_read_line();
char **jash_split_line(char* line);
char* Greetings();
int jash_execute(char **args);

int main(int argc, char **argv) {
  // Load config files, ir any.

  jash_loop();

  // Perform any shutdown/Cleanup code
  return EXIT_SUCCESS;
}

void jash_loop(void) {
  char *line;
  char **args;
  int status = 1;
  inner_builtin_variables();
  printf("%s\n", Greetings());
  do {
    printf("> ");
    line = jash_read_line();
    if (strcmp(line, "exit") == 0) {
      break;
    }
    args = jash_split_line(line);
    status = jash_execute(args);
  } while (status);
}

char* Greetings() {
  return "Welcome to Lash shell emulator :D\nTo see commands use `help`\nfor more information https://github.com/ashk123/jash`";
}

int jash_execute(char **args)
{
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < jash_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return jash_launch(args);
}
/*
  Function Declarations for builtin shell commands:
 */
int jash_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    // Child process
    if (execvp(args[0], args) == -1) {
      perror("jash");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // Error forking
    perror("jash");
  } else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

void AllocChecker(char* buffer) {
  if (!buffer) {
    fprintf(stderr, "[ERROR] error malloc function");
    exit(1);
  } /* else {
    printf("without any error");
  } */
}

char** jash_split_line(char* line) {
  int bufsize = LASH_TOEKN_BUFFER_SIZE;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token;
  int position=0;

  if (!tokens) {
    fprintf(stderr, "[ERROR] Alloaction error.\n");
    exit(1);
  }

  token = strtok(line, DELIMITER_TOKEN_SAMPLE);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= LASH_TOEKN_BUFFER_SIZE) {
      bufsize += LASH_TOEKN_BUFFER_SIZE;
      tokens = realloc(tokens, bufsize);
      if (!tokens) {
        fprintf(stderr, "[ERROR] reallocation error.\n");
        exit(1);
      }
    }

    token = strtok(NULL, DELIMITER_TOKEN_SAMPLE);
  }
  tokens[position] = NULL;
  return tokens;
}

char* jash_read_line(void) {
  int bufsize = LASH_BUFFER_SIZE;
  int position = 0;
  char* buffer = malloc(sizeof(char) * bufsize); // it's work like new
  int c;
  if (!buffer) {
    fprintf(stderr, "There is error in line 44");
    exit(1);
  }  
  // AllocChecker(buffer);

  while (1) {
    c = getchar();
    if (c == EOF || c == '\n'){
      buffer[position] = '\0'; // end of the line
      return buffer; // return the text when it's the end of the line
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize) {
      bufsize += LASH_BUFFER_SIZE;
      buffer = realloc(buffer, bufsize);
        if (!buffer) {
          fprintf(stderr, "There is error in line 44");
          exit(1);
        }  
    }
  }
}
