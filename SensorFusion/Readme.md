# SensorFusion

------

用于实现激光雷达和毫米波雷达的数据读取

###Rewrites @知乎:陈光 融合算法


### 目录结构

```
多传感器融合的代码目录结构如下所示：
|___SensorFusion
    |___algorithims 算法集成
    |___interface 枚举类型定义
    |___main 主程序目录
    |___data 传感器融合的输入数据
    |___BUILD
    |___WORKSPACE
    |___LICENSE Udacity的License
    |___Reame.md 使用说明
```

### 使用方法
(安装bazel, 并且请先将Eigen Library放在/usr/local/include/:参考:<https://www.codeleading.com/article/55692372926/> )
系统
Linux Ubuntu xxx


###方法1:编译然后执行
进入WORKSPACE目录
$ bazel build //main:excute_cpp
$ bazel-bin/main/excute_cpp
###方法2:直接运行(已经编译好了)
$ bazel-bin/main/excute_cpp 


### 链接
https://zhuanlan.zhihu.com/c_147309339
无人驾驶技术入门（十九）| 手把手教你实现多传感器融合技术
