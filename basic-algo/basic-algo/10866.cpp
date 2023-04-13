#include<iostream>

// deque를 직접 구현해보자(배열)
using namespace std;

int n;
const int MX = 10000;
int dat[2 * MX + 1];
int head = MX, tail = MX;

void push_front(int x) {
	dat[--head] = x;
}

void push_back(int x) {
	dat[tail++] = x;
}

void size() {
	cout << tail - head << "\n";
}

void empty() {
	if (head == tail) {
		cout << 1 << "\n";
	}
	else cout << 0 << "\n";
}

void pop_front() {
	if (head == tail) cout << -1 << "\n";
	else cout << dat[head++] << "\n";
}

void pop_back() {
	if (head == tail) cout << -1 << "\n";
	else cout << dat[--tail] << "\n";
}

void front() {
	if (head == tail) cout << -1 << "\n";
	else cout << dat[head] << "\n";
}

void back() {
	if (head == tail) cout << -1 << "\n";
	else cout << dat[tail - 1] << "\n";
}

int main() {
	cin >> n;
	string temp;
	while (n--) {
		cin >> temp;
		if (temp == "push_front") {
			int temp_int;
			cin >> temp_int;
			push_front(temp_int);
		}
		else if (temp == "push_back") {
			int temp_int;
			cin >> temp_int;
			push_back(temp_int);
		}
		else if (temp == "size")size();
		else if (temp == "empty")empty();
		else if (temp == "pop_front")pop_front();
		else if (temp == "pop_back")pop_back();
		else if (temp == "front")front();
		else if (temp == "back")back();
	}
	return 0;
}