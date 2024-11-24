#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

// arm-linux-gcc -o http_get http_get.c 

// 简单的 HTTP GET 请求函数
int http_get(const char *host, const char *path) {
    struct sockaddr_in server_addr;
    struct hostent *server;
    int sockfd;
    char request[512], response[1024];

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return -1;
    }

    // 获取服务器 IP 地址
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr, "No such host: %s\n", host);
        close(sockfd);
        return -1;
    }

    // 设置服务器地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80); // HTTP 默认端口
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // 连接到服务器
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        close(sockfd);
        return -1;
    }

    // 构建 HTTP GET 请求
    snprintf(request, sizeof(request),
             "GET %s HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n\r\n",
             path, host);

    // 发送请求
    if (send(sockfd, request, strlen(request), 0) < 0) {
        perror("Error sending request");
        close(sockfd);
        return -1;
    }

    // 接收响应并打印
    memset(response, 0, sizeof(response));
    while (recv(sockfd, response, sizeof(response) - 1, 0) > 0) {
        printf("%s", response);
        memset(response, 0, sizeof(response));
    }

    // 关闭套接字
    close(sockfd);
    return 0;
}

int main() {
    // 示例：发送 GET 请求到 http://www.baidu.com/robots.txt
    const char *host = "www.baidu.com";
    const char *path = "/robots.txt";

    printf("Sending HTTP GET request to %s%s\n", host, path);
    if (http_get(host, path) == 0) {
        printf("HTTP GET request completed successfully.\n");
    } else {
        printf("HTTP GET request failed.\n");
    }

    return 0;
}
