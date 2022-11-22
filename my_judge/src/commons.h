#ifndef COMMON_H
#define COMMON_H
#include<unistd.h>
#include<sys/resource.h>
#include<string>
using namespace std;

struct timeoutKillerConfig{
    int pid;
    int limitTime;
};
void init(struct limits *limit,struct judgeResult *result);
int setOptions(int argc,char *argv[],struct limits *limit);
//运行子程序中出现的问题
enum RUNNING_CONDITION{
    success=0,
    forkFailed=-2,
    timeSetError=-3,
    timeLimitError=-4,
    memorySetError=-5,
    memoryLimitError=-6,
    inputNotFound=-7,
    outputCantMake=-8,
    errorCantFound=-9,
    execPathCantFound=-12,
    uidError=-10,
    pthreadCreateFailed=-11
};
//各种限制与路径
struct limits{
    rlim_t cpuTimeLimit;
    rlim_t memoryLimit;
    rlim_t realTimeLimit;
    rlim_t outputLimit;
    char * inputPath;
    char * outputPath;
    char * execPath;
    char * stdOutputPath;
    char * loggerPath;
    char * errorPath;
    char * type;
    FILE * loggerFile;
    uid_t uid;
    int guard;
    int jar;
};
//判题结果
struct judgeResult{
    rlim_t cpuTimeCost;
    rlim_t realTimeCost;
    rlim_t memoryCost;
    string errorOut;
    string stdOut;
    int lineNumber;
    int condition;
    int exitCode;
};
enum analyse{
    WRONG_ANSWER=-1,
    SUCCESS=0,
    LOAD_SECCOMP_FAILED=1,
    TIME_LIMIT_EXCEEDED=2,
    MEMORY_LIMIT_EXCEEDED=3,
    RUNTIME_ERROR=4,
    SYSTEM_ERROR=5,
    FLOAT_ERROR=6,
    OUTPUT_CANT_FIND=7,
    STDOUTPUT_CANT_FIND=8,
    COMPILE_ERROR=9,
    NOT_ROOT_USER=10,
};
enum limitsDefault{
    cpuTimeLimit=4000, //4000ms
    memoryLimit=1024*1024*64, //64MB
    wallMemoryLimit=1024*1024*1024, //1024MB 硬限制
    realTimeLimit=4000, //4000ms真实时间
    uidDefeat=2333,
    outputLimit=20000000
};
#endif