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


//전역 변수
unsigned char userkey[] = "0";
unsigned char IV[] = "\x0A\x91\x72\x71\x6A\xE6\x42\x84\x09\x88\x5B\x8B\x82\x9C\xCB\x05";

char option;
char path[_MAX_PATH];
char re_path[_MAX_PATH];
char file[_MAX_FNAME + _MAX_EXT];

_finddatai64_t fd;
intptr_t hFile;
AES_KEY key;


//함수
void Ask(const char* about, char& answer);
void Ask(const char* about, char* answer);
void Encryption_AES(char* filename);
void Decryption_AES(char* filename);
void Encryption_MD5(char* filename);
void PrintManual();
void PrintList();


int main(void)
{
	//기본 경로 설정
	_getcwd(path, _MAX_PATH); 

	//암호화 키 설정
	AES_set_encrypt_key(userkey, 128, &key);

	//Manual 출력
	PrintManual();

	while (true)
	{
		//Manual 선택
		printf("\n>> ");
		option = getchar();
		rewind(stdin);

		//실행
		switch (option){

		case 'e': //암호화

			//파일 목록 존재 여부 확인 ... path로 지정된 디렉토리 하위 모든 파일
			sprintf(re_path, "%s\\*.*",path);
			if ((hFile = _findfirsti64(re_path, &fd)) == -1L) {
				perror(re_path);
				break;
			}
			//파일 목록 출력
			PrintList();

			//파일 선택
			while (true) {
				Ask("file", file);
				sprintf(re_path, "%s\\%s", path, file);

				//성공
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

				//오류 : 파일 접근 실패
				perror(file);

				//오류 발생 시 재시도 여부
				Ask("다시 입력하시겠습니까?", option);
				if (option != 'y' && option != 'Y') {
					printf("(취소)\n\n");
					break;
				}
			}
			break;

		case 'd': //복호화

			//파일 목록 존재 여부 확인 ... path로 지정된 디렉토리 하위 enc 파일
			sprintf(re_path, "%s\\*.enc", path);
			if ((hFile = _findfirsti64(re_path, &fd)) == -1L) {
				perror(re_path);
				break;
			}
			//파일 목록 출력
			PrintList();

			//파일 선택
			while (true) {
				Ask("file", file);
				sprintf(re_path, "%s\\%s", path, file);

				//오류 : 파일 접근 실패
				if ((_access(re_path, 0) != 0))
					perror(file);

				//오류 : 지정된 확장자가 아님
				else if (strcmp(strrchr(file, '.'),".enc") != 0)
					printf("파일의 확장자는 enc이여야합니다.");

				//성공
				else {
					Decryption_AES(file);
					break;
				}

				//오류 발생 시 재시도 여부
				Ask("다시 입력하시겠습니까?", option);
				if (option != 'y' && option != 'Y') {
					printf("(취소)\n\n");
					break;
				}
			}
			break;

		case 'p': // 경로 수정
			while (true) {
				Ask("path", re_path);
				if (_access(re_path, 0) == 0) {
					strcpy(path, re_path);
					system("cls");
					PrintManual();
					break;
				}
				Ask("존재하지 않는 경로입니다. 다시 입력하시겠습니까?", option);
				if (option != 'y' && option != 'Y') {
					printf("(취소)\n");
					break;
				}
			}
			break;

		case 'r': //화면 초기화
			system("cls");
			PrintManual();
			break;

		case 'q': //종료
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

		//암호화
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

		//복호화
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

	//암호화
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
	printf(" p : path (경로 수정)\n");
	printf(" r : reset (초기화)\n");
	printf(" q : quit(종료)\n");
	printf("========================================================================\n\n");
	printf("path : %s\n\n", path);
}

void PrintList() {
	//목록 출력
	printf("============================== File List ===============================\n");
	do
	{
		if ((fd.attrib&_A_SUBDIR) == false)
			printf(" %s\n", fd.name);

	} while (_findnexti64(hFile, &fd) != -1L);
	_findclose(hFile);
	printf("========================================================================\n");
}

