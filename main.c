#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "pthread_ex.h"



int main(int argc, char *argv[])
{

  pthread_t metrics;
  pthread_attr_t attr;
  int checking;
  checking = pthread_create(&metrics, NULL, metrics_fxn, NULL);
  if(checking)
    {
      fprintf(stderr, "error creating metrics thread");
      return -1;
    }
  


  pthread_join(metrics, NULL);
  
  
}


