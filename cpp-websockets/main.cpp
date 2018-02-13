#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[]) {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char sendBuff[1025],
         headers[94] =  "HTTP/1.1 200 OK\r\n Connection: keep-alive\r\n Content-Type: text/html\r\n Content-Length: 1024\r\n\r\n",
         inputBuff[1000];
    time_t ticks;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);

    while(1) {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

        recv(connfd, (char *) &inputBuff, sizeof(inputBuff), 0);
        printf( "query: %s\n",  inputBuff);

        snprintf(sendBuff, sizeof(sendBuff), "%s\r\n", "<h1>Hello world!!!</h1>");
        write(connfd, sendBuff, strlen(sendBuff));

        close(connfd);
     }
}