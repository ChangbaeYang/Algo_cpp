#include<iostream>
#define MAX_N 100
/*
	�迭�� ���ؼ� ������ ���� �����غ���
*/
using namespace std;

int stack[MAX_N];
int top;

void stackInit() {
	top = 0;
}

int stackIsEmpty() {
	return (top == 0);
}

int stackIsFull() {
	return (top == MAX_N);
}

int stackPush(int value) {
	if (stackIsFull()) {
		cout << "stack is overflow!" << "\n";
		return 0;
	}
	stack[top] = value;
	top++;
	return 1;
}

int stackPop(int* value) {
	if (stackIsEmpty()) {
		cout << "stack is empty!" << "\n";
		return 0;
	}
	top--;	// Ǫ���� �� top���� �� ĭ �ö��������Ƿ�
	*value = stack[top];

	return 1;
}

int main() {
	int T, N;	// T: test case, N: �־��� ������ ũ��
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N;
		stackInit();
		for (int i = 0; i < N; i++) {
			int value;
			cin >> value;
			if (stackIsFull()) break;
			stackPush(value);
		}
		while (!stackIsEmpty()) {
			int value;
			if (stackPop(&value) == 1) {
				cout << value << " ";
			}
		}
		cout << "\n";
	}
	return 0;
}
