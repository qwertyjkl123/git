 ///
 /// @file    pthread_mutex.c
 /// @author  liweihang
 /// @date    2018-03-22 00:24:16
 ///
 
#include "func.h"
#define N  10000000
pthread_mutex_t mutex;

void * threadfunc(void * p)
{
	int i = 0;
	int *l = (int *)p;

	for(i = 0;i < N;i++)
	{
		pthread_mutex_lock(&mutex);
		*l = *l + 1;
		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(NULL);
}

int main()
{
	pthread_t pthid;
	pthread_mutex_init(&mutex,NULL);
	int l = 0;

	pthread_create(&pthid,NULL,threadfunc,(void *)&l);

	int i;
	for(i = 0;i < N;i++)
	{
		pthread_mutex_lock(&mutex);
		l = l + 1;
		pthread_mutex_unlock(&mutex);
	}

	pthread_join(pthid,NULL);
	printf("the result = %d\n",l);

	int ret = pthread_mutex_destroy(&mutex);
	if(ret != 0)
	{
		printf("pthread_mutex_destory failed ret = %d\n",ret);
		return -1;
	}

	return 0;
}
