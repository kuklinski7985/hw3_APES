#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


//struct to be used to pass information between threads
typedef struct{
  int memberA;
  int memberB;

}input_var;           //struct is shared by all threads

//function to report CPU utilization metrics to a log file
void *metrics_fxn(void *param);
