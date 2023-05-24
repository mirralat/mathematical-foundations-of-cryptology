#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#define port 0x1A0A
#define address 0x0100007f

void closeALL(SOCKET sock)
{
    closesocket(sock);
    WSACleanup();
    return;
}



int main()
{
    WSADATA wsaData;
    char buf[1024];
    int res;
    SOCKET currentSocket = INVALID_SOCKET;

    res = WSAStartup(MAKEWORD(2, 2), &wsaData); // основа

    if (res != 0)
    {
        printf("Startup error!\n");
        return 1;
    }

    currentSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (currentSocket == INVALID_SOCKET)
    {
        printf("Socket error!\n");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = address;
    serverAddress.sin_port = port;

    if (connect(currentSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        printf("Connection error.\n");
        closeALL(currentSocket);
        return 1;
    }

    printf("Connected!\n");

    do {
        printf("Input message: ");
        fgets(buf, sizeof(buf), stdin);
        res = send(currentSocket, buf, strlen(buf), 0);
        if (res == SOCKET_ERROR)
        {
            printf("Data send error.\n");
            break;
        }

        int bytesRead = recv(currentSocket, buf, sizeof(buf), 0);
        if (bytesRead <= 0) {
            printf("Connection error.\n");
            break;
        }

        printf("Reply: %.*s", bytesRead, buf);

    } while (1);

    closeALL(currentSocket);     // сворачиваемся

    return 0;
}