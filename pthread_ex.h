/**
* @file pthread_ex.h
* @brief function definitions for threading example in hw3
* @author Andrew Kuklinski
* @date 02/18/2018
**/



#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

extern pthread_mutex_t locking;

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

//signal handler to exit metric thread
void metric_exit(int signum);

//signal handler to exit search thread
void search_exit(int signum);

/*create, initialize, and start a posix counter that sends
 *a signal to run a function.  arguments: how many nanoseconds between 
 *timer roll over*/
void metric_counter_init(unsigned long long int firedelay) ;
