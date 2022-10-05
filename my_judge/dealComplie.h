#ifndef DEALCOMPLIE_H
#define DEALCOMPLIE_H
#include<map>
#include<cstring>
using namespace std;
map<string,string> m={
    {".cc","g++ -o "},
    {".cpp","g++ -o "},
    {".c","gcc -o "},
    {".py","python3 -m "},
    {".java","javac "}
};
#endif