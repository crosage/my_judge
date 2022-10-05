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
- y:是否为python类型文件
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
- 31:选手代码包含危险代码
- 


## 示例

``` sh
sudo ./build/myjudge -t 3000 -c 3000 -p ./problems/hell_word/1.myout -r ./problems/hell_word/hell_word.py -i ./problems/hell_word/1.in -o ./problems/hell_word/1.out -l ./logger.txt -y
```

