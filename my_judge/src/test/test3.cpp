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
    char *argv[]={"java","-cp","../../problems/hell_word/","HelloWorld"};
//    char *envp[]={"PATH=/bin",0};
//    printf("%d\n",execve("/usr/bin/python3",argv,NULL));
    printf("%d\n",errno);
    if(execve("/usr/bin/java",argv,NULL))
    {
        printf("hjkasdhjkladsadhjkls\n");
    }
    else printf("jklasdjlasfljfas\n");
}