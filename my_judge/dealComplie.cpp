
#include<map>
#include<unistd.h>
#include<sys/resource.h>
#include<string>
#include<cstring>
#include<signal.h>
#include<pthread.h>
#include<iostream>
#include<sys/wait.h>
#include "dealComplie.h"
void showUsage()
{
    printf("\n[参数]\n");
    printf("\
    -n   路径\n");
    printf("\
    -h    查看帮助\n");
}
struct iwanna{
    pid_t pid;
};
void *monitorThread(void *pidC)
{
    struct iwanna *killpid=(struct iwanna *)pidC;
    pid_t pid=killpid->pid;
    sleep(5);
    kill(pid,SIGKILL);
    return NULL;
}

string constantPath,suffixName,errorPath;
int main(int argc,char *argv[])
{
    int opt;
    constantPath="\0";
    suffixName="\0";
    while ((opt = getopt(argc, argv, "h:n:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                showUsage();
                return 0;
            case 'n':
                constantPath=optarg;
                break;
        }
    }

    uid_t childPid=fork();
    if(childPid>0)
    {
        pthread_t pthread=0;
        struct iwanna para;
        para.pid=childPid;
        int t=pthread_create(&pthread,NULL,monitorThread,(struct iwanna *)(&childPid));
        wait4(childPid,NULL,WSTOPPED,NULL);
        pthread_cancel(pthread);
    }
    else 
    {
        suffixName=constantPath.substr(constantPath.find_last_of("."));
        errorPath=constantPath.substr(0,constantPath.rfind('/')+1)+"error.info";
//        cout<<suffixName<<endl;
//        cout<<errorPath<<endl;
//        gcc -o path path.c &>
//        cout<<m[suffixName]<<endl;
        string tmp="";
        if(suffixName==".java")
            tmp=m[suffixName]+constantPath+" &>"+errorPath;
        else 
            tmp=m[suffixName]+constantPath.substr(0,constantPath.rfind('.'))+" "+constantPath+" &>"+errorPath;
        cout<<tmp<<endl;
        system(tmp.c_str());
//        char *envp[]={"PATH=/bin",0};
//    printf("运行了 %s\n",limit->execPath);
//        char *tt="./problems/hell_word/HelloWorld.class";
//        execve(tt,NULL,envp);
    }
}