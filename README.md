# 数值积分
这是用C++语言描述的数值积分（定积分）程序，可用于计算指定函数在闭区间上的定积分。

## 编译
将`integrate.cpp`下载到本地，进入该目录，然后运行
```
g++ integrate.cpp -o integrate
```
即可得到可执行文件`integrate`

## 运行
进入到可执行文件的目录，运行
```
./integrate
```
例如：
```cpp
czile@Czile:~$ ./integrate 
INTEGRATE V2.0 (C) Czile.
Add '-h' to get help.
请输入积分下限、积分上限：0 2
请用C++语法描述被积函数：
double func(double x) {
	return sin(x);
}
1.41615
```

## 高级模式
运行时带上参数`-g`进入积分的高级模式，可设置`精确度`，`迭代次数`等设置项目。  
例如：
```cpp
czile@Czile:~$ ./integrate -g
INTEGRATE V2.0 (C) Czile.
Add '-h' to get help.
请输入积分下限、积分上限、精确度和最高迭代次数（若无限制，则输入0）：0 2 1e-5 0
请用C++语法描述被积函数：
double func(double x) {
	return sin(x);
}
1.41615
```

## 帮助模式
运行时带上参数`-h`进入积分的帮助模式。也即是：
```
./integrate -h
```

## 带上运行库运行
在命令行输入`./integrate 库1， 库2...`，并且按照提示输入积分下限，积分上限，以及被积函数即可。  
例如：
```cpp
czile@Czile:~$ ./integrate time.h stdlib.h
INTEGRATE V2.0 (C) Czile.
Add '-h' to get help.
请输入积分下限、积分上限：-10000 10000
请用C++语法描述被积函数：
#include <time.h>
#include <stdlib.h>
double func(double x) {
	srand(time(0));
	return double(1)/double(rand()+1)/(1+fabs(x));    
}
9.57641e-07

```
