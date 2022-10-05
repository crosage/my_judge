#include"guard.h"
#include<stdlib.h>
#include<unistd.h>
#include<cstdio>
int FORBIDDEN_LIST[]={
    SCMP_SYS(fork),
    SCMP_SYS(clone),
    SCMP_SYS(vfork),
    SCMP_SYS(kill),
    SCMP_SYS(socket)
};


/*
SCMP_ACT_ALLOW 0x7fff0000U
SCMP_ACT_KILL 0x00000000U
seccomp_rule_add 内置函数
params: ctx 初始化后传入的指针
params: 允许或者
params: 参数代表的系统调用号
params: 是否对对应的系统调用的参数作出限制 0是没限制
*/
int addSeccompRules(scmp_filter_ctx ctx)
{
    int len=sizeof(FORBIDDEN_LIST)/sizeof(int);
    for(int i=0;i<len;i++)
    {
        if(seccomp_rule_add(ctx,SCMP_ACT_KILL,FORBIDDEN_LIST[i],0))
            return 0;
    }
    return 1;
}

void setSeccompGuard()
{
    scmp_filter_ctx ctx;
    //初始化为黑名单模式 若初始化ALLOW 即为黑名单模式
    ctx=seccomp_init(SCMP_ACT_ALLOW);
    if(!ctx)
    {
        exit(0);
    }
    addSeccompRules(ctx);
    seccomp_load(ctx);
}