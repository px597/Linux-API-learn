#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<unistd.h>

void new_op(int, siginfo_t*, void*);
int main(int argc, char* argv[])
{
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=new_op;

	int sig;
	sig=atoi(argv[1]);
	if(sigaction(sig,&act,NULL)<0)
	{
		printf("sigaction set error\n");
	}
	while (1)
	{
		sleep(2);
		printf("wait for signal\n");
	}
	
}

void new_op(int signum, siginfo_t* info, void* myact)
{
	printf("recieve signal %d\n",signum);
	sleep(5);
}
