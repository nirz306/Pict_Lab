#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <fstream>
#include <string>

#define BUFFER_SIZE 1024

void receiveFile(int port) {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    int addrLen = sizeof(clientAddr);

  
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        WSACleanup();
        return;
    }

    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed!" << std::endl;
        closesocket(sock);
        WSACleanup();
        return;
    }

    std::cout << "Waiting for incoming files..." << std::endl;

    while (true) {
        
        recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &addrLen);
        std::string fileInfo(buffer);
        
        
        size_t delimiter1 = fileInfo.find('|');
        if (delimiter1 == std::string::npos) continue; 
        std::string filename = fileInfo.substr(0, delimiter1);
        
        size_t delimiter2 = fileInfo.find('|', delimiter1 + 1);
        if (delimiter2 == std::string::npos) continue; 
        size_t fileSize = std::stoul(fileInfo.substr(delimiter1 + 1, delimiter2 - delimiter1 - 1));
        
        
        std::string savePath = "C:\\Users\\HP\\Desktop\\received_" + filename.substr(filename.find_last_of("\\") + 1);
        
      
        const char* ack = "ACK: File info received.";
        sendto(sock, ack, strlen(ack), 0, (struct sockaddr*)&clientAddr, addrLen);

        
        std::ofstream file(savePath, std::ios::binary);
        if (!file) {
            std::cerr << "Error creating file at path: " << savePath << std::endl;
            continue; 
        }

        size_t bytesReceived = 0;
        while (bytesReceived < fileSize) {
            ssize_t bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &addrLen);
            if (bytes < 0) {
                std::cerr << "Error receiving data!" << std::endl;
                break;
            }
            if (bytes == 3 && strncmp(buffer, "EOF", 3) == 0) {
                break; 
            }
            file.write(buffer, bytes);
            bytesReceived += bytes;
        }

        std::cout << "File received successfully and saved as " << savePath << "!" << std::endl;

        file.close();
    }

    closesocket(sock);
    WSACleanup();
}

int main() {
    int port = 12345; 
    receiveFile(port);
    return 0;
}