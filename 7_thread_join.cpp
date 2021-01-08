#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

void* fn1(void*)
{
    printf("thread 1 is processed.\n");
    return((void*)1);
}
void* fn2(void*)
{
    printf("thread 2 is processed.\n");
    return((void*)2);
}

int main()
{
    pthread_t tid1,tid2;
    int err1 = pthread_create(&tid1,NULL,fn1,NULL);
    int err2 = pthread_create(&tid2,NULL,fn2,NULL);
    if(err1 != 0 && err2 != 0 )
    {
        printf("create thread failed\n");
        exit(1);
    }
    void *tret;
    // only for thread 1 finished, the process will continue
    pthread_join(tid1,&tret);
    printf("thread 1 has finished, return number is %d.\n",tret);
    // only for thread 2 finished, the process will continue
    pthread_join(tid2,&tret);
    printf("thread 2 has finished, return number is %d\n",tret);
    exit(0);
}
