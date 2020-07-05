#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <direct.h>
#include <io.h>
#include <openssl/aes.h>
#include <openssl/md5.h>

#define COLOR_CYAN printf("\x1b[96m")
#define COLOR_YELLOW printf("\x1b[93m")
#define COLOR_RESET printf("\x1b[0m")
#define LINE_CLEAR printf("\33[2K\x1b[A")


//���� ����
unsigned char userkey[] = "0";
unsigned char IV[] = "\x0A\x91\x72\x71\x6A\xE6\x42\x84\x09\x88\x5B\x8B\x82\x9C\xCB\x05";

char option;
char path[_MAX_PATH];
char re_path[_MAX_PATH];
char file[_MAX_FNAME + _MAX_EXT];

_finddatai64_t fd;
intptr_t hFile;
AES_KEY key;


//�Լ�
void Ask(const char* about, char& answer);
void Ask(const char* about, char* answer);
void Encryption_AES(char* filename);
void Decryption_AES(char* filename);
void Encryption_MD5(char* filename);
void PrintManual();
void PrintList();


int main(void)
{
	//�⺻ ��� ����
	_getcwd(path, _MAX_PATH); 

	//��ȣȭ Ű ����
	AES_set_encrypt_key(userkey, 128, &key);

	//Manual ���
	PrintManual();

	while (true)
	{
		//Manual ����
		printf("\n>> ");
		option = getchar();
		rewind(stdin);

		//����
		switch (option){

		case 'e': //��ȣȭ

			//���� ��� ���� ���� Ȯ�� ... path�� ������ ���丮 ���� ��� ����
			sprintf(re_path, "%s\\*.*",path);
			if ((hFile = _findfirsti64(re_path, &fd)) == -1L) {
				perror(re_path);
				break;
			}
			//���� ��� ���
			PrintList();

			//���� ����
			while (true) {
				Ask("file", file);
				sprintf(re_path, "%s\\%s", path, file);

				//����
				if (_access(re_path, 0) == 0) {
					printf("\na : AES\nm : MD5\n");
					while (true) {
						Ask("\n>>", option);
						if (option == 'a') {
							Encryption_AES(file);
							break;
						}
						else if (option == 'm') {
							Encryption_MD5(file);
							break;
						}
						else
							LINE_CLEAR;
					}
					break;
				}

				//���� : ���� ���� ����
				perror(file);

				//���� �߻� �� ��õ� ����
				Ask("�ٽ� �Է��Ͻðڽ��ϱ�?", option);
				if (option != 'y' && option != 'Y') {
					printf("(���)\n\n");
					break;
				}
			}
			break;

		case 'd': //��ȣȭ

			//���� ��� ���� ���� Ȯ�� ... path�� ������ ���丮 ���� enc ����
			sprintf(re_path, "%s\\*.enc", path);
			if ((hFile = _findfirsti64(re_path, &fd)) == -1L) {
				perror(re_path);
				break;
			}
			//���� ��� ���
			PrintList();

			//���� ����
			while (true) {
				Ask("file", file);
				sprintf(re_path, "%s\\%s", path, file);

				//���� : ���� ���� ����
				if ((_access(re_path, 0) != 0))
					perror(file);

				//���� : ������ Ȯ���ڰ� �ƴ�
				else if (strcmp(strrchr(file, '.'),".enc") != 0)
					printf("������ Ȯ���ڴ� enc�̿����մϴ�.");

				//����
				else {
					Decryption_AES(file);
					break;
				}

				//���� �߻� �� ��õ� ����
				Ask("�ٽ� �Է��Ͻðڽ��ϱ�?", option);
				if (option != 'y' && option != 'Y') {
					printf("(���)\n\n");
					break;
				}
			}
			break;

		case 'p': // ��� ����
			while (true) {
				Ask("path", re_path);
				if (_access(re_path, 0) == 0) {
					strcpy(path, re_path);
					system("cls");
					PrintManual();
					break;
				}
				Ask("�������� �ʴ� ����Դϴ�. �ٽ� �Է��Ͻðڽ��ϱ�?", option);
				if (option != 'y' && option != 'Y') {
					printf("(���)\n");
					break;
				}
			}
			break;

		case 'r': //ȭ�� �ʱ�ȭ
			system("cls");
			PrintManual();
			break;

		case 'q': //����
			exit(1);

		default:
			LINE_CLEAR;
			LINE_CLEAR;
			break;
		}
	}

	return 0;
}

