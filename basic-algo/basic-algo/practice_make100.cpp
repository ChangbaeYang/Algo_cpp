#include<iostream>
#include<vector>
using namespace std;

// 특정한 값들이 주어졌을 때
// 해당한 값으로 100을 만들 수 있는지를 O(N)으로 확인하기
vector<int> V;
int n;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		V.push_back(temp);
	}
	int occur[101] = {};
	for (int i = 0; i < n; i++) {
		if (occur[100 - V[i]] == 1) {
			cout << "100을 만듦";
			return 0;
		}
		occur[V[i]]++;
	}
	cout << "100을 못만듦";
	return 0;
}