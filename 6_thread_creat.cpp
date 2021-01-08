#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<string.h>
void print_ids(const char* s)
{
    printf("%s pid %u, tid %u\n",s,getpid(),(int)pthread_self());
}

void* thr_fn(void* arg)
{
    print_ids("new thread:");
}

int main()
{
    int err;
    pthread_t tid;
    err=pthread_create(&tid,NULL,thr_fn,NULL);
    if(err==0) 
    {
        printf("create thread success\n");
        print_ids("main thread:");
    }
    else
    {
        printf("creat thread failed\n");
        exit(1);
    }
    
    sleep(1);
    exit(0);
}