## 安装依赖

sudo apt install libseccomp-dev libseccomp2 seccomp

## 编译生成评测的可执行文件

``` sh
chmod 777 ./build.sh
./build.sh
```
## myjudge的可选参数
- t:限制现实时间 默认4000ms
- c:限制CPU时间 默认4000ms
- m:限制运行内存，单位MB，默认64MB
- u:执行目标可执行文件对应的UID，默认2333
- r:选手的可执行文件路径
- l:日志文件路径
- o:标程输出文件路径
- i:标程输入文件路径
- p:选手输出文件路径
- y:是什么类型的文件 python java c等
- h:帮助

## myjudge的返回结果示例
``` json
{
    "cpu_time": 20,
    "real_time": 21,
    "memory": 8204,
    "exit_code": 31,
    "result": 4
}
```
## myjudge exit_code码

- 0:无错误
- 8:浮点数例外，出现除0
- 9:超过真实时间限制被kill
- 11:段错误
- 24:触发setrlimit阈值被kill（时间或内存）
- 31:选手代码包含危险代码

## myjudge result码
- -1:答案错误
- 0:答案正确
- 1:设置沙盒出错
- 2:时间超限
- 3:内存超限
- 4:运行时错误
- 5:系统错误
- 6:浮点数例外
- 7:找不到选手输出文件
- 8:找不到标准输入文件
- 9:编译错误
- 10:非root用户
## 示例

- 选手为python类型文件

``` sh
sudo ./build/myjudge -t 3000 -c 3000 -p ./problems/hell_word/1.myout -r ./problems/hell_word/hell_word.py -i ./problems/hell_word/1.in -o ./problems/hell_word/1.out -l ./logger.txt -y python
```
- 选手为java类型文件
    
    -r参数可加class或不加class
```sh
sudo ./build/myjudge -t 3000 -c 3000 -p ./problems/hell_word/1.myut -r ./problems/hell_word/hell_word -i ./problems/hell_word/1.in -o ./problems/hell_word/1.out -l ./logger.txt -y java
```
```sh
sudo ./build/myjudge -t 3000 -c 3000 -p ./problems/hell_word/1.myut -r ./problems/hell_word/hell_word.class -i ./problems/hell_word/1.in -o ./problems/hell_word/1.out -l ./logger.txt -y java
```
- 选手为c/cpp类型文件

    执行二进制文件
```
sudo ./build/myjudge -t 3000 -c 3000 -p ./problems/hell_word/1.myut -r ./problems/hell_word/hell_word -i ./problems/hell_word/1.in -o ./problems/hell_word/1.out -l ./logger.txt 
```

## 输出示例

### wrong_ans
```json
{"cpu_time":47,"error_info":"wrong answer 98 line differ -expected 280 found 208","exitcode":0,"memory":23340,"real_time":49,"result":-1}
```
```json
{"cpu_time":0,"error_info":"wrong answer 2 line differ -expected nishishi found ","exitcode":0,"memory":3368,"real_time":2,"result":-1}
```
### Accept
```json
{"cpu_time":2,"exitcode":0,"memory":3372,"real_time":3,"result":0}
```
### timeout
```json
{"cpu_time":3998,"exitcode":9,"memory":3244,"real_time":4000,"result":2}
```
### memoryout
```json
{"cpu_time":1,"exitcode":11,"memory":1488,"real_time":1,"result":4}
```
### 

## 关于dealComplie
例子
```
./dealComplie -n ./problems/hell_word/hello.cpp
```
同一文件夹下生成可执行文件