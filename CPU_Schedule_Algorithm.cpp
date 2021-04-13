#include <iostream>

using namespace std;

const int timeSlice = 5;

//����

//�����ٸ� �Լ�

void FCFS(int arrivalTime[3], int workingTime[3]);

void SJF(int arrivalTime[3], int workingTime[3]);

void HRN(int arrivalTime[3], int workingTime[3]);

void RR(int arrivalTime[3], int workingTime[3]);

void SRT(int arrivalTime[3], int workingTime[3]);

int main() {

	//���� ����

	int arrivalTime[3], workingTime[3];

	//�� �Է¹ޱ�

	do

	{

		//�Է�

		cout << "\n�� �������� ���μ��� ���� �ð��� �۾� �ð�(ms)�� �Է��� �ּ���.\n\n";

		for (int i = 0; i < 3; i++) {

			cout << " data" << i + 1 << " : ";

			cin >> arrivalTime[i] >> workingTime[i];

		}

		//��������

		cout << endl << endl;

		//���� ���� ������ ���� �ʴٸ� �ٽ� �Է� �ޱ�

		if (arrivalTime[0] > arrivalTime[1] || arrivalTime[1] > arrivalTime[2]) {

			cout << "���������� data1, data2, data3�� ���߾� ���� �Է����ּ���.\n";

		}

	} while (arrivalTime[0] > arrivalTime[1] || arrivalTime[1] > arrivalTime[2]);

	//����ϱ�

	FCFS(arrivalTime, workingTime);

	SJF(arrivalTime, workingTime);

	HRN(arrivalTime, workingTime);

	RR(arrivalTime, workingTime);

	SRT(arrivalTime, workingTime);

	return 0;

}

//����� ���� �Լ�----------------------------------------------------------------------------------------------

//FCFS

//�غ� ť�� ������ ������� CPU�� �Ҵ��ϴ� ������ ���

void FCFS(int at[3], int wt[3]) {

	int sum = 0;

	//�������� �۾� �� d2 ���� ��...d1�� �۾� �ϷḦ ��ٸ���

	if (at[0] + wt[0] > at[1]) {

		sum += at[0] + wt[0] - at[1]; //d2�� ��� �ð�

	}

	//�������� �۾� �� d3 ���� ��...��2�� �۾� �ϷḦ ��ٸ���

	if (at[0] + wt[0] + wt[1] > at[2]) {

		sum += at[0] + wt[0] + wt[1] - at[2]; //d3�� ��� �ð�

	}

	//���

	if (sum % 3 == 0) {

		printf(" FCFS : %d ms\n", sum / 3);

	}

	else {

		printf(" FCFS : %.3f ms\n", ((float)sum) / 3);

	}

}

//SJF

//�غ� ť�� �ִ� ���μ��� �߿��� ���� �ð��� ���� ª�� �۾����� CPU�� �Ҵ��ϴ� ������ ���

void SJF(int at[3], int wt[3]) {

	int sum = 0;

	//d1�� �۾� �� d2�� d3 ���� ��...�۾� �ð��� ª�� ������ �켱 ó��

	if (at[0] + wt[0] > at[1] && at[0] + wt[0] > at[2]) {

		if (wt[1] < wt[2]) {

			sum += at[0] + wt[0] - at[1]; //d2�� ��� �ð�

			sum += at[0] + wt[0] + wt[1] - at[2]; //d3�� ��� �ð�

		}

		else {

			sum += at[0] + wt[0] - at[2]; //d3�� ��� �ð�

			sum += at[0] + wt[0] + wt[2] - at[1]; //d2�� ��� �ð�

		}

	}

	//d1�� �۾� �� d2 ���� ��

	else if (at[0] + wt[0] > at[1]) {

		sum += at[0] + wt[0] - at[2]; //d2�� ��� �ð�

		//d2�� �۾� �� d3 ���� ��

		if (at[0] + wt[0] + wt[1] > at[2]) {

			sum += at[0] + wt[0] + wt[1] - at[2]; //d3�� ��� �ð�

		}

	}

	//d2�� d1 �۾� �Ϸ� �� ����

	//�׸��� d2�� �۾� �� d3 ���� ��

	else if (at[1] + wt[1] > at[2]) {

		sum += at[1] + wt[1] - at[2]; //d2�� ��� �ð�

	}

	//���

	if (sum % 3 == 0) {

		printf(" SJF : %d ms\n", sum / 3);

	}

	else {

		printf(" SJF : %.3f ms\n", ((float)sum) / 3);

	}

}

