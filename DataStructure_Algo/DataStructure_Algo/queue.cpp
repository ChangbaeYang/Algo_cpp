#include<iostream>
#define MAX_N 100
using namespace std;

int front;
int rear;
int queue[MAX_N];

void queueInit() {
	front = 0;
	rear = 0;
}

int queueIsEmpty() {
	return (front == rear);
}

int queueIsFull() {
	if ((rear + 1) % MAX_N == front) {
		return 1;
	}
	else return 0;
}

int queueEnqueue(int value) {
	if (queueIsFull()) {
		cout << "queue is full!" << "\n";
		return 0;
	}
	queue[rear] = value;
	rear++;
	// 마지막 칸을 넣게 되면 rear가 앞칸으로 간다.(rear = 0)
	if (rear == MAX_N) {
		rear = 0;
	}
	return 1;
}

int queueDequeue(int* value) {
	if (queueIsEmpty()) {
		cout << "queue is empty!" << "\n";
		return 0;
	}
	*value = queue[front];
	front++;
	if (front == MAX_N) {
		front = 0;
	}
	return 1;
}

int main() {
	int T, N;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		for (int i = 0; i < N; i++) {
			int value;
			cin >> value;
			queueEnqueue(value);
		}
		cout << tc << " ";
		while (!queueIsEmpty()) {
			int value;
			if (queueDequeue(&value) == 1) {
				cout << value << " ";
			}
		}
		cout << "\n";
	}
	return 0;
}