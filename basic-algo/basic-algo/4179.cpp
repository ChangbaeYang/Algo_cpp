#include<iostream>
#include<queue>
using namespace std;

int r, c;
string board[1002];
int dist1[1002][1002];	// ���� ���� �ð�
int dist2[1002][1002];	// �������� �̵� �ð�
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> r >> c;
	// dist1, dist2�� -1�� ä���
	for (int i = 0; i < r; i++) {
		fill(dist1[i], dist1[i] + c, -1);
		fill(dist2[i], dist2[i] + c, -1);
	}
	for (int i = 0; i < r; i++)
		cin >> board[i];
	
	// Q1, Q2 ä���
	queue<pair<int, int>> Q1;
	queue<pair<int, int>> Q2;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			// �� ��ġ�� 0���� ����
			if (board[i][j] == 'F') {
				Q1.push({ i, j });
				dist1[i][j] = 0;
			}
			// ���� ��ġ�� 0���� ����
			if (board[i][j] == 'J') {
				Q2.push({ i, j });
				dist2[i][j] = 0;
			}
		}
	}
	//�ҿ� ���� BFS
	while (!Q1.empty()) {
		auto curr = Q1.front(); Q1.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			// �����ڸ�
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
			// �鸰���� ���� �����Ѵ�.
			if (dist1[nx][ny] >= 0 || board[nx][ny] == '#')continue;
			dist1[nx][ny] = dist1[curr.first][curr.second] + 1;
			Q1.push({ nx, ny });
		}
	}
	// ���ƿ� ���� BFS
	while (!Q2.empty()) {
		auto curr = Q2.front(); Q2.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			// ������ ��� �� -> Ż�� ������ �ǹ�
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
				cout << dist2[curr.first][curr.second] + 1;
				return 0;
			}
			if (dist2[nx][ny] >= 0 || board[nx][ny] == '#')continue;
			// ���� �̹� ������ ���̸� �� �� ����.
			if (dist1[nx][ny] != -1 && dist1[nx][ny] <= dist2[curr.first][curr.second] + 1) continue;
			dist2[nx][ny] = dist2[curr.first][curr.second] + 1;
			Q2.push({ nx, ny });
		}
	}
	cout << "IMPOSSIBLE";
}