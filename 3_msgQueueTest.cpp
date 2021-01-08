// author: px
// time: 2020/12/29
// note: share memory test program
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    //create message queue
    int msgid;
    struct
    {
        long mtype;
        char msg[40];
    }receive_buf,send_buf;
    msgid = msgget(IPC_PRIVATE, 0700);
    if(msgid < 0)
    {
        printf("message queue create failed\n");
        exit(1);
    }
    //creatr child process
    int pid = fork();
    if(pid < 0)
    {
        printf("child process create failed\n");
        exit(2);
    }
    else if(pid > 0)//parent process
    {
        send_buf.mtype = 1;
        strcpy(send_buf.msg, "I was sending message.\n");
        printf("sended message: %s", send_buf.msg);
        if(msgsnd(msgid,&send_buf,40, IPC_NOWAIT) < 0)
        {
            printf("send message failed\n");
            exit(3);
        }
    }
    else if(pid == 0)//child process
    {
        sleep(2);
        int infolen;
        if(infolen = msgrcv(msgid,&receive_buf,40,0,IPC_NOWAIT)<0)
        {
            printf("child process receive message failed.\n");
            exit(4);
        }
        else
        {
            printf("message receive success:%s\n",receive_buf.msg);
        }

        if((msgctl(msgid,IPC_RMID,NULL))<0)
        {
            printf("msgctl error\n");
            exit(5);
        }
        else
        {
            printf("%d message queue has been deleted\n",msgid);
            exit(0);
        }
        
    }
}