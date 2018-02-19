/**
* @file main.c
* @brief main file for hw3, covering threading
* @author Andrew Kuklinski
* @date 02/18/2018
**/


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "pthread_ex.h"

pthread_t metrics, llsearch;
pthread_attr_t attr;

static FILE *hw3log;

pthread_mutex_t locking;

int bizzounce=0;
input_var * varstruct;

int main(int argc, char *argv[])
{
  struct timeval my_timestamp;

  if(pthread_mutex_init(&locking, NULL)!= 0)
    {
      printf("mutex init failed\n");
      return 1;
    }
  
  //input_var * varstruct;
  
  varstruct = (input_var*)malloc(sizeof(varstruct));
  varstruct->inputfile = argv[1];

  hw3log = fopen(varstruct->inputfile, "a+");
  if(hw3log == NULL)
    {
      printf("output file could not be accessed\n");
      return 1;
    }
  fprintf(hw3log,"******************main fxn thread ENTER*****************\n");
  gettimeofday(&my_timestamp,NULL);
  fprintf(hw3log,"timestamp: %ld.%ld\n",my_timestamp.tv_sec, my_timestamp.tv_usec);
  fprintf(hw3log,"main thread posixID: %lu\n", pthread_self());
  fprintf(hw3log,"main thread linuxID: %d\n\n", getpid());
  fclose(hw3log);

  pthread_attr_init(&attr);
  
  int checking;
  checking = pthread_create(&metrics, &attr, metrics_fxn, (void*)varstruct);
  if(checking)
    {
      fprintf(stderr, "error creating metrics thread");
      return -1;
    }

  checking = pthread_create(&llsearch, &attr, llsearch_fxn, (void*)varstruct);
  if(checking)
    {
      fprintf(stderr, "error creating metrics thread");
      return -1;
    }
  
  pthread_join(metrics, NULL);
  pthread_join(llsearch,NULL);

  pthread_mutex_destroy(&locking);

  hw3log = fopen(varstruct->inputfile, "a+");
  fprintf(hw3log,"*****************Main Thread Exit***************************\n");
  gettimeofday(&my_timestamp,NULL);
  fprintf(hw3log,"timestamp: %ld.%ld\n\n",my_timestamp.tv_sec, my_timestamp.tv_usec);
  fclose(hw3log);
  free(varstruct);
  return 0;
}


