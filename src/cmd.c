#include <stdio.h>
#include <stdlib.h>

int jash_cd(char **args);
int jash_help(char **args);
int jash_exit(char **args);
int jash_rloop();
char** ParseLoopCmd(char** args);

char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "loop"
};

int (*builtin_func[]) (char **) = {
  &jash_cd,
  &jash_help,
  &jash_exit,
  &jash_rloop
};


int jash_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int jash_rloop(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "jash: expexted argument for looping\n");
    return 1;
  }
  char** res = ParseLoopCmd(args);
  for (int i = 0; i < atoi(args[1]); i++) {
    jash_launch(args + 2);
  }
  return 1;
}

char** ParseLoopCmd(char** args) {
}

int jash_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "jash: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("jash");
    }
  }
  return 1;
}

int jash_help(char **args)
{
  int i;
  Greetings();
  printf("Usage: jash <command>\n\n");
  printf("The following are built in:\n");

  for (i = 0; i < jash_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int jash_exit(char **args)
{
  return 0;
}


