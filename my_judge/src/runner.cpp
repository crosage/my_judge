#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<math.h>
#include<string>
#include<iostream>
#include<cstring>
#include "./guard.h"
#include "./commons.h"
#include "./runner.h"
#include "./logger.h"
void close_file(FILE *fp) {
    if (fp != NULL) {
        fclose(fp);
    }
}
void setLimit(struct limits *limit)//设置时间限制和内存限制
{
    struct rlimit memory_limit;
    memory_limit.rlim_cur=memory_limit.rlim_max=limit->memoryLimit*2;
    if(setrlimit(RLIMIT_AS,&memory_limit))
    {
        makeLog(ERROR,"限制出错",limit->loggerFile);    
        exit(memorySetError);   
    }
    struct rlimit time_limit;
    time_limit.rlim_cur=time_limit.rlim_max=(limit->cpuTimeLimit+1000)/1000;
    if(setrlimit(RLIMIT_CPU,&time_limit))
    {
        makeLog(ERROR,"限制出错",limit->loggerFile);    
        exit(timeSetError);
    }
}
void run(struct limits *limit)
{
//    printf("***************\n");
    FILE * input=NULL;
    FILE * output=NULL;
//    printf("limi =%s\n",limit->inputPath);
    if(limit->inputPath[0]!='\0')
    {
        input=fopen(limit->inputPath,"r");
        if(!input)
        {
//            printf("cao\n");
            makeLog(ERROR,"无法打开输入文件",limit->loggerFile);
            exit(inputNotFound);
        }
        //将键盘输入重定向至该文件
        int f=fileno(input);
        dup2(f,STDIN_FILENO);
    }
//    printf("****\n");
    if(limit->outputPath[0]!='\0')
    {
        output=fopen(limit->outputPath,"w");
        if(!output)
        {
            makeLog(ERROR,"无法打开输出文件",limit->loggerFile);
            exit(outputCantMake);
        }
        //将键盘输出重定向至该文件
        int f=fileno(output);
        dup2(f,STDOUT_FILENO);
    }
//    printf("***************\n");
    if(limit->uid>0)
    {
        if(setuid(limit->uid)==-1)
        {
//            printf("exit\n");
            makeLog(ERROR,"设置uid错误",limit->loggerFile);
            exit(uidError);
        }
    }
//    printf("haha\n");
    setLimit(limit);
    setSeccompGuard();
    if(limit->py==0)
    {
        char *envp[]={"PATH=/bin",0};
//    printf("运行了 %s\n",limit->execPath);
        execve(limit->execPath,NULL,envp);
    }
    else if(limit->py==1)
    {
//        printf("hahaha\n");
        string tmp=limit->execPath;
        string tmptmp=tmp.substr(tmp.rfind("/")+1);
        char *argv[]={"python","hell_word.py",NULL};
        char *envp[]={"PATH=/bin",0};
//        cout<<tmptmp<<endl;
//        system("ls");
        execve(limit->execPath,argv,envp);
    }
}