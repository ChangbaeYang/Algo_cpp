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
	queue<pair<int, int>> Q;	// 토마토의 위치를 담을 큐
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 1) {
				vis[i][j] = 1;
				Q.push({ i, j });
			}
			else if (arr[i][j] == -1) {
				vis[i][j] = -1;	// 벽은 -1 처리를 해준다.
			}
		}
	}
	
	// BFS로직을 수행해보자. -> 이미 앞서서 아래의 두 로직수행했다.
	// 1. 익은 토마토 시작점 점을 Q에 집어넣기
	// 2. 익은 토마토의 좌표 방문처리
	while (!Q.empty()) {
		auto curr = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (vis[nx][ny] != 0) continue;	// vis[nx][ny]가 0이 아니면, 방문한 점이거나, 벽이다.
			vis[nx][ny] = vis[curr.first][curr.second] + 1;
			Q.push({ nx, ny });
		}
	}
	
	// 안익은 토마토가 있는지 확인한다.
	// 안익은 토마토가 있으면 -1출력한다.(0이 있는 경우)
	// 안익은 토마토가 없으면 최대값 -1을 출력한다.
	int ret = -1;	// 날짜 결과값 담을 변수
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