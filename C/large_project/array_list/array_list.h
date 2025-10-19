#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stddef.h>

#define UNBOUND_INDEX_OFFSET -1

#define STATUS_SUCCESS 0
#define STATUS_ERR -1

typedef struct{

    void** data;
    size_t cap;
    size_t size;
    void* userdata;

}array_list;

array_list* initArrayList(size_t);
int pushArrayList(array_list*, void*);
int removeArrayList(array_list*);
int insertArrayList(array_list*, void*, int);
int deleteArrayList(array_list*, int);
static int capCheckerArrayList(array_list*);
void freeArrayList(array_list*);

#endif