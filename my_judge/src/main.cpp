#include "./commons.h"
#include "./judger.h"
#include<fstream>
#include<iostream>
char outString[450],inString[6000000];
int main(int argc,char *argv[])
{
    struct limits limit;
    struct judgeResult result;
    init(&limit,&result);
    
    
//    limit.inputPath="../problems/hell_word/1.in";
//    limit.outputPath="../problems/hell_word/1.myout";
//    limit.stdOutputPath="../problems/hell_word/1.out";
//    limit.execPath="../problems/hell_word/hell_word";
//    printf("%s\n",limit.inputPath);
/*
sudo ./build/myjudge -t 3000 -c 3000 '
-p ./problems/realtest/mayan1.myout 
-r ./problems/realtest/realtest 
-i ./problems/hell_word/1.in -o 
./problems/realtest/mayan1.ans >>result'
*/

    if(setOptions(argc,argv,&limit))
    {
        limit.loggerFile=fopen(limit.loggerPath,"a");
        judge(&limit,&result);
        printf("{\n"
            "    \"cpu_time\": %d,\n"
            "    \"real_time\": %d,\n"
            "    \"memory\": %ld,\n"
            "    \"exit_code\": %d,\n"
            "    \"result\": %d\n"
            "    \"lineNumber\": %d\n"
            "    \"stdOut\": %s\n"
            "    \"errorOut\": %s\n"
            "}",
            result.cpuTimeCost,
            result.realTimeCost,
            result.memoryCost,
            result.exitCode,
            result.condition,
            result.lineNumber,
            result.stdOut.c_str(),
            result.errorOut.c_str()
            );
        printf("\n");
    }
}