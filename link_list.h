/**
* @file link_list.
* @brief function prototypes and struction definitions for doubly linked list
* @author Andrew Kuklinski
* @date 02/18/2018
**/


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>


#ifndef link_list_h_
#define link_list_h_

#define GET_LIST_CONTAINER(addr,type,member) ({            \
        const typeof(((type*)0)->member)*__mptr = (addr);    \
        (type*)((char*)__mptr - offsetof(type,member));})


typedef struct llnode_t{
  struct llnode_t * prev;
  struct llnode_t * next;
}llnode_t;

typedef struct lldata_t{
  char data;
  uint32_t count;
  llnode_t linker;
}lldata_t;

llnode_t* destroy(llnode_t * node);

llnode_t* insert_at_begin(llnode_t * node, uint32_t info);

llnode_t* insert_at_end(llnode_t * node, char info);

llnode_t* insert_at_position(llnode_t * node, uint32_t info, uint32_t index);

llnode_t* delete_from_begin(llnode_t * node);

llnode_t* delete_from_end(llnode_t * node);

llnode_t* delete_from_position(llnode_t * node, uint32_t index);

uint32_t size(llnode_t * node);


#endif /*__link_list_h__*/
