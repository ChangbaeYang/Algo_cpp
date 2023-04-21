#include<iostream>
#include<queue>
using namespace std;

int n, m, p_count;
int arr[502][502];
int vis[502][502];
int psize = 0;	// psize의 최대값을 구해야 한다. 없는 경우 0
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };


void BFS(pair<int, int> start) {
	int temp = 1;
	queue<pair<int, int>> Q;
	Q.push(start);
	vis[start.first][start.second] = 1;
	while (!Q.empty()) {
		auto curr = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
			if (vis[nx][ny] != 0 || arr[nx][ny] == 0)continue;
			vis[nx][ny] = 1;
			temp++;
			Q.push({ nx, ny });
		}
	}
	psize = max(psize, temp);
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == 1 && vis[i][j] == 0) {
				p_count++;
				BFS({ i, j });
			}
		}
	}
	cout << p_count << "\n" << psize;
	return 0;
}