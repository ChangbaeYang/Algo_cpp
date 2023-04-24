#include<iostream>
using namespace std;
using ll = long long;

ll a, b, c;
int ret;

int func1(int a, int b, int c) {
	ll val = 1;
	while (b--) val = val * a % c;
	return val;
}

int main() {
	cin >> a >> b >> c;
	ret = func1(a, b, c);
	cout << ret;
	return 0;
}