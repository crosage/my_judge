#include<cstdio>
#include<sys/time.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
#include<pthread.h>
#include<cstring>
#include<string>
#include "compareIgnoreSpaces.h"
#include "./commons.h"
#include "./runner.h"
#include "./logger.h"
//监控真实时间线程
using namespace std;
void *monitorThread(void *timeConfig)
{
    struct timeoutKillerConfig *timeConf=(struct timeoutKillerConfig *)timeConfig;
    pid_t pid=timeConf->pid;
    int limitTime=timeConf->limitTime;
    sleep((unsigned int) ((limitTime+1000)/1000));
    sleep(10);
    kill(pid,SIGKILL);
    return NULL;
}

int getTimeMillisecondByTimeval(struct timeval timeval)
{
    return timeval.tv_sec*1000+timeval.tv_usec/1000;
}
/*
父进程中 ：
进行真实时间的监视线程
等待子进程的运行并获取子进程的执行状态

子进程中：
设置输入输出
执行沙盒屏蔽部分指令
执行程序
*/
int isRoot()
{
    uid_t uid=getuid();
    return uid==0;
}
void judge(struct limits *limit,struct judgeResult *result)
{
    if(!isRoot())
    {
        result->condition=NOT_ROOT_USER;
        makeLog(ERROR,"Non-root user",limit->loggerFile,limit->submissionId);
        return ;
    }

    pid_t childPid;
    childPid=fork();
    

    struct timeval start,end;
    gettimeofday(&start,NULL);
    if(childPid<0)//fork出现错误
    {
        result->condition=SYSTEM_ERROR;
        result->exitCode=forkFailed;
        makeLog(ERROR,"Cant fork child process",limit->loggerFile,limit->submissionId);
        return ;
    }
    else if(childPid>0)//父进程
    {
//        printf("父进程中\n");
//        makeLog(DEBUG,"父进程已创建",limit->loggerFile);
        pthread_t pthread=0;
        struct timeoutKillerConfig killer;
        killer.limitTime=limit->realTimeLimit;
        killer.pid=childPid;
        //创建超出现实时间的线程
        int t=pthread_create(&pthread,NULL,monitorThread,(struct timeoutKillerConfig *)(&killer));
        if(t!=0)
        {
            result->condition=SYSTEM_ERROR;
            makeLog(ERROR,"Monitor thread creation failure",limit->loggerFile,limit->submissionId);
            return ;
        }        
        int status=0;
        //等待子进程运行结束并获得子进程的状态
        //结束状态赋给status
        //运行的时间赋给costResource

        struct rusage costResource;
        wait4(childPid,&status,WSTOPPED,&costResource);
//        makeLog(DEBUG,"子进程运行结束",limit->loggerFile);
//        printf("运行结束\n");
        pthread_cancel(pthread);
        gettimeofday(&end,NULL);
        result->cpuTimeCost=(int) getTimeMillisecondByTimeval(costResource.ru_utime);
        result->realTimeCost=(int) (end.tv_sec*1000 +end.tv_usec/1000-start.tv_sec*1000-start.tv_usec/1000);
        result->memoryCost=costResource.ru_maxrss;
        //正常终止,抛出exit的会进入该分支
        if(WIFEXITED(status))
        {
            //为0说明运行没有问题，但仍可能有内存超限，时间超限等问题
            if(WEXITSTATUS(status)==0)
            {
                int isMemoryExceeded=(long long)(result->memoryCost)>(limit->memoryLimit/1024);
//                printf("cost=%d limit=%d\n",result->memoryCost,limit->memoryLimit);
                int isCpuTimeExceeded=(result->cpuTimeCost)>(limit->cpuTimeLimit);
                int isRealTimeExceeded=(result->realTimeCost)>(limit->realTimeLimit);
                if(isMemoryExceeded)
                {
                    result->condition=MEMORY_LIMIT_EXCEEDED;
                }
                else if(isCpuTimeExceeded||isRealTimeExceeded)
                {
                    result->condition=TIME_LIMIT_EXCEEDED;
                }
                else 
                {
//                    printf("开始比对\n");
                    compareIgnoreSpaces(limit,result);
                }
            }
            else 
            {
                //printf("%d   **********\n",WEXITSTATUS(status));
                result->condition=SYSTEM_ERROR;
            }
        }
        else
        {
            result->exitCode=WTERMSIG(status);
            //触发setrlimit的阈值
            if(WTERMSIG(status)==SIGXCPU)
            {
                result->condition=TIME_LIMIT_EXCEEDED;
            }
            else if(WTERMSIG(status)==SIGFPE)
            {
                //出现/0
                result->condition=FLOAT_ERROR;
            }
            else if(WTERMSIG(status)==SIGKILL)
            {
                //现实时间超时被kill
                if(limit->realTimeLimit<result->realTimeCost)
                {
                    result->condition=TIME_LIMIT_EXCEEDED;
                }
                else 
                {    
                    result->condition=RUNTIME_ERROR;
                }
            }
            else if(WTERMSIG(status)==31)
            {
                makeLog(FATAL,"non-compliant code",limit->loggerFile,limit->submissionId);
                result->condition=RUNTIME_ERROR;
            }//包含SIGSEGV 
            else result->condition=RUNTIME_ERROR;
        }
    }
    else if(childPid==0)//子进程
    {
//        makeLog(DEBUG,"子进程已创建",limit->loggerFile);
//        printf("开始运行 %s %s\n",limit->execPath,limit->outputPath);
        run(limit);
    }
}