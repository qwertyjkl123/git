 ///
 /// @file    pthread.c
 /// @author  liweihang
 /// @date    2018-03-21 06:56:09
 ///

#include "func.h" 

void * threadfunc(void *p)
{
	printf("i am thread1\n");
	sleep(2);

	return NULL;
}

int main()
{
	pthread_t pthid;
	pthread_create(&pthid,NULL,threadfunc,NULL);

	printf("i am main thread\n");
	while(1);
	return 0;
}

