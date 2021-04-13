#include <iostream>

using namespace std;

const int timeSlice = 5;

//선언

//스케줄링 함수

void FCFS(int arrivalTime[3], int workingTime[3]);

void SJF(int arrivalTime[3], int workingTime[3]);

void HRN(int arrivalTime[3], int workingTime[3]);

void RR(int arrivalTime[3], int workingTime[3]);

void SRT(int arrivalTime[3], int workingTime[3]);

int main() {

	//변수 선언

	int arrivalTime[3], workingTime[3];

	//값 입력받기

	do

	{

		//입력

		cout << "\n각 데이터의 프로세스 도착 시간과 작업 시간(ms)를 입력해 주세요.\n\n";

		for (int i = 0; i < 3; i++) {

			cout << " data" << i + 1 << " : ";

			cin >> arrivalTime[i] >> workingTime[i];

		}

		//간격조절

		cout << endl << endl;

		//만약 도착 순서가 맞지 않다면 다시 입력 받기

		if (arrivalTime[0] > arrivalTime[1] || arrivalTime[1] > arrivalTime[2]) {

			cout << "도착순서는 data1, data2, data3로 맞추어 가시 입력해주세요.\n";

		}

	} while (arrivalTime[0] > arrivalTime[1] || arrivalTime[1] > arrivalTime[2]);

	//출력하기

	FCFS(arrivalTime, workingTime);

	SJF(arrivalTime, workingTime);

	HRN(arrivalTime, workingTime);

	RR(arrivalTime, workingTime);

	SRT(arrivalTime, workingTime);

	return 0;

}

//계산을 위한 함수----------------------------------------------------------------------------------------------

//FCFS

//준비 큐에 도착한 순서대로 CPU를 할당하는 비선점형 방식

void FCFS(int at[3], int wt[3]) {

	int sum = 0;

	//데이터의 작업 중 d2 도착 시...d1의 작업 완료를 기다리기

	if (at[0] + wt[0] > at[1]) {

		sum += at[0] + wt[0] - at[1]; //d2의 대기 시간

	}

	//데이터의 작업 중 d3 도착 시...ㅇ2의 작업 완료를 기다리기

	if (at[0] + wt[0] + wt[1] > at[2]) {

		sum += at[0] + wt[0] + wt[1] - at[2]; //d3의 대기 시간

	}

	//출력

	if (sum % 3 == 0) {

		printf(" FCFS : %d ms\n", sum / 3);

	}

	else {

		printf(" FCFS : %.3f ms\n", ((float)sum) / 3);

	}

}

//SJF

//준비 큐에 있는 프로세스 중에서 실행 시간이 가장 짧은 작업부터 CPU를 할당하는 비선점형 방식

void SJF(int at[3], int wt[3]) {

	int sum = 0;

	//d1의 작업 중 d2과 d3 도착 시...작업 시간이 짧은 데이터 우선 처리

	if (at[0] + wt[0] > at[1] && at[0] + wt[0] > at[2]) {

		if (wt[1] < wt[2]) {

			sum += at[0] + wt[0] - at[1]; //d2의 대기 시간

			sum += at[0] + wt[0] + wt[1] - at[2]; //d3의 대기 시간

		}

		else {

			sum += at[0] + wt[0] - at[2]; //d3의 대기 시간

			sum += at[0] + wt[0] + wt[2] - at[1]; //d2의 대기 시간

		}

	}

	//d1의 작업 중 d2 도착 시

	else if (at[0] + wt[0] > at[1]) {

		sum += at[0] + wt[0] - at[2]; //d2의 대기 시간

		//d2의 작업 중 d3 도착 시

		if (at[0] + wt[0] + wt[1] > at[2]) {

			sum += at[0] + wt[0] + wt[1] - at[2]; //d3의 대기 시간

		}

	}

	//d2는 d1 작업 완료 후 도착

	//그리고 d2의 작업 중 d3 도착 시

	else if (at[1] + wt[1] > at[2]) {

		sum += at[1] + wt[1] - at[2]; //d2의 대기 시간

	}

	//출력

	if (sum % 3 == 0) {

		printf(" SJF : %d ms\n", sum / 3);

	}

	else {

		printf(" SJF : %.3f ms\n", ((float)sum) / 3);

	}

}

//HRN

//서비스를 받기 위해 기다린 시간과 CPU 사용 시간을 고려하여 스케줄링을 하는 방식

void HRN(int at[3], int wt[3]) {

	int sum = 0;

	float priority2, priority3;

	//d1의 작업 중 d2과 d3 도착 시

	if (at[0] + wt[0] > at[1] && at[0] + wt[0] > at[2]) {

		//우선순위 구하기

		priority2 = (at[0] + wt[0] - at[1] + wt[1]) / (at[0] + wt[0] - at[1]);

		priority3 = (at[0] + wt[0] - at[2] + wt[2]) / (at[0] + wt[0] - at[2]);

		//우선순위가 큰것을 우선으로 실행

		if (priority2 > priority3) {

			sum += at[0] + wt[0] - at[1]; //d2의 대기 시간

			sum += at[0] + wt[0] + wt[1] - at[2]; //d3의 대기 시간

		}

		else {

			sum += at[0] + wt[0] - at[2]; //d3의 대기 시간

			sum += at[0] + wt[0] + wt[2] - at[1]; //d2의 대기 시간

		}

	}

	//d1의 작업 중 d2 도착 시

	else if (at[0] + wt[0] + wt[1] > at[2]) {

		sum += at[0] + wt[0] - at[1]; //d2의 대기 시간

	}

	//d2의 작업 중 d3 도착 시

	else if (at[0] + wt[0] + wt[1] > at[2]) {

		sum += at[1] + wt[1] - at[2]; //d3의 대기 시간

	}

	//출력

	if (sum % 3 == 0) {

		printf(" HRN : %d ms\n", sum / 3);

	}

	else {

		printf(" HRN : %.3f ms\n", ((float)sum) / 3);

	}

}

//선점형 스케줄링

//타임 슬라이스는 5초

//큐 첫번째의 데이터가 실행되는 동안 나머지 데이터의 대기 시간을 합하는 방식을 사용

//RR

//한 프로세스가 할당 받은 시간(타임 슬라이스) 동안 작업을 하다가 작업을 완료하지 못하면 준비 큐의 맨 뒤로 가서 자기 차례를 기다리는 방식

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

		//대기 큐의 대기시간 구하기

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

		//상황 출력

		//printf(" [%3d, %3d, %3d]...%d\n", getWt[queue[0]], getWt[queue[1]], getWt[queue[2]], sum);

	}

	//출력

	if (sum % 3 == 0) {

		printf(" RR : %d ms\n", sum / 3);

	}

	else {

		printf(" RR : %.3f ms\n", ((float)sum) / 3);

	}

}

//SRT

//기본적으로 라운드 로빈 스케줄링을 사용하지만, CPU를 할당 받을 프로세스를 선택할 때 남아 있는 작업 시간이 가장 적은 프로세스를 선택

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

		//대기 큐의 대기시간 구하기

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

		//상황 출력

		//printf(" [%3d, %3d, %3d]...%d\n", getWt[queue[0]], getWt[queue[1]], getWt[queue[2]], sum);

	}

	//출력

	if (sum % 3 == 0) {

		printf(" SRT : %d ms\n\n", sum / 3);

	}

	else {

		printf(" SRT : %.3f ms\n\n", ((float)sum) / 3);

	}

}