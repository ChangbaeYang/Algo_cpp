#include<iostream>
using namespace std;

int n;

int recur(int n) {
	if (n == 0) return 0;
	return n + recur(n - 1);
}

int main() {
	cin >> n;
	int ret = 0;
	ret = recur(10);
	cout << ret;
	return 0;
}
