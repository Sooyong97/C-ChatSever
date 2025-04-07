#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1111

int main() {
    int sock;
    // 인터넷 주소 구조체 생성
    struct sockaddr_in server_addr;
    //문자열 데이터 배열
    char buffer[1024];

    // socket 생성 (IPv4, TCP)
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // 서버 세팅
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(PORT); // 네트워크 전송용으로 port번호 변환
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost 주소

    // 서버 연결 요청
    // 연결할 소켓, 연결할 대상 주소, 주소 구조체 크기
    connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    
    printf("Connected\n");

    while(1) {
        printf("Client: ");
        // buffer 초기화
        memset(buffer, 0, sizeof(buffer));
        // 입력을 버퍼에 저장
        fgets(buffer, sizeof(buffer), stdin);

        // exit 입력시 채팅 종료
        if (strncmp(buffer, "exit", 4) == 0) {
            write(sock, buffer, strlen(buffer));
            break;
        }


        // 데이터 전송
        write(sock, buffer, strlen(buffer));

        memset(buffer, 0, sizeof(buffer));
        // 서버로부터 데이터 저장
        read(sock, buffer, sizeof(buffer));
        
        // 서버의 종료
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Server Disconnected");
            break;
        }
        
        printf("Server: %s\n", buffer);
    }

    close(sock);
    return 0;
}