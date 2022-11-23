#include "./commons.h"
#include "./judger.h"
#include<fstream>
#include<iostream>
#include "./nlohmann/json.hpp"
char outString[450],inString[6000000];
using json=nlohmann::json;
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
        json result_json;
        result_json["cpuTime"]=result.cpuTimeCost;
        result_json["realTime"]=result.realTimeCost;
        result_json["memory"]=result.memoryCost;
        result_json["exitCode"]=result.exitCode;
        string res="";
        result_json["result"]=result.condition;
        res="wrong answer "+to_string(result.lineNumber)+" line differ -expected "+result.stdOut.c_str()+" found "+result.errorOut.c_str();
        result_json["errorInfo"]=res;
        cout<<result_json<<endl;
    }
}