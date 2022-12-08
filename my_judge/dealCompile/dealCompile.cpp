
#include<map>
#include<unistd.h>
#include<sys/resource.h>
#include<string>
#include<cstring>
#include<signal.h>
#include<pthread.h>
#include<iostream>
#include<array>
#include<memory>
#include<stdexcept>
#include<iostream>
#include "pthread.h"
#include "sys/wait.h"
#include "dealCompile.h"
#include "./nlohmann/json.hpp"
using json=nlohmann::json;
void showUsage()
{
    printf("\n[参数]\n");
    printf("\
    -n   路径\n");
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
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


string constantPath,suffixName,errorPath;
int main(int argc,char *argv[])
{
    int opt;
    constantPath="\0";
    suffixName="\0";
    while ((opt = getopt(argc, argv, "h:n:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                showUsage();
                return 0;
            case 'n':
                constantPath=optarg;
                break;
        }
    }

    uid_t childPid=fork();
    if(childPid>0)
    {
        pthread_t pthread=0;
        struct iwanna para;
        para.pid=childPid;
        int t=pthread_create(&pthread,NULL,monitorThread,(struct iwanna *)(&childPid));
        int status;
        wait4(childPid,&status,WSTOPPED,NULL);
        json info;
        if(WTERMSIG(status)==SIGKILL)
        {
            info["compile_info"]="compile_timeout";
            cout<<info<<endl;
        }
        pthread_cancel(pthread);
    }
    else 
    {
        suffixName=constantPath.substr(constantPath.find_last_of("."));
        errorPath=constantPath.substr(0,constantPath.rfind('/')+1)+"error.info";
//        cout<<suffixName<<endl;
//        cout<<errorPath<<endl;
//        gcc -o path path.c &>
//        cout<<m[suffixName]<<endl;
        string tmp="";
        if(suffixName==".java")
            tmp=m[suffixName]+constantPath+" &>"+errorPath;
        else 
            tmp=m[suffixName]+constantPath.substr(0,constantPath.rfind('.'))+" "+constantPath;
        // cout<<tmp<<endl;
        string tmpp=tmp+" 2>tmp";
        int flag=system(tmpp.c_str());
        tmp=tmp+" 2>&1";
        json info;
        if(flag)
            info["compile_info"]="compile_error";
        else 
            info["compile_info"]="success";
        info["traceback"]=exec(tmp.c_str());
        cout<<info<<endl;
    }
}