#include<iostream>
using namespace std;

// n부터 1까지 출력

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