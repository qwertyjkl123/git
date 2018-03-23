 ///
 /// @file    pthread_saletickets.c
 /// @author  liweihang
 /// @date    2018-03-22 17:43:51
 ///
 
#include "func.h"

int tickets = 20;

typedef struct 
{
	pthread_mutex_t mutex;
}ticket;

void * salewinds1(void * arg)
{	
	ticket * t = (ticket *) arg;
	pthread_mutex_lock(&t->mutex);
	while(1)
	{
		if(tickets > 0)
		{
			printf("thread1开始售票...\n");
			tickets --;
			pthread_mutex_unlock(&t->mutex);
		}else
		{
			printf("票已售罄...\n");
			break;
		}
		sleep(1);
	}
	pthread_mutex_unlock(&t->mutex);
	pthread_exit((void *)1);
}

void * salewinds2(void * arg)
{	
	ticket * t = (ticket *) arg;
	pthread_mutex_lock(&t->mutex);
	while(1)
	{
		if(tickets > 0)
		{
			printf("thread2开始售票...\n");
			tickets --;
			pthread_mutex_unlock(&t->mutex);
		}else
		{
			printf("票已售罄...\n");
			break;
		}
		sleep(1);
	}
	pthread_mutex_unlock(&t->mutex);
	pthread_exit((void *)2);
}

int main()
{	
	ticket t;
	pthread_t pthid1,pthid2;
	int ret = pthread_mutex_init(&t.mutex,NULL);
	if(ret != 0)
	{
		printf("pthread_mutex_init is wrong,the errornum is %d\n",ret);
		return -1;
	}
	pthread_create(&pthid1,NULL,salewinds1,&t);
	pthread_create(&pthid2,NULL,salewinds2,&t);

	
	int l;
	pthread_join(pthid1,(void **)&l);
	printf("thread%d 被收取\n",l);
	
	pthread_join(pthid2,(void **)&l);
	printf("thread%d 被收取\n",l);

	pthread_mutex_destroy(&t.mutex);

	return 0;
}
