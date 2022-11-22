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
#include "./seccomp_rules.h"
void close_file(FILE *fp) {
    if (fp != NULL) {
        fclose(fp);
    }
}
void setLimit(struct limits *limit)//设置时间限制和内存限制
{
    //java虚拟机需要单独处理
    if(strcmp(limit->type,"java"))
    {
        //printf("我不是java limit->type=%s\n",limit->type);
        struct rlimit memory_limit;
        memory_limit.rlim_cur=memory_limit.rlim_max=limit->memoryLimit*2;
        if(setrlimit(RLIMIT_AS,&memory_limit))
        {
            makeLog(ERROR,"限制出错",limit->loggerFile);    
            exit(memorySetError);   
        }
    }
    struct rlimit time_limit;
    time_limit.rlim_cur=time_limit.rlim_max=(limit->cpuTimeLimit+1000)/1000;
    if(setrlimit(RLIMIT_CPU,&time_limit))
    {
        makeLog(ERROR,"限制出错",limit->loggerFile);    
        exit(timeSetError);
    }
    struct rlimit maxOutput;
    maxOutput.rlim_cur=maxOutput.rlim_max=limit->outputLimit;
    if(setrlimit(RLIMIT_FSIZE,&maxOutput))
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
    FILE * errFile=NULL;
//    printf("limi =%s\n",limit->inputPath);
    if(!fopen(limit->execPath,"r"))
    {
        // printf("?????");
        exit(execPathCantFound);
    }
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
//        dup2(f,STDERR_FILENO);
    }
    if(limit->errorPath[0]!='\0')
    {
        errFile=fopen(limit->errorPath,"w");
        if(!errFile)
        {
            makeLog(ERROR,"无法打开错误文件",limit->loggerFile);
            exit(errorCantFound);
        }
        int f=fileno(errFile);
        dup2(f,STDERR_FILENO);
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
    
    
//    printf("%s\n",limit->type);
    if(!strcmp(limit->type,"\0")||!strcmp(limit->type,"c")||!strcmp(limit->type,"c++")||!strcmp(limit->type,"cpp"))
    {
        setLimit(limit);
//        printf("c = 1=%d 2=%d 3=%d 4=%d\n",strcmp(limit->type,"\0"),strcmp(limit->type,"c"),strcmp(limit->type,"c++"),strcmp(limit->type,"cpp"));
        c_cpp_seccomp_rules(limit);
        char *envp[]={"PATH=/bin",0};
//    printf("运行了 %s\n",limit->execPath);
        if(execve(limit->execPath,NULL,envp))
            makeLog(FATAL,"执行出错",limit->loggerFile);
    }
    else if(!strcmp(limit->type,"python")||!strcmp(limit->type,"py"))
    {
        setLimit(limit);
        setSeccompGuard();
        // printf("hahaha\n");
        string tmp=limit->execPath;
//        string tmptmp=tmp.substr(tmp.rfind("/")+1);
        char *argv[]={"python3",(char*)(tmp.c_str())};
        char *envp[]={"PATH=/bin",0};
//        cout<<tmptmp<<endl;
//        system("ls");
        if(execve("/usr/bin/python3",argv,envp))
            makeLog(FATAL,"执行出错",limit->loggerFile);
//            printf("*asd8*as8*asd8*asd\n");
    }
    else if(!strcmp(limit->type,"java"))
    {
        setLimit(limit);
        setSeccompGuard();
        string tmp=limit->execPath;
        string tmp1=tmp.substr(0,tmp.rfind("/")+1);
        string tmp2=tmp.substr(tmp.rfind("/")+1);
        char *argv[]={"java","-cp","./problems/hell_word/","HelloWorld"};
//        char *envp[]={"PATH=/bin",0};
//        cout<<tmp1.c_str()<<" "<<tmp2.c_str()<<endl;
        if(execve("/usr/bin/java",argv,NULL))
            makeLog(FATAL,"执行出错",limit->loggerFile);
    }
    else
    {
        makeLog(FATAL,"不支持的文件类型",limit->loggerFile);
    }
}