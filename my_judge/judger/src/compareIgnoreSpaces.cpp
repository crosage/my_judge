#include<cstdio>
#include<cstdlib>
#include<string.h>
#include"commons.h"
#include<ctime>
//实质是将答案以回车等，分成一块一块的，块间进行比较
void compareIgnoreSpaces(struct limits *limit,struct judgeResult *result)
{
//    double start=clock(),end;
    FILE *stdputFile=fopen(limit->stdOutputPath,"r");
    FILE *outputFile=fopen(limit->outputPath,"r");
    result->lineNumber=0;
    if(outputFile==NULL)
    {
        result->condition=OUTPUT_CANT_FIND;
        return ;
    }
    if(stdputFile==NULL)
    {
        result->condition=STDOUTPUT_CANT_FIND;
        return ;
    }
    char str1[50],str2[50],ch1='\n',ch2='\n';
    bool chk1=false,chk2=false;//windows环境下\r\n
    bool chkEof1=false,chkEof2=false;
    int flag1,flag2;
//ch1是选手输出
    while(1)
    {
//        printf("haha\n");
        if(ch1=='\n'||ch1=='\r'||ch1==EOF)//换行
        {
            result->lineNumber++;
            if(ch1=='\r')
            {
                ch1=fgetc(outputFile);
                if(ch1=='\n') ch1=fgetc(outputFile);
            }
            else ch1=fgetc(outputFile);
            while(ch1==' '||ch1=='\t')
                ch1=fgetc(outputFile);
            flag1=2;
        }
        else if(ch1==' '||ch1=='\t')//
        {
            while(ch1==' '||ch1=='\t')
                ch1=fgetc(outputFile);
            if(ch1=='\n'||ch1=='\r'||ch1==EOF)
            {
                result->lineNumber++;
                if(ch1=='\r')
                {
                    ch1=fgetc(outputFile);
                    if(ch1=='\n') ch1=fgetc(outputFile);
                }
                else ch1=fgetc(outputFile);
                while(ch1==' '||ch1=='\t')
                    ch1=fgetc(outputFile);
                flag1=2;
            }
            else flag1=1;
        }
        else flag1=0;
//        printf("one is ok second path=%s\n",);
        if(ch2=='\n'||ch2=='\r'||ch2==EOF)
        {
            if(ch2=='\r')
            {
                ch2=fgetc(stdputFile);
                if(ch2=='\n')ch2=fgetc(stdputFile);
            }
            else ch2=fgetc(stdputFile);
            while(ch2==' '||ch2=='\t')
                ch2=fgetc(stdputFile);
            flag2=2;
        }
        else if(ch2==' '||ch2=='\t')
        {
            while(ch2==' '||ch2=='\t')
                ch2=fgetc(stdputFile);
            if(ch2=='\n'||ch2=='\r'||ch2==EOF)
            {
                if(ch2=='\r')
                {
                    ch2=fgetc(stdputFile);
                    if(ch2=='\n') ch2=fgetc(stdputFile);
                }
                else ch2=fgetc(stdputFile);
                while(ch2==' '||ch2=='\t')
                    ch2=fgetc(stdputFile);
                flag2=2;
            }
            else flag2=1;
        }
        else flag2=0;
//        printf("why?\n");

        int len1=0;
        while(len1<20)
        {
            if(ch1!=' '&&ch1!='\t'&&ch1!='\r'&&ch1!='\n'&&ch1!=EOF)  
                str1[len1++]=ch1;
            else 
                break;
            ch1=fgetc(outputFile);
        }
        str1[len1]='\0';
        int len2=0;
        while(len2<20)
        {
            if(ch2!=' '&&ch2!='\t'&&ch2!='\r'&&ch2!='\n'&&ch2!=EOF)  
                str2[len2++]=ch2;
            else 
                break;
            ch2=fgetc(stdputFile);
        }
        str2[len2]='\0';
        result->errorOut=str1;
        result->stdOut=str2;
        if(flag1!=flag2)
        {
            result->condition=WRONG_ANSWER;
            fclose(stdputFile);
            fclose(outputFile);
            return ;
        }
        if(len1!=len2||strcmp(str1,str2)!=0)
        {
            result->condition=WRONG_ANSWER;
            fclose(stdputFile);
            fclose(outputFile);
            return ;
        }
        if(ch1==EOF&&ch2==EOF) break;
    }
//    printf("asdhkjasgfkjasfhkasfaskhfkjashfhakkjkkj\n");
    result->condition=SUCCESS;
    fclose(stdputFile);
    fclose(outputFile);
//    end=clock();
//    printf("%.6f\n",(end-start)/CLOCKS_PER_SEC);
}
void compareEps()
{

}