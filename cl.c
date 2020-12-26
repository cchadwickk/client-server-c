#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc , char *argv[])
{
    int socket_desc, inputport;
    struct sockaddr_in server;
    char *message , server_reply[2000], inputip[20], message[1000];

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("socket() error");
    }

    printf("Enter ip and port\n");
    scanf("%s\n%d",&inputip,&inputport);

    server.sin_addr.s_addr = inet_addr(inputip);
    server.sin_family = AF_INET;
    server.sin_port = htons(inputport);

    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect() error");
        return 1;
    }

    puts("Connected\n");
    while(1)
    {
        printf("Enter message to send, n to exit\n");
        scanf("%s",&message);

        if(strcmpi(message,"n")==0)
            break;

        if( send(socket_desc , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        puts("Data Send\n");

        if( recv(socket_desc, server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
        }
        puts("Reply received\n");
        puts(server_reply);
    }
    return 0;
}
