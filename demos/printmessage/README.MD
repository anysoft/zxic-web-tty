> 模块化及动态、静态编译

# 编译
## 单独编译

```bash
# 单独编译每个 .c 文件为目标文件（.o 文件）
gcc -c utils.c -o utils.o
gcc -c main.c -o main.o

# -c：表示只编译，不链接。
# 生成的目标文件分别为 utils.o 和 main.o。

# main.o 和 utils.o：将两者链接在一起。
gcc main.o utils.o -o my_program

# -o my_program：指定输出的可执行文件名为 my_program。

# 运行
./my_program

# 输出
Message: Hello, World!
```


## 一起编译

```
gcc main.c utils.c -o my_program

```

## 静态链接
```
# 编译 utils.c 为目标文件
gcc -c utils.c -o utils.o
# 生成静态库
ar rcs libutils.a utils.o

# 静态链接编译主程序
gcc main.c -L. -lutils -o my_program
```

## 动态编译
```
# 编译 utils.c 为动态库：
gcc -fPIC -shared utils.c -o libutils.so

# 使用动态库编译主程序：

gcc main.c -L. -lutils -o my_program

# 运行程序前指定动态库路径
export LD_LIBRARY_PATH=.

# 运行程序
./my_program
```

 