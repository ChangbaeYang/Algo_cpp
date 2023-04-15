#include<iostream>
#include<queue>
using namespace std;
// �Ʒ��� ���� Ǯ�� O(N^2*M^2)�� �Ǿ� �ð� �ʰ�

int n, m;	// 2 ~ 1000
int arr[1000][1000];
int vis[1000][1000];
int ret;	// ��� �� �ʹ� ��¥ üũ
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

// �ִ� ���� ã��
void find_max() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (vis[i][j] == 0) {
				ret = -1;
				return;
			}
			if (ret < vis[i][j]) ret = vis[i][j];
		}
	}
}

void BFS(pair<int, int> start) {
	int x = start.first;
	int y = start.second;
	queue<pair<int, int>> Q;
	vis[x][y] = 1;
	Q.push({ x, y });
	while (Q.size()) {
		pair<int, int> curr = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
			if (vis[nx][ny] == -1)continue;
			// �鸮�� �ʾҴ� ���̸� �׳� ����
			if (vis[nx][ny] == 0) {
				vis[nx][ny] = vis[curr.first][curr.second] + 1;
				Q.push({ nx, ny });
			}
			// ��ȴ� ���� ���
			else {
				if (vis[nx][ny] > vis[curr.first][curr.second] + 1) {
					vis[nx][ny] = vis[curr.first][curr.second] + 1;
					Q.push({ nx, ny });
				}
			}
		}
	}
}

int main() {
	cin >> m >> n;
	ios::sync_with_stdio(0);
	cin.tie(0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == -1) {
				vis[i][j] = -1;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == 1) BFS({i, j});
		}
	}
	// ret�� �ٷ� ���� ���Ž�Ŵ
	find_max();
	if (ret == -1) cout << -1 << "\n";
	else cout << ret - 1 << "\n";
	return 0;
}
