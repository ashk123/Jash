#include <stdio.h>
#include <stdlib.h>
#include "info.h"
#include <uthash.h>
#include "var.h"

int jash_cd(char **args);
int jash_help(char **args);
int jash_exit(char **args);
int jash_rloop(char **args);
int jash_version(char **args);
int jash_var(char **args);
int jash_gvar(char** args);

char *builtin_str[] = {
  "cd",
  "help",
  "exit",
  "loop",
  "version",
  "var",
  "gvar",
};

int (*builtin_func[]) (char **) = {
  &jash_cd,
  &jash_help,
  &jash_exit,
  &jash_rloop,
  &jash_version,
  &jash_var,
  &jash_gvar,
};

// Main Jash Memory
Memory* mem = NULL;

void inner_builtin_variables() {
	char* version = VERSION;
	mem = jash_AddVar("version", (char*)VERSION, mem);
	mem = jash_AddVar("NAME", "JASH", mem);
	mem = jash_AddVar("PWD", ".", mem);
	printf("[DEBUG] Initial default variables\n");
}

int jash_gvar(char** args) {
  Memory* javab = jash_GetVar(args[1], mem);
  if (javab == NULL) {
	  fprintf(stderr, "[JASH] Can't find that variable\n");
	  return 1; // still be in progres
  };
  printf("%s\n", javab->values);
}
// void concatenate(char *str1, char *str2) {
//     // Move pointer to the end of the first string
//     while (*str1) {
//         str1++;
//     }

//     // Copy characters of the second string to the end of the first string
//     while (*str2) {
//         *str1 = *str2;
//         str1++;
//         str2++;
//     }
//     *str1 = '\0';  // Terminate the concatenated string
// }
int jash_var(char** args) {
  char* value = malloc(sizeof(char*)); // be sure to use malloc when using strcat
  // strcpy(value, "default");
  // printf("%d", strlen(args));
  // char** main = args+1;
  // printf("%s", main[0]);
  for (char** i = args+2; i[0] != NULL; i=i+1) {
  // for (int i = 2; i < strlen(args) - 1; i++) {
    // printf("%s\n", i[0]);
    strcat(value, i[0]);
    strcat(value, " ");
    // printf("%s", nice);
  }
  // strcpy(value, value);
  mem = jash_AddVar(args[1], value, mem);
  printf("this is the value: %s\n", value);
  printf("Jash saved your variable\n");
  // free(value); we can add value to the list of variables and do some GC stuff on them :D
  return 1;
}

int jash_version(char **args) {
  printf("Jash " Year " Version " VERSION "\n");
  return 1;
}

int jash_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

int jash_rloop(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "jash: expexted argument for looping\n");
    return 1;
  }
  for (int i = 0; i < atoi(args[1]); i++) {
    jash_launch(args + 2);
  }
  return 1;
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


