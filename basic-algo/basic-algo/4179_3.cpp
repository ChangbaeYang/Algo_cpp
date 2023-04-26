#include<iostream>
#include<queue>
using namespace std;

int r, c;
string arr[1002];
queue<pair<int, int>> Q1;
queue<pair<int, int>> Q2;
int dist1[1002][1002];
int dist2[1002][1002];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int main() {
	cin >> r >> c;
	for (int i = 0; i < r; i++) {
		fill(dist1[i], dist1[i] + c, -1);
		fill(dist2[i], dist2[i] + c, -1);
	}
	for (int i = 0; i < r; i++) {
		string temp = "";
		cin >> temp;
		arr[i] = temp;
		for (int j = 0; j < c; j++) {
			if (arr[i][j] == 'J') {
				Q1.push({ i, j });
				dist1[i][j] = 0;
			}
			else if (arr[i][j] == 'F') {
				Q2.push({ i, j });
				dist2[i][j] = 0;
			}
		}
	}
	// 불로 BFS를 먼저 돌려보자
	while (!Q2.empty()) {
		auto curr2 = Q2.front(); Q2.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr2.first + dx[i];
			int ny = curr2.second + dy[i];
			// 범위를 넘어서면 스킵
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
			// 이미 지난 점이거나 벽이면 스킵
			if (dist2[nx][ny] != -1 || arr[nx][ny] == '#') continue;
			Q2.push({ nx, ny });
			dist2[nx][ny] = dist2[curr2.first][curr2.second] + 1;
		} 
	}
	// 지훈이로 BFS를 돌려보자
	while (!Q1.empty()) {
		auto curr = Q1.front(); Q1.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			// 범위를 넘어서면 탈출 성공]
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
				cout << dist1[curr.first][curr.second] + 1;
				return 0;
			}
			// 이미 지난 점이거나 벽이면 스킵
			if (dist1[nx][ny] != -1 || arr[nx][ny] == '#') continue;
			// 다음 점에 불이 들렸고,
			// 다음 점의 불이 현재 점의 지훈이 + 1보다 작거나 같으면 스킵
			if (dist2[nx][ny] != -1 && dist2[nx][ny] <= dist1[curr.first][curr.second] + 1) continue;
			// 여기까지 오면 다음 점으로 이동가능 한 것
			Q1.push({ nx, ny });
			dist1[nx][ny] = dist1[curr.first][curr.second] + 1;
		}
	}
	// 여기까지 왔으면 탈출이 실패한 것이다.
	cout << "IMPOSSIBLE";
	return 0;
}