#include <iostream>

using namespace std;


/*
날짜 : 2020.03.27.금
이름 : 이헤원

강의 : 현대암호학응용및실습
분반 : 02

과제 : 고대 또는 근대 암호 알고리즘 1개 만들기
선택 : 소스코드 방식 - 시저암호
*/


//함수 선언
void Caesar(char *plain, char *en, int num);

int main() {
	char en[100] = "";	//암호문
	char plain[100];	//평문
	int num = 0;		//평행 이동할 정도

	//값 입력받기
	cout << "\n평문 입력 : ";
	cin >> plain;
	cout << "\n평행 이동 : ";
	cin >> num;

	//출력
	Caesar(plain, en, num);

	return 0;
}

/*
* plain	: 평문 매개변수
* en	: 암호문 매개변수이자 출력해야할 값
* num	: 평행 이동할 정도
*/
void Caesar(char *plain, char *en, int num) {
	char tmp;
	int i;

	//입력한 문자 길이만큼 반복
	for (i=0; *plain; en++, plain++, i++) {

		//숫자나 문자인 경우
		if (isalnum(*plain) != 0) {

			//숫자 문자일 때
			if (*plain >= '0' && *plain <= '9')		//isdigit(*plain)
				tmp = '0';	//48

			//대문자 처리
			else if (*plain >= 'A' && *plain <= 'Z')	//isupper(*plain)
				tmp = 'A';	//65

			//소문자 처리
			else if (*plain >= 'a' && *plain <= 'z')	//islower(*plain)
				tmp = 'a';	//97


			//num 값 만큼 값을 변경 (예시 : plain = a, num = 5 --> en = f)
			*en = (*plain - tmp + num) % (tmp>'0' ? 26 : 10) + tmp;
		}

		//문자도 숫자도 아닌 경우 (예시 : !,@,#,$,%,... )
		else 
			*en = *plain;

	}

	//포인터 위치 제자리로
	en -= i;

	//출력
	cout << "\n암호화 \n > " << en << endl << endl << endl;
}
