
#include<map>
#include<unistd.h>
#include<sys/resource.h>
#include<string>
#include<cstring>
#include<signal.h>
#include<pthread.h>
#include<stdio.h>
#include<iostream>
#include<sys/wait.h>
#include "dealComplie.h"
void showUsage()
{
    printf("\n[参数]\n");
    printf("\
    -c   测试点个数\n");
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
    int opt,cnt=0;
    constantPath="\0";
    suffixName="\0";
    FILE *pfd=fopen("./result","w+");
    fclose(pfd);
    while ((opt = getopt(argc, argv, "h:c:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                showUsage();
                return 0;
            case 'c':
                cnt=atoi(optarg);
                break;
        }
    }
    for(int i=3;i<=7;i++)
    {
        string inputPath="-i ./problems/MLE/data"+to_string(i)+".in ";
//        inputPath="-i ./problems/hell_word/1.in ";
        string stdOutputPath="-o ./problems/MLE/data"+to_string(i)+".out ";
        string Time="-t 3000 ";
        string cpuTime="-c 3000 ";
        string outputPath="-p ./problems/MLE/data"+to_string(i)+".myout ";
        string execPath="-r ./problems/MLE/MLE ";
        string memory="-m 5 ";
        string log="-l ./logger.txt ";
        string err="-e ./problems/MLE/data"+to_string(i)+".error ";
        string tmp="sudo ./build/myjudge "+err+log+memory+Time+cpuTime+stdOutputPath+execPath+inputPath+outputPath+">>result";
        cout<<tmp<<" **getTest"<<endl;
        printf("%d\n",system(tmp.c_str()));
    }
}
