#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

int m, n;
int arr[1002][1002];
int vis[1002][1002];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int main() {
	cin >> m >> n;
	queue<pair<int, int>> Q;	// �丶���� ��ġ�� ���� ť
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) {
				vis[i][j] = 1;
				Q.push({ i, j });
			}
			else if (arr[i][j] == -1) {
				vis[i][j] = -1;	// ���� -1 ó���� ���ش�.
			}
		}
	}
	
	// BFS������ �����غ���. -> �̹� �ռ��� �Ʒ��� �� ���������ߴ�.
	// 1. ���� �丶�� ������ ���� Q�� ����ֱ�
	// 2. ���� �丶���� ��ǥ �湮ó��
	while (!Q.empty()) {
		auto curr = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (vis[nx][ny] != 0) continue;	// vis[nx][ny]�� 0�� �ƴϸ�, �湮�� ���̰ų�, ���̴�.
			vis[nx][ny] = vis[curr.first][curr.second] + 1;
			Q.push({ nx, ny });
		}
	}
	
	// ������ �丶�䰡 �ִ��� Ȯ���Ѵ�.
	// ������ �丶�䰡 ������ -1����Ѵ�.(0�� �ִ� ���)
	// ������ �丶�䰡 ������ �ִ밪 -1�� ����Ѵ�.
	int ret = -1;	// ��¥ ����� ���� ����
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (vis[i][j] == 0) {
				cout << -1;
				return 0;
			}
			ret = max(ret, vis[i][j]);
		}
	}
	cout << ret - 1;
	return 0;
}