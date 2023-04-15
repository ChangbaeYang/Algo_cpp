#include<iostream>
#include<queue>
using namespace std;

int n, m;	// 2~100

int arr[100][100];
int dist[100][100];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void BFS() {
	queue<pair<int, int>> Q;
	dist[0][0] = 1;
	Q.push({ 0, 0 });
	while (Q.size()) {
		pair<int, int> curr = Q.front(); Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m)continue;
			if (dist[nx][ny] != 0 || arr[nx][ny] == 0)continue;
			dist[nx][ny] = dist[curr.first][curr.second] + 1;
			Q.push({ nx, ny });
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string temp;
		cin >> temp;
		for (int j = 0; j < m; j++) {
			// "1"은 string '1'은 char이다.
			if (temp[j] == '1') arr[i][j] = 1;
			else arr[i][j] = 0;
		}
	}
	
	// BFS 수행
	BFS();
	cout << dist[n - 1][m - 1] << "\n";
	return 0;
}