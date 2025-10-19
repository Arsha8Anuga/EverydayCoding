
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

typedef struct{
  void** data;
  int* dimension;
  size_t size_dim;
  size_t size;
  size_t cap;
  void* ext;
}d_array;

typedef struct{
  int* dimension;
  size_t size_dim;
}init_d_arr;


d_array* initDynamicArray(init_d_arr*);
int8_t pushDynamicArray(d_array*, void*);
int8_t capDetectorDynamicArray(d_array*);


d_array* initDynamicArray(init_d_arr* init){
  if(!init || !init->dimension || init->size_dim == 0) return NULL;

  d_array* arr = malloc(sizeof(d_array));
  if(!arr) return NULL;

  arr->dimension = malloc(init->size_dim * sizeof(int));
  if(!arr->dimension){
    free(arr);
    return NULL;
  }

  memcpy(arr->dimension, init->dimension, init->size_dim * sizeof(int));


  arr->size_dim = init->dimension;

  size_t cap = 1;

  for(int i = 0; i < init->size_dim; i++){
    cap *= *(arr->dimension + i);
  }

  arr->cap = cap;
  arr->size = 0;

  arr->data = calloc(cap, sizeof(void*));
  if(!arr->data){
    free(arr->dimension);
    free(arr);
    return NULL;
  }

  arr->ext = NULL;
  return arr;
}

int8_t pushDynamicArray(d_array* arr, void* val){

  if(!arr) return -1;
  
  capDetectorDynamicArray(arr);

  int cursor = arr->size;
  while(arr->data[cursor] && cursor <= arr->cap){
    cursor++;
  }

  arr->data[cursor] = val;
  arr->size++;
   

  return 0;

}

int8_t capDetectorDynamicArray(d_array* arr){
    if(!arr) return -1;

    size_t newCap = 0;
    
    if((arr->size + 1) >= arr->cap){
        
        newCap = arr->cap * 2;
        
        void** newData = realloc(arr, newCap * sizeof(void*));
        if(!newData) return -1;

        arr->cap = newCap;
        arr->data = newData;
        
    }else if(arr->size < (arr->cap / 2)){
        
        newCap = arr->cap / 2;

        void** newData = realloc(arr->data, newCap * sizeof(void*));
        if(!newData) return -1;

        arr->cap = newCap;
        arr->data = newData;
    }

    return 0;
}
