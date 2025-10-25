#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define NO_DESC

typedef enum{
  UPDATE_TITLE,
  UPDATE_DESC,
  UPDATE_STATUS,
} OperationType;

typedef enum{
  NOT_STARTED_YET,
  IN_PROGRESS,
  DONE,
  LATE
} StatusAssign;

typedef struct{
  unsigned int id;
  char *title;
  char *description;
  StatusAssign status;
} TodoList;

static unsigned int id_cntr = 1;

TodoList *createTodo(char*, char*, StatusAssign);
int8_t updateTodo (TodoList*, OperationType,const void*);
static inline int8_t updateTitle(TodoList*, char*);
static inline int8_t updateDesc(TodoList*, char*);
int8_t destroyTodo(TodoList*);

TodoList *createTodo(char* title, char* desc, StatusAssign stat){

  if (!title) return NULL;

  TodoList *obj = (TodoList *)malloc(sizeof(TodoList));
  if (!obj) return NULL;

  int len_title = strlen(title);
  int len_desc = (desc ? strlen(desc) : 0);

  obj->title = (char *)malloc((len_title + 1) * sizeof(char));
  if (!obj->title){
    free(obj);
    return NULL;
  }
  obj->description = (char *)malloc((len_desc + 1) * sizeof(char));
  if (!obj->description){
    
    free(obj->title);
    free(obj);
    return NULL;
  }

  strcpy(obj->title, title);
  if (desc){
    strcpy(obj->description, desc);
  }
  else{
    obj->description[0] = '\0';
  }

  obj->status = (stat >= NOT_STARTED_YET && stat <= LATE) ? stat : NOT_STARTED_YET;
  obj->id = id_cntr++;

  return obj;
}

int8_t updateTodo(TodoList *obj, OperationType op, const void* val){

  if(!obj || !val) return -1;

  switch(op){
    case UPDATE_TITLE:
    case UPDATE_DESC: {
      char* tmp = strdup((const char*)val);
      if (!tmp) return -1; 
      (op == UPDATE_TITLE) 
        ? updateTitle(obj, tmp)
        : updateDesc(obj, tmp);
      break;
    }
    case UPDATE_STATUS: {
      const StatusAssign* s = (const StatusAssign*)val;
      obj->status = *s;
      break;
    }
    default : return -1;
  }

  return 0;
}

static inline int8_t updateTitle(TodoList* obj, char* val){

  if(!obj || !val) return -1;

  free(obj->title);
  obj->title = val;

  return 0;
}

static inline int8_t updateDesc(TodoList* obj, char* val){

  if(!obj || !val) return -1;

  free(obj->description);
  obj->description = val;

  return 0;
}

int8_t destroyTodo(TodoList *obj){
  if (!obj)
    return -1;

  free(obj->title);
  free(obj->description);
  free(obj);

  return 0;
}
