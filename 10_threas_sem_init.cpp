#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<fcntl.h>
#include<unistd.h>
#include<pthread.h>

void* thread_fn(void* arg);
void print(void);
sem_t sem;      //can't be a pointer without initialization, otherwise it will be a segment error.
int val;
const int num=5;

int main(int argc, char* argv[])
{
    if((sem_init(&sem,0,2))!=0)
    {
        printf("create semaphore failed.\n");
        exit(1);
    }

    printf("ready to creat threads.\n");

    int flag;
    pthread_t a_thread[num];
    for(int i=0;i<num;i++)
    {
        flag=pthread_create(&a_thread[i],NULL,thread_fn,NULL);
        if(flag!=0)
        {
            printf("create thread failed, flag is %d.\n",flag);
            exit(2);
        }
    }

    for(int i=0;i<num;i++)
    {
        pthread_join(a_thread[i],NULL);
    }
    
}

void* thread_fn(void* arg)
{
    sem_wait(&sem);
    print();
    sleep(1);
    sem_post(&sem);
    printf("I finished, my tid is %d.\n",(int)pthread_self());
    pthread_exit(NULL);
}

void print(void)
{
    printf("I get it, my tid is %d.\n",(int)pthread_self());
    sem_getvalue(&sem,&val);
    printf("Now the value have %d.\n",val);
}