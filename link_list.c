#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "link_list.h"

llnode_t* destroy(llnode_t * node);

llnode_t* insert_at_begin(llnode_t * node, uint32_t info)
{
  lldata_t * newcontainer;
  newcontainer = (lldata_t*)malloc(sizeof(lldata_t));
  if(newcontainer == NULL)
    return NULL;

  if(node == NULL)
    {
      ((newcontainer->linker).prev) = NULL;
      ((newcontainer->linker).next) = NULL;
      newcontainer->data = info;
      return &(newcontainer->linker);
    }

  ((newcontainer->linker).prev) = NULL;
  ((newcontainer->linker).next) = node;
  node->prev = &(newcontainer->linker);
  newcontainer->data = info;
    
  return &(newcontainer->linker);
}

llnode_t* insert_at_end(llnode_t * node, char info)
{
  lldata_t * newcontainer;
  newcontainer = (lldata_t*)malloc(sizeof(lldata_t));
  if(newcontainer == NULL)
    return NULL;
  //condition to start a new linked list
  if(node == NULL)
    {
      ((newcontainer->linker).prev) = NULL;
      ((newcontainer->linker).next) = NULL;
      newcontainer->data = info;
      newcontainer->count = 0;
      return &(newcontainer->linker);
    }

  llnode_t * startingnode;
  startingnode = node;
  while(node->next != NULL)
    {
      node = node->next;
    }

  node->next = &(newcontainer->linker);
  ((newcontainer->linker).next) = NULL;
  ((newcontainer->linker).prev) = node;
  newcontainer->data = info;
  newcontainer->count = 0;
  /*uint32_t distance;
  distance = size(node);
  ((newcontainer->linker).prev) = node+distance;
  ((newcontainer->linker).next) = NULL;
  node->next += distance;
  node->next = &(newcontainer->linker);
  newcontainer->data = info;*/
  return startingnode;
  
}

llnode_t* insert_at_position(llnode_t * node, uint32_t info, uint32_t index);

llnode_t* delete_from_begin(llnode_t * node);

llnode_t* delete_from_end(llnode_t * node);

llnode_t* delete_from_position(llnode_t * node, uint32_t index);

uint32_t size(llnode_t * node)
{
  uint32_t count;
  count = 0;
  if((node->next) == NULL)
    {
      count++;
      return count;
    }

  llnode_t *travel = node;
  while(travel != NULL)
    {
      
      count++;
      travel = travel->next;
    }
  return count;
}

/*typedef struct llnode_t{
  struct llnode_t * prev;
  struct llnode_t * next;
}llnode_t;

typedef struct lldata_t{
  char data;
  uint32_t count;
  llnode_t linker;
}lldata_t;
*/
