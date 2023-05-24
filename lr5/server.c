#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <winsock2.h>
#include <windows.h>s
#include <ws2tcpip.h>
#include "cryptools.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma warning(disable:4996)

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
    int res, resSend;
    SOCKET currentSocket = INVALID_SOCKET;
    SOCKET clientSocket = INVALID_SOCKET;
    char buf[1024];


    res = WSAStartup(MAKEWORD(2, 2), &wsaData); // основа

    if (res != 0)
    {
        printf("Startup error!\n");
        return 1;
    }

    currentSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // сокет сервера пока нет клиента

    if (currentSocket == INVALID_SOCKET)
    {
        printf("Socket error!\n");
        WSACleanup();
        return 1;
    }

    int val = 1;
    setsockopt(currentSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&val, sizeof(val));

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = address;
    serverAddress.sin_port = port;


    if (bind(currentSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)))   // бинд
    {
        printf("Bindind failed!\n");
        closeALL(currentSocket);
        return 1;
    }


    if (listen(currentSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Unexpected socker error!\n");
        closeALL(currentSocket);
        return 1;
    }

    clientSocket = accept(currentSocket, NULL, NULL);   // клиент прилетел
    if (clientSocket == INVALID_SOCKET)
    {
        printf("Invalid client socket!\n");
        closeALL(currentSocket);
        return 1;
    }
    printf("Ok\n");

    closesocket(currentSocket);     // не нужен больше

    do {
        res = recv(clientSocket, buf, 1024, 0);
        if (res > 0)
        {
            char* encryptedText = NULL;
            encryptedText  = (char*)malloc(sizeof(buf) * 100);
            strcpy(encryptedText, Encryption(buf));
            resSend = send(clientSocket, encryptedText, strlen(encryptedText), 0);
            free(encryptedText);
            memset(buf, 0, sizeof(buf));
            encryptedText = NULL;
            if (resSend == SOCKET_ERROR)
            {
                closeALL(clientSocket);
                return 1;
            }

        }
        else if (resSend == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed\n");
            closeALL(clientSocket);
            return 1;
        }

    } while (res > 0);

    res = shutdown(clientSocket, SD_SEND);
    if (res == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closeALL(clientSocket);
        return 1;
    }


    closeALL(clientSocket);     // сворачиваемся

    return 0;
}