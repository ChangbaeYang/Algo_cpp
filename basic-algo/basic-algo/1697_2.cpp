#include<iostream>
#include<queue>
using namespace std;

int n, k;
int arr[100002];	// 배열 변수를 바로 visited 처리하는 데에 활용할 것이다.

int main() {
	cin >> n >> k;
	fill(arr, arr + 100002, -1);	// 방문 안한점 -1처리
	queue<int> q;
	q.push(n);
	arr[n] = 0;
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		if (curr == k) break;
		int np = curr + 1;
		int np2 = curr - 1;
		int np3 = curr * 2;
		// 해당 점이 범위 안이고, 방문하지 않았던 점이라면
		// &&을 통해서 앞의 값이 거짓이라면 뒤의 값을 판단하지 않도록해서
		// array 범위가 넘어가는 일을 없도록 방지한다.
		if (np >= 0 && np < 100002 && arr[np] == -1) {
			arr[np] = arr[curr] + 1;
			q.push(np);
		}
		if (np2 >= 0 && np2 < 100002 && arr[np2] == -1) {
			arr[np2] = arr[curr] + 1;
			q.push(np2);
		}
		if (np3 >= 0 && np3 < 100002 && arr[np3] == -1) {
			arr[np3] = arr[curr] + 1;
			q.push(np3);
		}
	}
	cout << arr[k];
	return 0;
}