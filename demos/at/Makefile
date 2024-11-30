# 定义交叉编译工具链路径和工具
CC = arm-linux-gcc
CFLAGS = -Wall                        # 仅打开编译警告，没有调试信息
LDFLAGS =                             # 链接选项，暂时为空
LIBS = -latutils -lnvram -lsoftap -lsoft_timer -lpthread  # 要链接的库

# 头文件和库的相对路径
INCLUDE_PATH = ../../include          # 头文件目录相对路径
LIB_PATH = ../../lib                  # 库文件目录相对路径

# 源文件和目标文件
SRC_DIR = .                            # 源文件当前目录
OBJ_DIR = .                            # 目标文件当前目录
TARGET = at                            # 生成的可执行文件名

# 获取所有的 C 源文件
SRCS := $(wildcard $(SRC_DIR)/*.c)

# 生成目标文件的规则
OBJS := $(SRCS:.c=.o)

# 编译目标文件
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_PATH) -c $< -o $@

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -L$(LIB_PATH) $(LIBS) -o $(TARGET)

# 清理规则
clean:
	rm -rf $(OBJS) $(TARGET)

# 安装规则（如果有需要，可以添加）
install:
	cp $(TARGET) /usr/local/bin/

# 默认目标
.PHONY: all clean install
all: $(TARGET)