//HRN

//���񽺸� �ޱ� ���� ��ٸ� �ð��� CPU ��� �ð��� ����Ͽ� �����ٸ��� �ϴ� ���

void HRN(int at[3], int wt[3]) {

	int sum = 0;

	float priority2, priority3;

	//d1�� �۾� �� d2�� d3 ���� ��

	if (at[0] + wt[0] > at[1] && at[0] + wt[0] > at[2]) {

		//�켱���� ���ϱ�

		priority2 = (at[0] + wt[0] - at[1] + wt[1]) / (at[0] + wt[0] - at[1]);

		priority3 = (at[0] + wt[0] - at[2] + wt[2]) / (at[0] + wt[0] - at[2]);

		//�켱������ ū���� �켱���� ����

		if (priority2 > priority3) {

			sum += at[0] + wt[0] - at[1]; //d2�� ��� �ð�

			sum += at[0] + wt[0] + wt[1] - at[2]; //d3�� ��� �ð�

		}

		else {

			sum += at[0] + wt[0] - at[2]; //d3�� ��� �ð�

			sum += at[0] + wt[0] + wt[2] - at[1]; //d2�� ��� �ð�

		}

	}

	//d1�� �۾� �� d2 ���� ��

	else if (at[0] + wt[0] + wt[1] > at[2]) {

		sum += at[0] + wt[0] - at[1]; //d2�� ��� �ð�

	}

	//d2�� �۾� �� d3 ���� ��

	else if (at[0] + wt[0] + wt[1] > at[2]) {

		sum += at[1] + wt[1] - at[2]; //d3�� ��� �ð�

	}

	//���

	if (sum % 3 == 0) {

		printf(" HRN : %d ms\n", sum / 3);

	}

	else {

		printf(" HRN : %.3f ms\n", ((float)sum) / 3);

	}

}

//������ �����ٸ�

//Ÿ�� �����̽��� 5��

//ť ù��°�� �����Ͱ� ����Ǵ� ���� ������ �������� ��� �ð��� ���ϴ� ����� ���

//RR

//�� ���μ����� �Ҵ� ���� �ð�(Ÿ�� �����̽�) ���� �۾��� �ϴٰ� �۾��� �Ϸ����� ���ϸ� �غ� ť�� �� �ڷ� ���� �ڱ� ���ʸ� ��ٸ��� ���

void RR(int at[3], int wt[3]) {

	int sum = 0;

	int working = 0;

	int time = 0;

	int queue[3] = { 0,1,2 };

	int getWt[3];

	for (int i = 0; i < 3; i++) {

		getWt[i] = wt[i];

	}

	//printf(" [%3d, %3d, %3d]...%d\n", getWt[queue[0]], getWt[queue[1]], getWt[queue[2]], sum);

	while (getWt[queue[0]] > 0 || getWt[queue[1]] > 0 || getWt[queue[2]] > 0) {

		//dequeue

		if (getWt[queue[0]] > timeSlice) {

			working = timeSlice;

		}

		else {

			working = getWt[queue[0]];

		}

		time += working;

		//��� ť�� ���ð� ���ϱ�

		if (time > at[queue[1]] && getWt[queue[1]] > 0) {

			if (at[queue[1]] > time - timeSlice) {

				sum += time - at[queue[1]];

				//cout << "1 " << time - at[queue[1]]<<endl;

			}

			else if (getWt[queue[0]] > timeSlice) {

				sum += timeSlice;

				//cout << "2 " << timeSlice<< endl;

			}

			else if (getWt[queue[0]] > 0) {

				sum += getWt[queue[0]];

				//cout << "3 " << getWt[queue[0]]<< endl;

			}

		}

		if (time > at[queue[2]] && getWt[queue[2]] > 0) {

			if (at[queue[2]] > time - timeSlice) {

				sum += time - at[queue[2]];

				//cout << "1 " << time - at[queue[2]]<< endl;

			}

			else if (getWt[queue[0]] > timeSlice) {

				sum += timeSlice;

				//cout << "2 " << timeSlice<< endl;

			}

			else if (getWt[queue[0]] > 0) {

				sum += getWt[queue[0]];

				//cout << "3 " << getWt[queue[0]]<< endl;

			}

		}

		getWt[queue[0]] -= working;

		//enqueue

		int temp = queue[0];

		for (int i = 0; i < 2; i++) {

			queue[i] = queue[i + 1];

		}

		queue[2] = temp;

		//��Ȳ ���

		//printf(" [%3d, %3d, %3d]...%d\n", getWt[queue[0]], getWt[queue[1]], getWt[queue[2]], sum);

	}

	//���

	if (sum % 3 == 0) {

		printf(" RR : %d ms\n", sum / 3);

	}

	else {

		printf(" RR : %.3f ms\n", ((float)sum) / 3);

	}

}

