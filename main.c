#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//#include <sys/types.h>
#include <unistd.h>
#include "pthread_ex.h"

pthread_t metrics, llsearch;
pthread_attr_t attr;

FILE *hw3log;



int main(int argc, char *argv[])
{
  time_t my_ctime = time(NULL);
  struct tm tm = *localtime(&my_ctime);
  input_var * varstruct;
  varstruct = malloc(sizeof(varstruct));
  varstruct->inputfile = argv[1];

  hw3log = fopen(varstruct->inputfile, "a+");
  if(hw3log == NULL)
    {
      printf("output file could not be accessed\n");
      return 1;
    }
  fprintf(hw3log,"***main fxn thread starting***\n");
  fprintf(hw3log,"%02d/%02d/%04d || %02d:%02d:%02d\n"
	  ,tm.tm_mon+1,tm.tm_mday, tm.tm_year+1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
  fprintf(hw3log,"main thread posixID: %lu\n", pthread_self());
  fprintf(hw3log,"main thread linuxID: %d\n", getpid());

  fclose(hw3log);
  
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


