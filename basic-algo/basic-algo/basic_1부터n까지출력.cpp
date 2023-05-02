#include<iostream>
using namespace std;

int n;

void recur(int x) {
	if (x == n) {
		cout << x;
		return;
	}
	cout << x << "\n";
	recur(x + 1);
}

int main() {
	cin >> n;
	recur(1);
}