#include<iostream>
#define MAX_N 100
/*
	배열을 통해서 스택을 직접 구현해보기
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
	top--;	// 푸시할 때 top값이 한 칸 올라가져있으므로
	*value = stack[top];

	return 1;
}

int main() {
	int T, N;	// T: test case, N: 주어질 데이터 크기
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
