#include<iostream>
#include<queue>
using namespace std;

int n, k;
int arr[100001];
int ret;

int main() {
	cin >> n >> k;
	fill(arr, arr + 100001, -1);
	queue<int> Q;
	Q.push(n);
	arr[n] = 0;
	while (!Q.empty()) {
		auto curr = Q.front(); Q.pop();
		if (curr == k) break;
		int np = curr + 1;
		int np2 = curr - 1;
		int np3 = curr * 2;
		if (np >= 0 && np < 100001 && arr[np] == -1) {
			arr[np] = arr[curr] + 1;
			Q.push(np);
		}
		if (np2 >= 0 && np2 < 100001 && arr[np2] == -1) {
			arr[np2] = arr[curr] + 1;
			Q.push(np2);
		}
		if (np3 >= 0 && np3 < 100001 && arr[np3] == -1) {
			arr[np3] = arr[curr] + 1;
			Q.push(np3);
		}
	}
	cout << arr[k];
	return 0;
}