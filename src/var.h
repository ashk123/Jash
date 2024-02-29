
typedef struct Memory {
    int id;
    int type;
    char* name;
    char* values;
    int live;
    UT_hash_handle hh;
} Memory;

Memory* jash_AddVar(char* name, char* data, Memory* list);
Memory* jash_GetVar(char* name, Memory* list);