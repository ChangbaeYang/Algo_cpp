#include<iostream>
using namespace std;

// 가정 : 첫 번째 매개변수는 항상 두 번째 매개변수보다 작다.
int sum(int a, int b) {
	int s = 0;
	for (int i = a; i <= b; i++) {
		s += i;
	}
	return s;
}

int sum(int a) {
	int s = 0;
	for (int i = 0; i <= a; i++) {
		s += i;
	}
	return s;
}

int main() {
	cout << sum(3, 5) << "\n";
	cout << sum(3) << "\n";
	cout << sum(100) << "\n";
	return 0;
}