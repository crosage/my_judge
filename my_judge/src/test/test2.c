#include <unistd.h>
#include <seccomp.h>

int main(void){
    scmp_filter_ctx ctx;
    ctx = seccomp_init(SCMP_ACT_ALLOW);
    seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execve), 0);
    seccomp_load(ctx);
    char * str = "/bin/sh";
    write(1,"hello worldn",12);
    syscall(59,str,NULL,NULL);//execve
    return 0;
}