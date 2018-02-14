#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "pthread_ex.h"

pthread_t metrics, llsearch;
pthread_attr_t attr;


int main(int argc, char *argv[])
{

  FILE *hw3log;

  printf("shit broke\n");
  input_var * varstruct;
  varstruct = malloc(sizeof(varstruct));
  varstruct->inputfile = argv[1];
  printf("good\n");
  printf("input file name: %s\n",varstruct->inputfile);
  //hw3log = fopen(main_copy->inputfile, "a+");
  //fprintf(hw3log, "lets see if this works\n");
  //fclose(hw3log);
  
  /*main_copy->hw3log = argv[1];
  main_copy->hw3log = fopen(argv[1], "w");
  if(main_copy->hw3log == NULL)
    {
      printf("shit broke");
      return -1;
    }
  char * testing = "this is a test";
  fprintf(hw3log, "%s", testing);
  fprintf(main_copy->hw3log, "**Main Thread Begin**\n");
  fprintf(main_copy->hw3log, "POSIX Thread ID: %lu\n", pthread_self());
  fprintf(main_copy->hw3log, "Linux Thread ID: %d\n", getpid());
  fclose(main_copy->hw3log);*/
  
  /* pthread_attr_init(&attr);
  input_var m_thread, ll_thread;
  m_thread.member1 = 31;
  m_thread.member2 = 89;
  
  int checking;
  checking = pthread_create(&metrics, &attr, metrics_fxn, (void*)&m_thread);
  if(checking)
    {
      fprintf(stderr, "error creating metrics thread");
      return -1;
    }

  checking = pthread_create(&llsearch, &attr, llsearch_fxn, (void*)&ll_thread);
  if(checking)
    {
      fprintf(stderr, "error creating metrics thread");
      return -1;
    }
  
  pthread_join(metrics, NULL);
  pthread_join(llsearch,NULL);*/
  return 0;
}


