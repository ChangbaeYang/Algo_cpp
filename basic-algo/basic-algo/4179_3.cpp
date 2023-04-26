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
	// �ҷ� BFS�� ���� ��������
	while (!Q2.empty()) {
		auto curr2 = Q2.front(); Q2.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr2.first + dx[i];
			int ny = curr2.second + dy[i];
			// ������ �Ѿ�� ��ŵ
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) continue;
			// �̹� ���� ���̰ų� ���̸� ��ŵ
			if (dist2[nx][ny] != -1 || arr[nx][ny] == '#') continue;
			Q2.push({ nx, ny });
			dist2[nx][ny] = dist2[curr2.first][curr2.second] + 1;
		} 
	}
	// �����̷� BFS�� ��������
	while (!Q1.empty()) {
		auto curr = Q1.front(); Q1.pop();
		for (int i = 0; i < 4; i++) {
			int nx = curr.first + dx[i];
			int ny = curr.second + dy[i];
			// ������ �Ѿ�� Ż�� ����]
			if (nx < 0 || nx >= r || ny < 0 || ny >= c) {
				cout << dist1[curr.first][curr.second] + 1;
				return 0;
			}
			// �̹� ���� ���̰ų� ���̸� ��ŵ
			if (dist1[nx][ny] != -1 || arr[nx][ny] == '#') continue;
			// ���� ���� ���� ��Ȱ�,
			// ���� ���� ���� ���� ���� ������ + 1���� �۰ų� ������ ��ŵ
			if (dist2[nx][ny] != -1 && dist2[nx][ny] <= dist1[curr.first][curr.second] + 1) continue;
			// ������� ���� ���� ������ �̵����� �� ��
			Q1.push({ nx, ny });
			dist1[nx][ny] = dist1[curr.first][curr.second] + 1;
		}
	}
	// ������� ������ Ż���� ������ ���̴�.
	cout << "IMPOSSIBLE";
	return 0;
}