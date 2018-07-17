#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>

void* cal_loop(void* arg)
{
	int i, sum = 0;
	int n = *(int*)arg;
	for( i=0; i<n; i++)
    {	
		sum += i;
    } 
	return (void*)sum;
}
void signal_handler(int sig)
{
	sigset_t old_sig, new_sig;
	fprintf(stderr, "Got Signal %d\n", sig);	
	signal(SIGINT, SIG_DFL);
	
	sigaddset(&new_sig, SIGALRM);

	sigprocmask(SIG_SETMASK, NULL, &old_sig);
	if( sigismember(&old_sig, SIGALRM) )
	{
		printf("[INT SIG HANDLER]sigalrm is blocking member\n");
		sigdelset(&old_sig, SIGALRM);
	}
	if( sigismember(&old_sig, SIGALRM) )
	{
		printf("[INT SIG HANDLER]sigalrm is blocking member\n");
		sigdelset(&old_sig, SIGALRM);
	}
	sigprocmask(SIG_SETMASK, &old_sig, NULL);

	
}

void sig_alarm_handler(int sig)
{
	fprintf(stderr, "Wake up by %d\n", sig);

}
int main()
{
	// sa_hanlder
	// sigset_t sa_mask
	// int sa_flags -> SA_NOCLDSTOP, SA_RESETHAND, SA_RESTART, SA_NODEFER
	struct sigaction sig_act;
	struct itimerval itime;
	sigset_t block_signal;
	

	sig_act.sa_handler = sig_alarm_handler;
	sig_act.sa_flags = 0;
	
	itime.it_value.tv_sec = 1;
	itime.it_value.tv_usec = 0;
	itime.it_interval.tv_usec =0;
	itime.it_interval.tv_sec = 1;
	
	//sigprocmask(int how, sigset_t* ...)
	// how : SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK
	sigaddset(&block_signal, SIGALRM);
	sigprocmask(SIG_BLOCK, &block_signal, NULL);	

	// SIG_IGN: ingnore the signal
	// SIG_DFL: default handler
	signal(SIGINT, signal_handler);
	if(sigemptyset(&sig_act.sa_mask)==-1 || sigaction( SIGALRM, &sig_act, NULL)==-1 )
		perror("Fail to set sig action\n");
	//pause();
	setitimer(ITIMER_REAL, &itime, NULL);
	



	for(;;){ 
		int sig_no =0;
		sigset_t wait_sig;
		sigset_t old_sig;
		sigemptyset(&old_sig);		
		fprintf(stderr, "Looping...\n"); sleep(1);
		sigprocmask(SIG_UNBLOCK, NULL, &old_sig);
		if( sigismember(&old_sig, SIGALRM) )
		{
			printf("sigalrm is blocking member\n");
		}
		sigemptyset(&wait_sig);
		sigaddset(&wait_sig, SIGALRM);
		//sigwait(&wait_sig, &sig_no);
		if( sig_no ) fprintf(stderr, "Wait signal %d\n", sig_no);
	}
	return 0;
}
