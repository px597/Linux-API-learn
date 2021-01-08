#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

void* thread_fn(void* arg);
void print();

sem_t* sem = NULL;      //create semaphore, must be initalization
pthread_t a_thread[5];  //create 5 thread
int val;

int main(int argc, char* argv[])
{
    
    if(argc!=2)
    {
        printf("Please input a file name.\n");
        exit(1);
    }
    //set the number of semaphore to 3
    sem = sem_open(argv[1],O_CREAT,0644,3);
    //creat 5 thread to apply 3 semaphore

    int flag = 1;
    // pthread_t b_thread;
    // flag=pthread_create(&b_thread,NULL,thread_fn,NULL);
    // printf("flag = %d.\n",flag);

    for(int n=0;n<5;n++)
    {
        flag = pthread_create(&a_thread[n],NULL,thread_fn,NULL);
        printf("flag = %d.\n",flag);
        if(!flag);
        {
            printf("create %d thread failed, flag is %d.\n",n,flag);
            exit(2);
        }
        //printf("cread %d thread success, the tid is %d\n",(int)pthread_self());
        // exit(2);
    }
    
    //wait for a_thread finish processing.
    for(int n=0;n<5;n++)
    {
        pthread_join(a_thread[n],NULL);
    }
    //close semaphore and unlink it
    sem_close(sem);
    sem_unlink(argv[1]);

}
void* thread_fn(void* arg)
{
    sem_wait(sem);       //apply for semaphore
    print();
    sleep(1);
    sem_post(sem);      //release semaphore
    printf("I am finished, my tid is %d.\n",(int)pthread_self());
}
void print()
{
    printf("I get it, my tid is %d.\n",(int)pthread_self());
    sem_getvalue(sem,&val);
    printf("Now the value have %d.\n",val);
}