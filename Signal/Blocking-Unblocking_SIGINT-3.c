#include <stdio.h> 
#include <signal.h> 
#include <time.h> 

void catcher(int sig)
{ 
	printf("inside catcher() function\n"); 
} 

void catcher2(int sig)
{
        printf("inside catcher() function-2\n");
}


int main(int argc, char *argv[])
{ 
	time_t start, finish; 
	struct sigaction sact, sact2; 
	sigset_t new_set, old_set; 
	double diff;
 	sigemptyset(&sact.sa_mask); 
	sact.sa_flags = 0; 
	sact.sa_handler = catcher; 
	sigaction(SIGALRM, &sact, NULL); 
//	sigaction(SIGINT, &sact, NULL); 

        sigemptyset(&sact2.sa_mask);
        sact2.sa_flags = 0;
        sact2.sa_handler = catcher2;
	sigaction(SIGINT, &sact2, NULL);

	sigemptyset(&new_set); 
	sigaddset(&new_set, SIGALRM); 
	sigaddset(&new_set, SIGINT);
	sigprocmask(SIG_BLOCK, &new_set, &old_set);   
	time(&start);    
	printf("SIGALRM signals blocked at %s\n", ctime(&start)); 
	alarm(1); /* SIGALRM will be sent in 1 second */ 

	do
	{  
		time(&finish); 
		diff = difftime(finish, start); 
	}while(diff < 3); 
	
	sigprocmask(SIG_SETMASK, &old_set, NULL);
 	printf("SIGALRM signals unblocked at %s\n", ctime(&finish)); 
 	return(0); 
} 

