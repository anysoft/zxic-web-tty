# 编译
```
# 编译lib库
gcc -fPIC -shared -o libhello.so hello.c

# 编译 main 并链接 hello 对应的 lib 库
gcc -o main main.c  -L. -lhello

```
