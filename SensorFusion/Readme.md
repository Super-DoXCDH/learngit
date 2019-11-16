# SensorFusion

------

用于实现激光雷达和毫米波雷达的数据读取



### 目录结构

```
多传感器融合的代码目录结构如下所示：
|___SensorFusion
    |___bin 代码编译后的可执行文件存放目录
    |___build 代码编译时的过程文件存放处
    |___data 传感器融合的输入数据
    |___src 传感器融合的源代码
    |___build.sh 编译脚本
    |___CMakeLists.txt 组建工程的CMake文件
    |___LICENSE Udacity的License
    |___Reame.md 使用说明
```

### 使用方法

系统
Linux Ubuntu 16.04

编译
$ bash build.sh

运行
$ cd bin
$ ./SensorFusion ../data/sample-laser-radar-measurement-data-2.txt



### 链接
https://zhuanlan.zhihu.com/c_147309339
无人驾驶技术入门（十九）| 手把手教你实现多传感器融合技术