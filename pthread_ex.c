#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "pthread_ex.h"
  
extern int bizzounce;

void *metrics_fxn(void *param)
{
  static FILE *hw3log1;
  input_var * inner_struct = (input_var*) param;
  struct timeval my_timestamp;

  pthread_mutex_lock(&locking);
  hw3log1 = fopen(inner_struct->inputfile,"a+");
  if(hw3log1 == NULL)
    {
      printf("output file could not be accessed\n");
      return (void*)1;
    }

  fprintf(hw3log1,"******************Metrics Fxn thread starting*****************\n");
  gettimeofday(&my_timestamp,NULL);
  fprintf(hw3log1,"timestamp in sec: %ld.%ld\n",my_timestamp.tv_sec, my_timestamp.tv_usec);
  fprintf(hw3log1,"metrics thread posixID: %lu\n", pthread_self());
  fprintf(hw3log1,"metrics thread linuxID: %d\n\n", getpid());
  
  fclose(hw3log1);
  pthread_mutex_unlock(&locking);

  signal(SIGUSR1, metric_exit);
  unsigned long long int delay_time = 100000000;  //in nanoseconds
  metric_counter_init(delay_time);
  cpustats = fopen("/proc/stat", "r");
  while(bizzounce == 0);
  fclose(cpustats);
}


void *llsearch_fxn(void *param)
{
  static FILE *hw3log2;
  input_var * llthread_struct = (input_var*) param;
  struct timeval my_timestamp;

  pthread_mutex_lock(&locking);

  hw3log2 = fopen(llthread_struct->inputfile,"a+");
  if(hw3log2 == NULL)
    {
      printf("output file could not be accessed\n");
      return (void*)1;
    }

  fprintf(hw3log2,"******************Linked List Fxn Thread Starting*****************\n");
  gettimeofday(&my_timestamp,NULL);
  fprintf(hw3log2,"timestamp in sec: %ld.%ld\n",my_timestamp.tv_sec, my_timestamp.tv_usec);
  fprintf(hw3log2,"metrics thread posixID: %lu\n", pthread_self());
  fprintf(hw3log2,"metrics thread linuxID: %d\n\n", getpid());


  //do linked list sorting stuff here.


  
  fclose(hw3log2);
  pthread_mutex_unlock(&locking);
  signal(SIGUSR2, search_exit);
  while(bizzounce == 0);

}

void metric_exit(int signum)
{
  printf("exit signal received : metric thread!\n\n");
  bizzounce=1;
}

void search_exit(int signum)
{
  printf("exit singal received : search thread\n\n");
  bizzounce=1;
}

void handler_timer(union sigval arg)
{
  //static int counter = 0;
  //counter++;
  //printf("timer going off: %d\n",counter);
  while(fscanf(cpustats
  
}

void metric_counter_init(unsigned long long int firedelay)     //firedelay is number of nanoseconds
{
  timer_t timer;
  struct itimerspec timer_interval;    //sets values for timer interval and initial expiration
  struct sigevent timer_actions;       //descibe the way a process is to be notified about and event
  
  timer_actions.sigev_notify = SIGEV_THREAD;
  timer_actions.sigev_value.sival_ptr = &timer;
  timer_actions.sigev_notify_function = handler_timer;
  timer_actions.sigev_notify_attributes = NULL;

  timer_interval.it_value.tv_sec = firedelay / 10000000000;
  timer_interval.it_value.tv_nsec = firedelay % 10000000000;
  timer_interval.it_interval.tv_sec = timer_interval.it_value.tv_sec;//0;
  timer_interval.it_interval.tv_nsec = timer_interval.it_value.tv_nsec;//0;

  int timer_status;
  timer_status = timer_create(CLOCK_REALTIME, &timer_actions, &timer);  //creates new timer
  if(timer_status == -1)
    {
      printf("timer create failed\n");
      return;
    }

  timer_status = timer_settime(timer, 0, &timer_interval,0);    //this starts the counter
  if(timer_status == -1)
    {
      printf("timer start failed\n");
      return;
    }
}
