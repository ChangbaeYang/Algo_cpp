#include<iostream>
#include<queue>
using namespace std;

int n, m;	// 1 ~ 500
int dat[502][502];
int vis[502][502];
int pic_count;	// 그림의 갯수
int pic_max;	// 가장 큰 그림의 크기
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void BFS(pair<int, int> start) {
	int temp_size = 1;	// 시작점의 크기
	queue<pair<int, int>> Q;
	vis[start.first][start.second] = 1;
	Q.push({ start.first, start.second });
	while (!Q.empty()) {
		pair<int, int> curr = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
			if (vis[nx][ny] == 1 || dat[nx][ny] == 0)continue;
			Q.push({ nx, ny });
			vis[nx][ny] = 1;
			temp_size++;
		}
	}
	pic_max = max(pic_max, temp_size);
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> dat[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (dat[i][j] == 1 && vis[i][j] == 0) {
				pic_count++;
				BFS({ i, j });
			}
	cout << pic_count << "\n" << pic_max;
	return 0;
}