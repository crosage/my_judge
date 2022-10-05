#include"commons.h"
void init(struct limits *limit,struct judgeResult *result)
{
    limit->cpuTimeLimit=cpuTimeLimit;
    limit->realTimeLimit=realTimeLimit;
    limit->memoryLimit=memoryLimit;
    limit->outputPath="\0";
    limit->inputPath="\0";
    limit->stdOutputPath="\0";
    limit->execPath="\0";
    limit->loggerPath="./main.log";
    limit->uid=uidDefeat;
    limit->py=0;
    limit->jar=0;
    result->condition=1000;
    result->memoryCost=0;
    result->cpuTimeCost=0;
    result->exitCode=0;
    result->realTimeCost=0;
}
void showUsage() {
    printf("\n[限制相关]\n");
    printf("\
  -t,     [可选] 限制实际时间，单位 ms，请注意和 CPU 时间区分，默认值为 4000\n\
  -c,     [可选] 限制 CPU 时间，单位 ms，默认值为 4000\n\
  -m,     [可选] 限制运行内存，单位 MB，默认值为 64MB\n\
  -u,     [可选] 执行目标可执行文件对应的用户 ID，默认值为 3000\n");
    printf("[输入/输出相关]\n");

    printf("\
  -r,      目标可执行文件\n\
  -l,      日志文件\n\
  -o,      标准输出文件\n\
  -e,      标准错误文件\n\
  -i,      标准输入文件\n\
  -p,      选手输出文件\n\
  -y,      是否为python类型文件\n ");

    printf("[其他]\n");
    printf("\
  -h,     查看帮助\n\n");
}
int setOptions(int argc,char *argv[],struct limits *limit)
{
    int opt;
    while ((opt = getopt(argc, argv, "t:c:m:f:o:e:i:r:l:h::u:g:p:y")) != -1) 
    {
        switch (opt) 
        {
            case 't':
                limit->realTimeLimit = atoi(optarg);
                break;
            case 'c':
                limit->cpuTimeLimit = atoi(optarg);
                break;
            case 'm':
                limit->memoryLimit = atoi(optarg)*1024*1024;
                break;
            case 'o':
                limit->stdOutputPath = optarg;
                break;
            case 'e':
                limit->complieErrorPath = optarg;
                break;
            case 'i':
                limit->inputPath = optarg;
                break;
            case 'r':
                limit->execPath = optarg;
                break;
            case 'p':
                limit->outputPath=optarg;
                break;
            case 'l':
                limit->loggerPath = optarg;
                break;
            case 'u':
                limit->uid = atoi(optarg);
                break;
            case 'y':
                limit->py=1;
                break;
            case 'j':
                limit->jar=1;
                break;
            case 'g':
                limit->guard = atoi(optarg);
                break;
            case 'h':
                showUsage();
                return 0;
            default:
                printf("Unknown option: %c\n", (char) optopt);
                return 0;
        }
    }
    return 1;
}