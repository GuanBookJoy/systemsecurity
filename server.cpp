#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <wait.h>

void network();

int main(int argc, char *argv[])
{
    network();
    return 0;
}

void network()
{
    printf("----------------HTTP网络服务----------------\n\n");
    printf("\n初始化服务器socket\n");
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0) 
    {
        printf("服务器初始化socket失败\n");
        exit(-1);
    }
    printf("初始化服务器socket成功\n");
    struct sockaddr_in server_sockaddr;
    memset(&server_sockaddr, 0, sizeof(server_sockaddr));
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(80);
    server_sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("\n服务器绑定套接字\n");
    if (bind(server_socket, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) < 0)
    {
        printf("绑定套接字失败\n");
    }
    else
    {
        printf("绑定套接字成功\n\n");
    }
    int i = 0;
    while(1)
    {
        printf("服务器监听中,%d\n",i++);
        accept(server_socket, NULL, NULL);
        sleep(5);
    }
    printf("\n关闭服务器socket\n");
    close(server_socket);
    printf("关闭服务器socket成功\n");
    printf("\n----------------HTTP网络服务----------------\n\n");
}
