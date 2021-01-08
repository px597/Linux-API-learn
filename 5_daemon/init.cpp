#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/param.h>
#include<sys/stat.h>
#include "init.hpp"

void init_daemon(void)
{
    int pid,i;
    //create the first child process
    pid=fork();
    if (pid<0)  //create child process failed
    {
        exit(1);
    }
    else if(pid<0)  //parent process
    {
        exit(0);
    }
    else if(pid==0) //first child process
    {
        setsid();   //let first child process to be the leader of session and processes
        pid=fork(); //create the second process
        if(pid<0)   //create second child process failed
        {
            exit(2);
        }
        else if(pid>0)
        {
            exit(0);
        }
        else if(pid==0) //the second child process
        {
            for(i=0;i<NOFILE;i)
            {
                close(i);
            }
            chdir("/tmp");
            umask(0);
            return;
        }
    }
    
}