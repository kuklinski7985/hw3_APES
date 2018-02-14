#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


//struct to be used to pass information between threads
typedef struct{
  int member1;
  int member2;
  //FILE *hw3log;
  char * inputfile;
  
}input_var;           //struct is shared by all threads

//function to report CPU utilization metrics to a log file
void *metrics_fxn(void *param);

//function to search a file and produce a linked list of the contents
void* llsearch_fxn(void *param);
