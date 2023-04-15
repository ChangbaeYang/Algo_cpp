#include<iostream>
#include<queue>
using namespace std;

int n, m;	// 2 ~ 1000
int tomato[1000][1000];
int dist[1000][1000];	// 0: 시작점이거나 토마토가 익은 곳. -1: 토마토가 안익은 곳
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int main() {
	cin >> m >> n;
	queue<pair<int, int>> Q;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> tomato[i][j];
			if (tomato[i][j] == 0) dist[i][j] = -1;
			else if (tomato[i][j] == 1) Q.push({ i, j });
		}
	}
	while (Q.size()) {
		auto curr = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
			if (dist[nx][ny] >= 0) continue;
			dist[nx][ny] = dist[curr.first][curr.second] + 1;
			Q.push({ nx, ny });
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (dist[i][j] == -1) {
				cout << -1;
				return 0;
			}
			ans = max(ans, dist[i][j]);
		}
	}
	cout << ans;
	return 0;
}