#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>
#include "var.h"

Memory* jash_AddVar(char* name, char* data, Memory* list) {
    Memory* tmp = (Memory*)malloc(sizeof(Memory));
    if (tmp == NULL) {
        printf("I found a error\n");
        exit(-1);
    }
    tmp->id = 1; // it will be random numbers
    tmp->name = name;
    tmp->type = 1;
    tmp->live = 1;
    tmp->values = data;
    HASH_ADD_STR(list, name, tmp);
    printf("Add new item to the list!\n");
    free(tmp);
    return list;
}

Memory* jash_GetVar(char* name, Memory* list) {
    Memory* res = NULL;
    char* username = name;
    HASH_FIND_STR(list, username, res);
    // free(res);
    return res;
}