void Ask(const char* about, char& answer) {
	printf("%s ", about);
	answer = getchar();
	rewind(stdin);
}

void Ask(const char* about, char* answer) {
	printf("\n%s : ", about);
	scanf("%[^\n]s", answer);
	rewind(stdin);
}

void Encryption_AES(char* filename) {

	unsigned char indata[AES_BLOCK_SIZE] = {'\0',};
	unsigned char outdata[AES_BLOCK_SIZE] = { '\0', };

	FILE* ifp, *ofp;
	ifp = fopen(re_path, "r+");
	ofp = fopen(strcat(strtok(re_path, "."), ".enc"), "w+");

	int postion = 0;
	int bytes_read, bytes_write;

	
	while (1)
	{
		unsigned char ivec[AES_BLOCK_SIZE];
		memcpy(ivec, IV, AES_BLOCK_SIZE);
		bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);

		//Plain Text
		printf("\n%s >>\n", filename);
		COLOR_CYAN;
		printf("%s\n", indata);
		COLOR_RESET;

		//��ȣȭ
		AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &postion, AES_ENCRYPT);
		bytes_write = fwrite(outdata, 1, bytes_read, ofp);

		//Encryption Text
		printf("\n%s >>\n", strcat(strtok(filename, "."), ".enc"));
		COLOR_YELLOW;
		printf("%s\n\n\n", outdata);
		COLOR_RESET;

		if (bytes_read < AES_BLOCK_SIZE)
			break;
	}
	fclose(ifp);
	fclose(ofp);

}

void Decryption_AES(char* filename) {
	unsigned char indata[AES_BLOCK_SIZE] = { '\0', };
	unsigned char outdata[AES_BLOCK_SIZE] = { '\0', };

	FILE* ifp, *ofp;
	ifp = fopen(re_path, "r+");
	ofp = fopen(strcat(strtok(re_path, "."), ".dec"), "w+");

	int postion = 0;
	int bytes_read, bytes_write;

	while (1)
	{
		unsigned char ivec[AES_BLOCK_SIZE];
		memcpy(ivec, IV, AES_BLOCK_SIZE);
		bytes_read = fread(indata, 1, AES_BLOCK_SIZE, ifp);

		//��ȣȭ
		AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &postion, AES_DECRYPT);
		bytes_write = fwrite(outdata, 1, bytes_read, ofp);

		//Decryption Text
		printf("\Decryption_AES : %s >>\n", strcat(strtok(filename, "."), ".dec"));
		COLOR_CYAN;
		printf("%s\n\n\n", outdata);
		COLOR_RESET;

		if (bytes_read < AES_BLOCK_SIZE)
			break;
	}
	fclose(ifp);
	fclose(ofp);
}

void Encryption_MD5(char* filename) {
	char indata[100];
	char digest[200];
	unsigned char outdata[MD5_DIGEST_LENGTH];

	FILE* fp = fopen(re_path, "r+");
	fgets(indata, sizeof(indata), fp);
	fclose(fp);

	//Plain Text
	printf("\n%s >>\n", filename);
	COLOR_CYAN;
	printf("%s\n", indata);
	COLOR_RESET;

	//��ȣȭ
	MD5((unsigned char*)&indata, strlen(indata), (unsigned char*)&outdata);

	for (int i = 0; i < strlen(indata); ++i)
		sprintf(digest + (i * 2), "%02x", (unsigned int)outdata[i]);

	//Encryption Text
	printf("\nmd5 digest >>\n");
	COLOR_YELLOW;
	printf("%s\n\n\n", digest);
	COLOR_RESET;

}

void PrintManual() {
	printf("\n=================================Manual=================================\n");
	printf(" e : File encryption (AES/MD5)\n");
	printf(" d : File Decryption (AES)\n");
	printf(" p : path (��� ����)\n");
	printf(" r : reset (�ʱ�ȭ)\n");
	printf(" q : quit(����)\n");
	printf("========================================================================\n\n");
	printf("path : %s\n\n", path);
}

void PrintList() {
	//��� ���
	printf("============================== File List ===============================\n");
	do
	{
		if ((fd.attrib&_A_SUBDIR) == false)
			printf(" %s\n", fd.name);

	} while (_findnexti64(hFile, &fd) != -1L);
	_findclose(hFile);
	printf("========================================================================\n");
}

