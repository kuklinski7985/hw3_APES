#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include "pthread_ex.h"
#include "link_list.h"
  
extern int bizzounce;
extern input_var *varstruct;

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

  fprintf(hw3log1,"******************Metrics Fxn thread ENTER*********************\n");
  gettimeofday(&my_timestamp,NULL);
  fprintf(hw3log1,"timestamp in sec: %ld.%ld\n",my_timestamp.tv_sec, my_timestamp.tv_usec);
  fprintf(hw3log1,"metrics thread posixID: %lu\n", pthread_self());
  fprintf(hw3log1,"metrics thread linuxID: %d\n\n", getpid());
  
  fclose(hw3log1);
  pthread_mutex_unlock(&locking);

  signal(SIGUSR1, metric_exit);
  unsigned long long int delay_time = 100000000;  //in nanoseconds
  metric_counter_init(delay_time);
  while(bizzounce == 0);

  hw3log1 = fopen(inner_struct->inputfile,"a+");

  fprintf(hw3log1,"******************Metrics Fxn thread EXIT**********************\n");
  gettimeofday(&my_timestamp,NULL);
  fprintf(hw3log1,"timestamp in sec: %ld.%ld\n\n",my_timestamp.tv_sec, my_timestamp.tv_usec);

  fclose(hw3log1);
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

  fprintf(hw3log2,"******************Linked List Fxn Thread ENTER*****************\n");
  gettimeofday(&my_timestamp,NULL);
  fprintf(hw3log2,"timestamp in sec: %ld.%ld\n",my_timestamp.tv_sec, my_timestamp.tv_usec);
  fprintf(hw3log2,"metrics thread posixID: %lu\n", pthread_self());
  fprintf(hw3log2,"metrics thread linuxID: %d\n\n", getpid());
  fclose(hw3log2);
  pthread_mutex_unlock(&locking);

  llnode_t * llnode;
  llnode_t * firstnodeaddr;
  lldata_t * data_wrap;
  FILE * valentines;
  char valchar;
  uint32_t char_count;

  valentines = fopen("valentinesday_testing.txt","r");
  if(valentines == NULL)
    {
      printf("cannot open valentinesday.txt\n");
      return (void*)1;
    }

  valchar = fgetc(valentines);
  printf("got char: %c\n",valchar);
  
  llnode = insert_at_end(NULL, valchar);    //llist contains the start point of the linked list
  firstnodeaddr = llnode;
  data_wrap = GET_LIST_CONTAINER(llnode,lldata_t,linker);
  data_wrap->count = 1;
  //printf("addr of node: %p | data: %d | count: %d\n", llnode, (data_wrap->data),(data_wrap->count));

  while(valchar != EOF)
    {
      int flag = 0;
      valchar = fgetc(valentines);
      printf("got char: %c\n",valchar);
      while(flag == 0)
	{
	  if(valchar == (data_wrap->data))
	    {
	      (data_wrap->count)++;
	      flag = 1;
	      printf("matched\n");
	    }
	  else if((llnode->next) == NULL)
	  {
	    //if(llnode->next == NULL)
	    //{
		  llnode = insert_at_end(llnode,valchar);
		  data_wrap = GET_LIST_CONTAINER(llnode,lldata_t,linker);
		  (data_wrap->count)++;
		  flag = 1;
		  printf("new node\n");
		}
	      else
		{
		  llnode = (llnode->next);
		  //printf("traverse\n");
		}
	      }
      //}
      	llnode = firstnodeaddr;
	data_wrap = GET_LIST_CONTAINER(llnode,lldata_t,linker);
	printf("reset\n\n");
    }
  fclose(valentines);
  
  uint32_t ll_size = size(firstnodeaddr);
  printf("size of linked list %d\n",ll_size);

  signal(SIGUSR2, search_exit);
  //while(bizzounce == 0);

  hw3log2 = fopen(llthread_struct->inputfile,"a+");
  fprintf(hw3log2,"******************Linked List Fxn Thread EXIT*****************\n");
  gettimeofday(&my_timestamp,NULL);
  fprintf(hw3log2,"timestamp in sec: %ld.%ld\n\n",my_timestamp.tv_sec, my_timestamp.tv_usec);

  fclose(hw3log2);
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
  
  pthread_mutex_lock(&locking);
  FILE *hw3log4, *cpustat;

  hw3log4 = fopen(varstruct->inputfile, "a+");

  if(hw3log4 == NULL)
    {
      printf("problem with open log file\n");
      return;
    }
  
  cpustat = fopen("/proc/stat", "r");
  if(cpustat == NULL)
    {
      printf("problem with open CPU file\n");
      return;
    }

  char cpu_char = fgetc(cpustat);
  while(cpu_char != EOF)
    {
      fputc(cpu_char, hw3log4);
      cpu_char = fgetc(cpustat);
    }
  
  pthread_mutex_unlock(&locking);
  fclose(hw3log4);
  fclose(cpustat);
}


 //firedelay is number of nanoseconds
void metric_counter_init(unsigned long long int firedelay)    
{
  timer_t timer;
  //sets values for timer interval and initial expiration
  struct itimerspec timer_interval;

  //descibe the way a process is to be notified about and event
  struct sigevent timer_actions;       
  
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
