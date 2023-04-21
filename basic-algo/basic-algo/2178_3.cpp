#include<iostream>
#include<queue>
using namespace std;

int n, m;
int arr[102][102];
int vis[102][102];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
string S;

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> S;
		for (int j = 0; j < m; j++) {
			if (S[j] == '1')arr[i][j] = 1;
			else if (S[j] == '0')arr[i][j] = 0;
		}
	}
	// BFS¼öÇà
	queue<pair<int, int>> q;
	q.push({ 0, 0 });
	vis[0][0] = 1;
	while (!q.empty()) {
		auto curr = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (vis[nx][ny] != 0 || arr[nx][ny] == 0) continue;
			q.push({ nx, ny });
			vis[nx][ny] = vis[curr.first][curr.second] + 1;
		}
	}
	cout << vis[n - 1][m - 1];
	return 0;
}