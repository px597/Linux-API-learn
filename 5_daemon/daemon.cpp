#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include "init.hpp"

main()
{
    FILE* fp;
    time_t t;
    init_daemon();

    while(1)
    {
        sleep(5);
        if((fp=fopen("test.log","a"))>=0)
        {
            t=time(0);
            fprintf(fp,"I am at %s.\n",asctime(localtime(&t)));
            fclose(fp);
        }
    }
}