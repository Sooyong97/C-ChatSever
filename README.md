#  Simple C Socket Chat Program

##  프로젝트 설명

이 프로젝트는 **C를 이용한 TCP 기반 1:1 채팅 프로그램**입니다.  
주 목적은 C 소켓 프로그래밍을 학습하고, 서버-클라이언트 구조의 기본 개념을 익히는 것입니다.

- **소켓(Socket)** 통신의 기본 흐름을 이해하고
- **TCP 프로토콜** 기반으로 데이터를 주고받는 과정을 공부.

---

##  프로그램 구조 및 동작 방식

###  구성

```
📁 project_root/
├── server.c   //  서버 소스
├── client.c   //  클라이언트 소스
└── README.md
```

###  동작 방식 요약

#### 1. 서버 (`server.c`)
- `socket()` 으로 소켓 생성
- `bind()`로 IP/포트 할당
- `listen()`으로 연결 대기
- `accept()`로 클라이언트 연결 수락
- `read()`/`write()`로 메시지 송수신

#### 2. 클라이언트 (`client.c`)
- `socket()`으로 소켓 생성
- `connect()`로 서버에 접속 시도
- 사용자 입력 → `write()`로 서버에 전송
- 서버 응답 → `read()`로 수신 후 출력

###  실행

**1. 컴파일**

```bash
gcc server.c -o server
gcc client.c -o client
```

**2. 실행 (두 개의 터미널 사용)**

- 터미널 1: 서버 실행
```bash
./server
```

- 터미널 2: 클라이언트 실행
```bash
./client
```

채팅을 입력하면 양방향으로 주고받을 수 있습니다.


##  정리

| 항목 | 설명 |
|------|------|
| 언어 | C |
| 방식 | TCP/IP 소켓 프로그래밍 |
| 통신 | 1:1 채팅 (한 명의 클라이언트만 지원) |
| 목적 | C 소켓 기초 학습, 네트워크 개념 실습 |
