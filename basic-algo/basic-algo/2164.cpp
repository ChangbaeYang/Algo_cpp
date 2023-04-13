#include<iostream>
using namespace std;

const int MX = 1000001;
int n;	// 1~50�� O(logN)���� ����
int dat[MX];
int head = 500001, tail;
bool finish = false;

void pop_and_push() {
	// ���� ���� �ִ� ī�带 ������
	tail--;
	if (head == tail) {
		finish = true;
		return;
	}
	dat[head - 1] = dat[tail--];
	head--;
}

int main() {
	cin >> n;
	tail = 500000 + n;
	for (int i = n + 500001 - 1; i > 500000; i--) {
		dat[i] = 500001 + n - i;
	}

	while (head != tail) {
		if (finish) break;
		pop_and_push();
	}
	cout << dat[head] << "\n";
	return 0;
}