#include<stdio.h>
#include<sys/prctl.h>
#include<linux/seccomp.h>
int main()
{
    prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);
    char *buf="hell word!";
    printf("%s",buf);
}