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
    char *argv[]={"python","/home/krosa/my_judge/problems/hell_word/hell_word.py",NULL};
    char *envp[]={"PATH=/bin",0};
    printf("%d\n",execve("/bin/bash -c ",argv,NULL));
    printf("%d\n",errno);
    if(execve("/bin/bash -c ",argv,envp))
    {
        printf("hjkasdhjkladsadhjkls*****\n");
    }
/*    if(execve("../../problems/hell_word/hell_word.py",NULL,envp))
    {
        printf("hjkasdhjkladsadhjkls\n");
    }
    else printf("jklasdjlasfljfas\n");
*/}