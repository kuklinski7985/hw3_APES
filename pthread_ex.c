#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pthread_ex.h"
  

void *metrics_fxn(void *param)
{
  static FILE *hw3log1;
  input_var * inner_struct = (input_var*) &param;

  //inner_struct =(input_var*)malloc(sizeof(inner_struct));

  printf("thread struct file name: %s\n\n",inner_struct->inputfile);
  return NULL;
}


void *llsearch_fxn(void *param)
{
  printf("llsearch_fxn started\n\n");
  return NULL;
}

