#include<iostream>
using namespace std;

// n���� 1���� ���

void recur(int n) {
	if (n == 0) return;
	cout << n << "\n";
	recur(n - 1);
}

int a;

int main() {
	cin >> a;
	recur(a);
}