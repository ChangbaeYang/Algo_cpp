#include<iostream>
#include<stack>
using namespace std;

int k;
stack<int> S;

int main() {
	cin >> k;
	for (int i = 0; i < k; i++) {
		int temp;
		cin >> temp;
		if (temp == 0) {
			S.pop();
		}
		else {
			S.push(temp);
		}
	}
	long long ret = 0;
	while (S.size()) {
		ret += S.top();
		S.pop();
	}
	cout << ret << "\n";
	return 0;
}