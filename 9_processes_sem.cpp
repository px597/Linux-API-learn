#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<wait.h>

void print(pid_t);
sem_t* sem;             // define semaphore
int val;                // define the number of semaphore

int main(int argc, char* argv[])
{

    if (argc!=2)
    {
        printf("please input a file name.\n");
        exit(1);
    }
    //creat semaphore
    sem=sem_open(argv[1],O_CREAT,0644,2);

    for(int i=0;i<5;i++)
    {
        if(fork()==0)       //child process
        {
            sem_wait(sem);  //apply for semaphore
            print(getpid());
            sleep(1);
            sem_post(sem);
            printf("I finished, my pid is %d.\n",getpid());
            return 0;
        }
    }
    wait(NULL);                 //wait for child process finished
    sem_close(sem);             //close the semaphore
    sem_unlink(argv[1]);        //delete the semaphore
    exit(0);
}

void print(pid_t pid)
{
    printf("I get the semaphore, my pid is %d.\n",pid);
    sem_getvalue(sem,&val);
    printf("Now the value have %d.\n",val);

}