//SRT

//�⺻������ ���� �κ� �����ٸ��� ���������, CPU�� �Ҵ� ���� ���μ����� ������ �� ���� �ִ� �۾� �ð��� ���� ���� ���μ����� ����

void SRT(int at[3], int wt[3]) {

	int sum = 0;

	int working = 0;

	int time = 0;

	int queue[3] = { 0,1,2 };

	int getWt[3];

	for (int i = 0; i < 3; i++) {

		getWt[i] = wt[i];

	}

	//printf(" [%3d, %3d, %3d]...%d\n", getWt[queue[0]], getWt[queue[1]], getWt[queue[2]], sum);

	while (getWt[queue[0]] > 0 || getWt[queue[1]] > 0 || getWt[queue[2]] > 0) {

		//dequeue

		if (getWt[queue[0]] > timeSlice) {

			working = timeSlice;

		}

		else {

			working = getWt[queue[0]];

		}

		time += working;

		//��� ť�� ���ð� ���ϱ�

		if (time > at[queue[1]] && getWt[queue[1]] > 0) {

			if (at[queue[1]] > time - timeSlice) {

				sum += time - at[queue[1]];

				//cout << "1 " << time - at[queue[1]]<<endl;

			}

			else if (getWt[queue[0]] > timeSlice) {

				sum += timeSlice;

				//cout << "2 " << timeSlice<< endl;

			}

			else if (getWt[queue[0]] > 0) {

				sum += getWt[queue[0]];

				//cout << "3 " << getWt[queue[0]]<< endl;

			}

		}

		if (time > at[queue[2]] && getWt[queue[2]] > 0) {

			if (at[queue[2]] > time - timeSlice) {

				sum += time - at[queue[2]];

				//cout << "1 " << time - at[queue[2]]<< endl;

			}

			else if (getWt[queue[0]] > timeSlice) {

				sum += timeSlice;

				//cout << "2 " << timeSlice<< endl;

			}

			else if (getWt[queue[0]] > 0) {

				sum += getWt[queue[0]];

				//cout << "3 " << getWt[queue[0]]<< endl;

			}

		}

		getWt[queue[0]] -= working;

		//enqueue

		int temp = queue[0];

		if (getWt[queue[0]] == 0) {

			if (getWt[queue[1]] > 0 && getWt[queue[1]] < getWt[queue[2]]) {

				queue[0] = queue[1];

				queue[1] = temp;

			}

			else if (getWt[queue[2]] > 0) {

				queue[0] = queue[2];

				queue[2] = temp;

			}

		}

		else if (getWt[queue[1]] > 0

			&& getWt[queue[1]] < getWt[queue[0]]

			&& getWt[queue[1]] < getWt[queue[2]]) {

			queue[0] = queue[1];

			queue[1] = temp;

		}

		else if (getWt[queue[2]] > 0

			&& getWt[queue[2]] < getWt[queue[0]]

			&& getWt[queue[2]] < getWt[queue[1]]) {

			queue[0] = queue[2];

			queue[2] = temp;

		}

		//��Ȳ ���

		//printf(" [%3d, %3d, %3d]...%d\n", getWt[queue[0]], getWt[queue[1]], getWt[queue[2]], sum);

	}

	//���

	if (sum % 3 == 0) {

		printf(" SRT : %d ms\n\n", sum / 3);

	}

	else {

		printf(" SRT : %.3f ms\n\n", ((float)sum) / 3);

	}

}