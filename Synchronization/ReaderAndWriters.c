#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex;
pthread_mutex_t wrt;
int readcount=0;
void *read_func(void *arg)
{
	do{
		pthread_mutex_lock(&mutex);
		readcount++;
		if(readcount==1) 
			pthread_mutex_lock(&wrt);
		pthread_mutex_unlock(&mutex);

		printf("tid=%ld,reading...\n",(unsigned long)pthread_self());
		sleep(1);

		pthread_mutex_lock(&mutex);
		
		printf("tid=%ld,finish...\n",(unsigned long)pthread_self());
		readcount--;

		if(readcount==0)
			pthread_mutex_unlock(&wrt);
		pthread_mutex_unlock(&mutex);
	}while(1);
}


void *write_func(void *arg)
{
	do{
		pthread_mutex_lock(&wrt);
		printf("readcount=%d, \n",readcount);
		printf("tid=%ld, writing....\n",(unsigned long)pthread_self());
		pthread_mutex_unlock(&wrt);
	}while(1);
}

int main(void) 
{
	int i, n=2; pthread_t tid[2*n];
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&wrt, NULL);

	//read threads
	for(i=0; i<n; i++) 
	{
		tid[i]=pthread_self();
		pthread_create(tid+i, NULL, read_func, NULL);
	}

	//write threads
	for(i=2; i<2*n; i++) 
	{
		tid[i]=pthread_self();
		pthread_create(tid+i, NULL, write_func, NULL);
	}

	for(i=0; i<2*n; i++)
		pthread_join(tid[i], NULL);

	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&wrt);
	return 0;
}
