#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

gcc http_server.c -o http_server


#define PORT 8080
#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    read(client_socket, buffer, sizeof(buffer) - 1);
    
    // 打印接收到的请求
    printf("Received request:\n%s\n", buffer);
    
    // 解析请求
    char *response;
    if (strstr(buffer, "GET /getnvram?a")) {
        // 返回JSON数据
        response = "HTTP/1.1 200 OK\r\n"
                   "Content-Type: application/json\r\n"
                   "Access-Control-Allow-Origin: *\r\n"  // 允许跨域
                   "\r\n"
                   "{\"a\":\"123\"}";
    } else {
        // 处理其他请求
        response = "HTTP/1.1 404 Not Found\r\n"
                   "Content-Type: text/plain\r\n"
                   "Access-Control-Allow-Origin: *\r\n"  // 允许跨域
                   "\r\n"
                   "404 Not Found";
    }

    // 发送响应
    write(client_socket, response, strlen(response));
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 创建socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        return 1;
    }

    // 设置服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_socket);
        return 1;
    }

    // 监听连接
    if (listen(server_socket, 10) == -1) {
        perror("listen");
        close(server_socket);
        return 1;
    }

    printf("HTTP server is running on port %d\n", PORT);

    while (1) {
        // 接受连接
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("accept");
            continue;
        }
        
        // 处理请求
        handle_request(client_socket);
    }

    // 关闭服务器socket
    close(server_socket);
    return 0;
}
