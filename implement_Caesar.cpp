#include <iostream>

using namespace std;


/*
��¥ : 2020.03.27.��
�̸� : �����

���� : �����ȣ������׽ǽ�
�й� : 02

���� : ��� �Ǵ� �ٴ� ��ȣ �˰��� 1�� �����
���� : �ҽ��ڵ� ��� - ������ȣ
*/


//�Լ� ����
void Caesar(char *plain, char *en, int num);

int main() {
	char en[100] = "";	//��ȣ��
	char plain[100];	//��
	int num = 0;		//���� �̵��� ����

	//�� �Է¹ޱ�
	cout << "\n�� �Է� : ";
	cin >> plain;
	cout << "\n���� �̵� : ";
	cin >> num;

	//���
	Caesar(plain, en, num);

	return 0;
}

/*
* plain	: �� �Ű�����
* en	: ��ȣ�� �Ű��������� ����ؾ��� ��
* num	: ���� �̵��� ����
*/
void Caesar(char *plain, char *en, int num) {
	char tmp;
	int i;

	//�Է��� ���� ���̸�ŭ �ݺ�
	for (i=0; *plain; en++, plain++, i++) {

		//���ڳ� ������ ���
		if (isalnum(*plain) != 0) {

			//���� ������ ��
			if (*plain >= '0' && *plain <= '9')		//isdigit(*plain)
				tmp = '0';	//48

			//�빮�� ó��
			else if (*plain >= 'A' && *plain <= 'Z')	//isupper(*plain)
				tmp = 'A';	//65

			//�ҹ��� ó��
			else if (*plain >= 'a' && *plain <= 'z')	//islower(*plain)
				tmp = 'a';	//97


			//num �� ��ŭ ���� ���� (���� : plain = a, num = 5 --> en = f)
			*en = (*plain - tmp + num) % (tmp>'0' ? 26 : 10) + tmp;
		}

		//���ڵ� ���ڵ� �ƴ� ��� (���� : !,@,#,$,%,... )
		else 
			*en = *plain;

	}

	//������ ��ġ ���ڸ���
	en -= i;

	//���
	cout << "\n��ȣȭ \n > " << en << endl << endl << endl;
}
