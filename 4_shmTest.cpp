#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>

int main()
{
    int pid,shmid;
    char* read_add;
    char* write_add;
    //char* write_add=(char*)malloc(20*sizeof(char));
    printf("the address of write_add:%x\n",&write_add);
    struct shmid_ds dsbuf;
    // Allocate shared memory

    if((shmid=shmget(IPC_PRIVATE,32,0))<0)
    {
        printf("Allocate shared memory error\n");
        exit(1);
    }
    else
    {
        printf("Allocate shared memory success\n");
    }
    //create child process
    pid=fork();
    if(pid<0)
    {
        printf("Creat child process failed\n");
        exit(2);
    }
    else if(pid>0)      //Parent process
    {
        printf("Parent process is %d\n",getpid());
        //link shared memory
        write_add=(char*)shmat(shmid,NULL,0);
        printf("Shared memory has established,the address of write_add is %x\n",&write_add);
        if(sizeof(write_add) <= 1)
        {
            printf("Link shared memory failed\n");
            exit(3);
        }
        else
        {
            printf("Link shared memory success\n");
            strcpy(write_add,"Test information\n");
            printf("write information:%s",write_add);
            //disable connect
            if((shmdt((void*)write_add))<0)
            {
                printf("Disable connect failed\n");
            }
            else
            {
                printf("Disable connect success\n");
            }
            sleep(2);
            return 0;
        }      
    }
    else if (pid==0)
    {
        sleep(2);
        printf("The ID of child process is %d\n",getpid());
        if((shmctl(shmid,IPC_STAT,&dsbuf))<0)
        {
            printf("Get the state of shared memory failed\n");
            exit(4);
        }
        else
        {
            printf("Get the state of shared memory success\n");
            printf("The size of shared memory is %d\n",dsbuf.shm_segsz);
            if((read_add=(char*)shmat(shmid,0,0))<0)
            {
                printf("shmat link error\n");
                exit(5);
            }
            else
            {
                printf("The information geted is :%s",read_add);
                printf("The latest operated process is:%d\n",dsbuf.shm_lpid);
                if((shmdt((void*)read_add))<0)
                {
                    printf("shmdt delete shared memory error\n");
                    exit(6);
                }
                else
                {
                    printf("shmdt delete shared memory success\n");
                    exit(0);
                }
                
            }
            
        }
        
    }
    
    
}