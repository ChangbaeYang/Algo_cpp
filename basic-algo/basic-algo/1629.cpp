#include<iostream>
#include<vector>
using namespace std;
using ll = long long;

ll a, b, m;	// a, b, m는 각각 21억씩
int ret;
vector<int> v;

ll POW(int a, int b, int m) {
	if (b == 1) return a % m;
	ll val = POW(a, b / 2, m);
	val = val * val % m;
	if (b % 2 == 0) return val;
	return val * a % m;
}

int main() {
	cin >> a >> b >> m;
	cout << POW(a, b, m);
	return 0;
}