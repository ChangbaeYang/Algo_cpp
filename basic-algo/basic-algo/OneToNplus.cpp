#include<iostream>
using namespace std;

int recur(int n) {
	if (n == 0) return 0;
	return n + recur(n - 1);
}

int main() {
	int n = 0;
	cin >> n;
	int result = recur(n);
	cout << result;
	return 0;
}