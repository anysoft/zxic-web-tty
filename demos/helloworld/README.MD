# 编译
```
# 编译lib库
arm-linux-gcc -fPIC -shared -o libhello.so hello.c

# 编译 main 并链接 hello 对应的 lib 库
arm-linux-gcc -o main main.c  -L. -lhello

```
