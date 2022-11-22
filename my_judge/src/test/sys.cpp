#include<map>
#include<unistd.h>
#include<sys/resource.h>
#include<string>
#include<cstring>
#include<signal.h>
#include<pthread.h>
#include<iostream>
using namespace std;
int main()
{
    system("g++ test3.cpp -o test3 -W | ls");
}