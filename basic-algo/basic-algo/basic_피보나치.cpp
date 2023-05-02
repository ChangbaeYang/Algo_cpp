#include<iostream>
using namespace std;

int n;
int fibo(int n) {
	if (n <= 1) return 1;
	return fibo(n - 1) + fibo(n - 2);
}


int main() {
	cin >> n;
	int ret = fibo(n);
	cout << ret;
	return 0;
}