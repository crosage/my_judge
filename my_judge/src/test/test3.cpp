#include<cstdio>
#include<cstdlib>
#include<string>
#include<cstring>
#include<unistd.h>
#include<iostream>
#include<math.h>
#include<errno.h>
using namespace std;
int main()
{
    string s;
//    cin>>s;
    extern int errno;
    char *argv[]={"hell_word",NULL};
//    char *envp[]={"PATH=/bin",0};
//    printf("%d\n",execve("/usr/bin/python3",argv,NULL));
    printf("%d\n",errno);
    if(execve("../../problems/hell_word/hell_word",argv,NULL))
    {
        printf("hjkasdhjkladsadhjkls\n");
    }
    else printf("jklasdjlasfljfas\n");
}