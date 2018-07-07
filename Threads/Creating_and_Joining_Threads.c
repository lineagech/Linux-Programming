#include <stdio.h>
#include <pthread.h>
void *thread_func(void *arg) 
{
	//non portable code
	fprintf(stderr, "pid:%ld, tid:%lx\n", (long)getpid(), (unsigned long)pthread_self());
	return NULL;
}
int main(void)
{
	int error;
	pthread_t tid;
	if((error=pthread_create(&tid, NULL, thread_func, NULL)))
		fprintf(stderr, "Failed to create thread: %d\n", strerror(error));
	if((error=pthread_join(tid, NULL)))
		fprintf(stderr, "Failed to join thread: %d\n", strerror(error));
	fprintf(stderr, "pid:%ld, tid:%lx (main thread)\n", (long)getpid(), (unsigned long)pthread_self());
	return 0;
}

