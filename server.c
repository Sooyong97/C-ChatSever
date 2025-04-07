#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1111

int main() {
    int server_fd, client_fd;
    // 인터넷 주소 구조체 생성
    struct sockaddr_in server_addr, clinet_addr;
    socklen_t addr_size;
    char buffer[1024];

    // socket 생성
    // AFINET : IPv4 주소 체계 사용
    // SOCK_STREAM : TCP
    // 0 : 기본 프로토콜 (TCP/UDP, 현재 TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 서버 주소 세팅
    // IPv4 주소 체계
    server_addr.sin_family = AF_INET;
    // 어떤 IP 주소 요청이든 받음
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // 네트워크 전송용으로 port번호 변환
    server_addr.sin_port = htons(PORT);

    // bind : 소켓을 주소(IP + PORT)에 연결
    // bind (소켓, 주소 구조체 주소, 구조체 크기)
    bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
}