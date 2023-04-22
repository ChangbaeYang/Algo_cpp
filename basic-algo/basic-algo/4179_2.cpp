#include<iostream>
#include<queue>
#define MX_I 987654321
using namespace std;

int r, c;
string arr[1002];
int dist_j[1002][1002];
int dist_f[1002][1002];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
int ret = MX_I;	// 지훈이의 탈출 최소 시간

int main() {
	cin >> r >> c;
	string S;
	queue<pair<int, int>> Qj;
	queue<pair<int, int>> Qf;
	for (int i = 0; i < r; i++) {
		fill(dist_j[i], dist_j[i] + c, -1);
		fill(dist_f[i], dist_f[i] + c, -1);
	}
	for (int i = 0; i < r; i++) {
		cin >> S;
		arr[i] = S;
		for (int j = 0; j < c; j++) {
			if (S[j] == 'J') {
				Qj.push({ i, j });
				dist_j[i][j] = 0;
			}
			else if (S[j] == 'F') {
				Qf.push({ i, j });
				dist_f[i][j] = 0;	// 0이상일 경우 visited이다.
			}
		}
	}
	
	// 불의 영역으로 먼저 bfs를 돌린다.
	while (!Qf.empty()) {
		auto curr = Qf.front(); Qf.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
			if (arr[nx][ny] == '#' || dist_f[nx][ny] != -1) continue;
			dist_f[nx][ny] = dist_f[curr.first][curr.second] + 1;
			Qf.push({ nx, ny });
		}
	}

	// 이제 지훈이로 bfs를 돌린다.
	while (!Qj.empty()) {
		auto curr = Qj.front(); Qj.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			// 탈출할 수 있는 순간	-> queue가 거리순으로 채워지기 때문에 이 지점 들리면 함수 종료
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
				cout << dist_j[curr.first][curr.second] + 1;
				return 0;
			}
			if (arr[nx][ny] == '#' || dist_j[nx][ny] != -1) continue;
			// 다음 점에서 불이 먼저, 혹은 동시에 점거 했어도 이동할 수 없다.
			// dist_f[nx][ny]를 붙여준 것은 불이 점령한 지점만 체크해야하므로.
			if (dist_f[nx][ny] != -1 && dist_f[nx][ny] <= dist_j[curr.first][curr.second] + 1) continue;
			dist_j[nx][ny] = dist_j[curr.first][curr.second] + 1;
			Qj.push({ nx, ny });
		}
	}
	cout << "IMPOSSIBLE";
	return 0;
}