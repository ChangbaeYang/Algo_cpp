#include<iostream>
#include<queue>
using namespace std;

int n;	// 1 ~ 500
int m;	// 1 ~ 500
int arr[500][500];
bool vis[500][500];
int ret_count;
int ret_max = 0;
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int BFS(pair<int, int> start) {
	int temp_ret = 0;
	int x = start.first;
	int y = start.second;
	vis[x][y] = true;
	queue<pair<int, int>> Q;
	Q.push({ x, y });
	temp_ret++;
	while (Q.size()) {
		pair<int, int> curr = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
			if (vis[nx][ny] || arr[nx][ny] != 1)continue;
			// temp_ret Ãß°¡
			vis[nx][ny] = true;
			Q.push({ nx, ny });
			temp_ret++;
		}
	}
	return temp_ret;
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
			if (vis[i][j] == false && arr[i][j] == 1) {
				ret_count++;
				int temp = BFS({ i, j });
				if (temp > ret_max) {
					ret_max = temp;
				}
			}
		}
	}
	cout << ret_count << "\n";
	cout << ret_max << "\n";
	return 0;
}