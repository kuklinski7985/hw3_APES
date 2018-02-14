#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pthread_ex.h"
  

void *metrics_fxn(void *param)
{
  
  printf("metrics_fxn started\n\n");
  //input_var *in_struct;
  //in_struct = param;
  //printf("member1: %d\n", in_struct->member1);
  //printf("member2: %d\n", in_struct->member2);

  printf("metrics fxn ThreadID: %lu\n", pthread_self());
  return NULL;
}


void *llsearch_fxn(void *param)
{
  printf("llsearch_fxn started\n\n");
  return NULL;
}

