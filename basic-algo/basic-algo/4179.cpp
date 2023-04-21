#include<iostream>
#include<queue>
using namespace std;

int r, c;
string board[1002];
int dist1[1002][1002];	// 불의 전파 시간
int dist2[1002][1002];	// 지훈이의 이동 시간
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> r >> c;
	// dist1, dist2를 -1로 채우기
	for (int i = 0; i < r; i++) {
		fill(dist1[i], dist1[i] + c, -1);
		fill(dist2[i], dist2[i] + c, -1);
	}
	for (int i = 0; i < r; i++)
		cin >> board[i];
	
	// Q1, Q2 채우기
	queue<pair<int, int>> Q1;
	queue<pair<int, int>> Q2;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			// 불 위치는 0으로 시작
			if (board[i][j] == 'F') {
				Q1.push({ i, j });
				dist1[i][j] = 0;
			}
			// 지훈 위치는 0으로 시작
			if (board[i][j] == 'J') {
				Q2.push({ i, j });
				dist2[i][j] = 0;
			}
		}
	}
	//불에 대한 BFS
	while (!Q1.empty()) {
		auto curr = Q1.front(); Q1.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			// 가장자리
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
			// 들린점과 벽은 무시한다.
			if (dist1[nx][ny] >= 0 || board[nx][ny] == '#')continue;
			dist1[nx][ny] = dist1[curr.first][curr.second] + 1;
			Q1.push({ nx, ny });
		}
	}
	// 지훈에 대한 BFS
	while (!Q2.empty()) {
		auto curr = Q2.front(); Q2.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			// 범위를 벗어난 것 -> 탈출 성공을 의미
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
				cout << dist2[curr.first][curr.second] + 1;
				return 0;
			}
			if (dist2[nx][ny] >= 0 || board[nx][ny] == '#')continue;
			// 불이 이미 점령한 곳이면 갈 수 없다.
			if (dist1[nx][ny] != -1 && dist1[nx][ny] <= dist2[curr.first][curr.second] + 1) continue;
			dist2[nx][ny] = dist2[curr.first][curr.second] + 1;
			Q2.push({ nx, ny });
		}
	}
	cout << "IMPOSSIBLE";
}