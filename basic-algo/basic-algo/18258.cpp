#include <iostream>
#include <string>

using namespace std;
// queue를 직접 구현해봅시다. -> 큐(10845) 문제와 N의 크기만 다름

const int MX = 2000001;
int dat[MX];
int head = 0, tail = 0;

bool size() {
	cout << tail - head << "\n";
	return tail - head;
}

bool empty() {
	if (tail == head) cout << 1 << "\n";
	else cout << 0 << "\n";
	return tail == head;
}

void push(int x) {
	dat[tail++] = x;
}

void pop() {
	if (tail != head) {
		cout << dat[head++] << "\n";
	}
	else cout << -1 << "\n";
}

void front() {
	if (tail != head) {
		cout << dat[head] << "\n";
	}
	else cout << -1 << "\n";
}

void back() {
	if (tail != head) {
		cout << dat[tail - 1] << "\n";
	}
	else cout << -1 << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n = 0;
	cin >> n;
	string input_str;
	while (n--) {
		cin >> input_str;
		if (input_str == "push") {
			int input_int;
			cin >> input_int;
			push(input_int);
		}
		else if (input_str == "pop") pop();
		else if (input_str == "empty")empty();
		else if (input_str == "size") size();
		else if (input_str == "front") front();
		else if (input_str == "back") back();
	}
	// 중복 출력문제가 있음! -> empty, size
	return 0;
}
