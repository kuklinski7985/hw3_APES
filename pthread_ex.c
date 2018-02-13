#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
  

void *metrics_fxn(void *param)
{
  printf("metrics_fxn is now printing something\n\n");
  return NULL;
}
