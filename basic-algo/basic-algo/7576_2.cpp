#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

int n, m;	// 2 ~ 1000
int days[1002][1002];
int	field[1002][1002];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };


int main() {
	cin >> m >> n;
	queue<pair<int, int>> Q;
	for (int i = 0; i < n; i++) fill(days[i], days[i] + m, -1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> field[i][j];
			if (field[i][j] == 1) {
				Q.push({ i, j });
				days[i][j] = 1;
			}
			else if (field[i][j] == -1) days[i][j] = 0;	// 갈 수 없는 길 표시
		}
	}
	while (!Q.empty()) {
		pair<int, int> curr = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (days[nx][ny] != -1) continue;
			days[nx][ny] = days[curr.first][curr.second] + 1;
			Q.push({ nx, ny });
		}
	}
	int max_day = -123;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (days[i][j] == -1) {
				cout << -1;
				return 0;
			}
			max_day = max(max_day, days[i][j]);
		}
	}
	cout << max_day - 1;
	return 0;
}