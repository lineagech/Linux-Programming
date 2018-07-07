#include <stdio.h> 
#include <signal.h> 
#include <time.h> 

void catcher(int sig)
{ 
	printf("inside catcher() function\n"); 

//	sigprocmask(SIG_BLOCK, &new_set, &old_set);
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

	sigemptyset(&new_set); 
	sigaddset(&new_set, SIGALRM); 
	time(&start);    
	printf("SIGALRM signals blocked at %s\n", ctime(&start)); 
	sigprocmask(SIG_BLOCK, &new_set, &old_set);
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

