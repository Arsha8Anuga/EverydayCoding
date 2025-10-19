#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define NO_DESC



typedef enum{ 
    NOT_STARTED_YET,
    IN_PROGRESS, 
    DONE, 
    LATE
}StatusAssign;

typedef struct{ 
    unsigned int id;
    char* title; 
    char* description;
    StatusAssign status;
}TodoList;


static unsigned int id_cntr = 1;


TodoList* initTodo(char*, char*, StatusAssign);

TodoList* initTodo(char* title, char* desc, StatusAssign stat){

    if(!title) return NULL;
    
    TodoList* obj = (TodoList*)malloc(sizeof(TodoList));
    if(!obj) return NULL;
    
    int len_title = strlen(title);
    int len_desc = (desc ? strlen(desc) : 0);

    obj->title = (char*)malloc((len_title + 1) * sizeof(char));
    obj->description = (char*)malloc((len_desc + 1) * sizeof(char));
    
    obj->title = malloc(len_title + 1);
    if (!obj->title) {
        free(obj);
        return NULL;
    }

    obj->description = malloc(len_desc + 1);
    if (!obj->description) {
        free(obj->title);
        free(obj);
        return NULL;
    }
    
    strcpy(obj->title, title);
    if(desc){ 
      strcpy(obj->description, desc);
    }else{ 
      obj->description[0] = '\0';
    }
    

    obj->status = (!stat ? NOT_STARTED_YET : stat);
    obj->id = id_cntr++;

    return obj;
}

