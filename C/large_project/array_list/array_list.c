#include "array_list.h"

array_list* initArrayList(size_t cap){

    if(!cap) return NULL;

    array_list* arr = malloc(sizeof(array_list));
    if(!arr) return NULL;

    arr->data = calloc(cap, sizeof(void*));
    if(!arr->data){
        free(arr);
        return NULL;
    }

    arr->cap = cap;
    arr->size = 0;
    arr->userdata = NULL;

    return arr;

}

int pushArrayList(array_list* arr, void* val){

    if (!arr || !val) return STATUS_ERR;

    arr->data[arr->size] = val;
    arr->size++;

    if(capCheckerArrayList(arr) == -1) {
        arr->size--;
        return STATUS_ERR;
    }

    return STATUS_SUCCESS;

}

int removeArrayList(array_list* arr){

    if(!arr || arr->size == 0) return STATUS_ERR;

    
    arr->size--;
    arr->data[arr->size] = NULL;

    capCheckerArrayList(arr);
    
    return STATUS_SUCCESS;
}

int insertArrayList(array_list* arr, void* val, int index){

    if(!arr || !val || (index >= arr->size) || (index <= UNBOUND_INDEX_OFFSET)) return STATUS_ERR;

    if (capCheckerArrayList(arr) == -1) return STATUS_ERR;

    memmove(
        &arr->data[index+1],
        &arr->data[index],
        (arr->size - index) * sizeof(void*)
    );

    arr->data[index] = val;
    arr->size++;

    return STATUS_SUCCESS;

}

int deleteArrayList(array_list* arr, int index){
    if(!arr || (index >= arr->size) || (index <= UNBOUND_INDEX_OFFSET)) return STATUS_ERR;

    memmove(
        &arr->data[index],
        &arr->data[index + 1],
        ((arr->size - index) - 1 ) * sizeof(void*)
    );

    arr->size--;
    arr->data[arr->size] = NULL;

    capCheckerArrayList(arr);

    return STATUS_SUCCESS;
}

int capCheckerArrayList(array_list* arr){

    if(!arr) return STATUS_ERR;

    size_t newCap = arr->cap;


    if (arr->size >= arr->cap) {
        newCap = arr->cap * 2;
    } else if (arr->size > 0 && arr->size <= arr->cap / 4) {
        newCap = arr->cap / 2;
        if (newCap == 0) newCap = 1;
    }

    
    if (newCap != arr->cap) {

        void** newData = realloc(arr->data, newCap * sizeof(void*));
        if (!newData) return STATUS_ERR;
        arr->cap = newCap;
        arr->data = newData;

    }

    return STATUS_SUCCESS;
}

void freeArrayList(array_list* arr){
    
    if(!arr) return;

    free(arr->data);
    free(arr);

}
