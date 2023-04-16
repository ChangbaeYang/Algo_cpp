#include<iostream>
#include<queue>
using namespace std;

int n, m;	// 2 ~ 100
int dat[102][102];
int dist[102][102];
string S;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void BFS(pair<int, int> start) {
	queue<pair<int, int>> Q;
	Q.push({ start.first, start.second });
	dist[start.first][start.second] = 1;
	while (!Q.empty()) {
		pair<int, int> curr = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (dat[nx][ny] == 0 || dist[nx][ny] != 0) continue;
			Q.push({ nx, ny });
			dist[nx][ny] = dist[curr.first][curr.second] + 1;
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> S;
		for (int j = 0; j < m; j++) {
			if (S[j] == '1') dat[i][j] = 1;
			else if (S[j] == '0') dat[i][j] = 0;
		}
	}
	BFS({ 0, 0 });
	cout << dist[n - 1][m - 1];
	return 0;
}