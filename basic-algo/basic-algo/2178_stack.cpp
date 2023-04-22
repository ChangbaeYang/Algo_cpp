#include<iostream>
#include<stack>

using namespace std;

int n, m;
int arr[102][102];
int dist[102][102];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		string S;
		cin >> S;
		for (int j = 0; j < m; j++) {
			if (S[j] == '1') {
				arr[i][j] = 1;
			}
			else if (S[j] == '0') {
				arr[i][j] = 0;
			}
		}
	}
	
	stack<pair<int, int>> St;
	St.push({ 0, 0 });
	dist[0][0] = 1;
	while (!St.empty()) {
		auto curr = St.top(); St.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
			if (arr[nx][ny] == 0 || dist[nx][ny] != 0) continue;
			dist[nx][ny] = dist[curr.first][curr.second] + 1;
			St.push({ nx, ny });
		}
	}
	cout << dist[n - 1][m - 1];
}