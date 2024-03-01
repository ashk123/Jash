// when you wanna just Declarae a function 
// (specially when you have pointer function) use extern
extern char *builtin_str[];
extern int (*builtin_func[]) (char **);
int jash_num_builtins();
int jash_launch(char **args);
void inner_builtin_variables();
