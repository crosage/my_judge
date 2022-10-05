#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/wait.h>
#include<sys/resource.h>
#include"./a.h"
int main()
{
    pid_t child=fork();
    if(child==0)
    {
        haha();
    }
    else
    {
        int status=0;
        struct rusage costResout;
        wait4(child,&status,WSTOPPED,&costResout);
        printf("child status is %d %d WEXITSTATUS(status)=%d\n",status,WIFEXITED(status),WEXITSTATUS(status));
        if(WIFEXITED(status))//非0时正常终止
        {
            if(WEXITSTATUS(status)==0)
            {
                printf("cao");
            }
        }
        else printf("??");//为0时触发RUNTIME ERROR
    }
}