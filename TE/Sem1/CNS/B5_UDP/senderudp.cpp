#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <fstream>
#include <string>

#define BUFFER_SIZE 1024

void sendFile(const char* ip, int port, const char* filename) {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    
    WSAStartup(MAKEWORD(2, 2), &wsaData);


    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        WSACleanup();
        return;
    }

  
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "File not found: " << filename << std::endl;
        closesocket(sock);
        WSACleanup();
        return;
    }

  
    size_t fileSize = file.tellg();
    std::string fileType = filename; 
    size_t pos = fileType.find_last_of('.');
    if (pos != std::string::npos) {
        fileType = fileType.substr(pos + 1);
    } else {
        fileType = "unknown"; 
    }

   
    file.seekg(0, std::ios::beg);

   
    std::string fileInfo = std::string(filename) + "|" + std::to_string(fileSize) + "|" + fileType;
    sendto(sock, fileInfo.c_str(), fileInfo.size(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    
    char ack[BUFFER_SIZE];
    recvfrom(sock, ack, sizeof(ack), 0, nullptr, nullptr);
    std::cout << ack << std::endl;

    
    while (file) {
        file.read(buffer, sizeof(buffer));
        size_t bytesRead = file.gcount();
        sendto(sock, buffer, bytesRead, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    }

    
    const char* eofSignal = "EOF";
    sendto(sock, eofSignal, strlen(eofSignal), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    file.close();
    closesocket(sock);
    WSACleanup();
}

int main() {
    const char* ip = "192.168.130.246"; 
    int port = 12345; 
    std::string filename;

    while (true) {
        std::cout << "Enter the file path to send (or type 'exit' to quit): ";
        std::getline(std::cin, filename);

        if (filename == "exit") {
            break; 
        }

        sendFile(ip, port, filename.c_str());
    }

    return 0;
}