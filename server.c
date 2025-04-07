#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1111

int main() {
    int server_fd, client_fd;
    // 인터넷 주소 구조체 생성
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    //문자열 데이터 배열
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

    // 연결 요청 대기
    // socket, 대기열 크기
    listen(server_fd, 1);

    printf("연결 대기 중 \n");

    addr_size = sizeof(client_addr);
    // accept : client_addr에 클라이언트 IP, port 정보 리턴
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);
    printf("client 연결\n");

    // clinet 정보 출력
    char *client_ip = inet_ntoa(client_addr.sin_addr);
    int client_port = ntohs(client_addr.sin_port);
    printf("접속한 클라이언트 IP : %s, 포트 : %d\n", client_ip, client_port);

    // 채팅 시작
    while (1) {
        //새 데이터를 받기 전 데이터 초기화
        memset(buffer, 0, sizeof(buffer));
        // 클라이언트의 소켓에서 버퍼로 데이터 저장
        read(client_fd, buffer, sizeof(buffer));

        // client의 종료
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Client Disconnected");
            break;
        }

        printf("Client: %s\n", buffer);

        // 서버에서 데이터 전송
        printf("\nServer: ");
        // 버퍼 초기화
        memset(buffer, 0, sizeof(buffer));
        // 입력을 buffer에 저장
        // 버퍼의 주소, 최대 읽을 문자 수, 입력 스트림
        fgets(buffer, sizeof(buffer), stdin);

        // 종료 로직
        if (strncmp(buffer, "exit", 4) == 0) {
            write(client_fd, buffer, strlen(buffer));
            break;
        }

        // 데이터 전송
        // 보낼 대상, 버퍼, 버퍼 길이
        write(client_fd, buffer, strlen(buffer));
    }
    
    // 소켓 종료
    close(client_fd);
    close(server_fd);

    return 0;
}