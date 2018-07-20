#include <stdio.h>
#include <pthread.h>

#define pnum 5
pthread_mutex_t mutex[pnum];
int eatime[pnum];

void* thread_func( void* arg )
{
	int i;
	int max_delay = 1000000;
	int delay;
	int phid = *(int*)arg;
	int lid = (phid+1)%pnum;
	int rid = phid;
	while(1)
	{
		printf("%d: picking chopsticks\n", phid);
		pthread_mutex_lock(&mutex[lid]);
		for(i=0, delay=rand()%max_delay; i<delay; i++);
		
		pthread_mutex_lock(&mutex[rid]);
		printf("%d: ** eating **\n", phid);
		for(i=0, delay=rand()%max_delay; i<delay; i++);
		eatime[phid]++;
		pthread_mutex_unlock(&mutex[lid]);
		
		for(i=0, delay=rand()%max_delay; i<delay; i++);
		pthread_mutex_unlock(&mutex[rid]);
		
		for(i=0, delay=rand()%max_delay; i<delay; i++);
		printf("%d: thinking");
	}
}

void* thread_func2(void* arg)
{
	int i;
	while(1)
	{
		sleep(10);
		printf("eating time");
		for(i=0; i<pnum; i++)
			printf(" %d", eatime[i]);
		printf("\n");
	}	
}

int main()
{
	int i;
	int phid[pnum] = {0, 1, 2, 3, 4};
	int eatime[pnum] = {0, 0, 0, 0, 0};
	pthread_t tid[pnum];
	pthread_t tid1;
	srand(time(NULL));	

	for( i = 0; i < pnum; i++ ) 
		pthread_mutex_init(&mutex[i], NULL);

	for( i = 0; i < pnum; i++ ) 	
	{
		pthread_create(&tid[i], NULL, thread_func, &phid[i]);
	}
	pthread_create(&tid1, NULL, thread_func2, NULL);
	for( i = 0; i < pnum; i++ )
		pthread_join(tid[i], NULL);
	return 0;
}
