#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include "pthread_ex.h"

pthread_t metrics, llsearch;
pthread_attr_t attr;

static FILE *hw3log;

int main(int argc, char *argv[])
{
  struct timeval my_timestamp;
  input_var * varstruct;
  
  varstruct = (input_var*)malloc(sizeof(varstruct));
  varstruct->inputfile = argv[1];
  varstruct->member1 = 34;

  hw3log = fopen(varstruct->inputfile, "a+");
  if(hw3log == NULL)
    {
      printf("output file could not be accessed\n");
      return 1;
    }
  fprintf(hw3log,"***main fxn thread starting***\n");
  gettimeofday(&my_timestamp,NULL);
  fprintf(hw3log,"timestamp: %ld.%ld\n",my_timestamp.tv_sec, my_timestamp.tv_usec);
  fprintf(hw3log,"main thread posixID: %lu\n", pthread_self());
  fprintf(hw3log,"main thread linuxID: %d\n", getpid());
  fclose(hw3log);

  pthread_attr_init(&attr);

  
  //m_thread.member1 = 31;
  //m_thread.member2 = 89;
  
  int checking;
  checking = pthread_create(&metrics, &attr, metrics_fxn, (void*)&varstruct);
  if(checking)
    {
      fprintf(stderr, "error creating metrics thread");
      return -1;
    }

  /* checking = pthread_create(&llsearch, &attr, llsearch_fxn, (void*)&ll_thread);
  if(checking)
    {
      fprintf(stderr, "error creating metrics thread");
      return -1;
      }*/
  
  pthread_join(metrics, NULL);
  //pthread_join(llsearch,NULL);

  hw3log = fopen(varstruct->inputfile, "a+");
  fprintf(hw3log,"***Main Thread Exit***\n");
  gettimeofday(&my_timestamp,NULL);
  fprintf(hw3log,"timestamp: %ld.%ld\n\n",my_timestamp.tv_sec, my_timestamp.tv_usec);
  fclose(hw3log);
  free(varstruct);
  return 0;
}


