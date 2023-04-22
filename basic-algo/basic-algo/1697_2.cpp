#include<iostream>
#include<queue>
using namespace std;

int n, k;
int arr[100002];	// �迭 ������ �ٷ� visited ó���ϴ� ���� Ȱ���� ���̴�.

int main() {
	cin >> n >> k;
	fill(arr, arr + 100002, -1);	// �湮 ������ -1ó��
	queue<int> q;
	q.push(n);
	arr[n] = 0;
	while (!q.empty()) {
		int curr = q.front(); q.pop();
		if (curr == k) break;
		int np = curr + 1;
		int np2 = curr - 1;
		int np3 = curr * 2;
		// �ش� ���� ���� ���̰�, �湮���� �ʾҴ� ���̶��
		// &&�� ���ؼ� ���� ���� �����̶�� ���� ���� �Ǵ����� �ʵ����ؼ�
		// array ������ �Ѿ�� ���� ������ �����Ѵ�.
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