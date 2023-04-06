#include <iostream>
#include <tuple>
#include <queue>
#include <climits>

using namespace std;

int n, m;
int grid[15][15];
int curr_t = 0;
pair<int, int> cvs_list[30];	// ������ ��ġ
pair<int, int> people[30];		// ����� ��ġ - �ε����� �������� ��Ī��Ŵ
int dy[4] = { -1, 0, 0, 1 };
int dx[4] = { 0, -1, 1, 0 };

// bfs���� ����ϴ� ������
int step[15][15];			// �ִܰŸ� ��� ���
int visited[15][15];		// �湮 ���� ǥ��

// start_pos�� �������� BFS�� ����
// ���������κ����� �ִܰŸ� ����� step�迭�� ��ϵ˴ϴ�.
void BFS(pair<int, int> start_pos) {
	// visited, step�� �ʱ�ȭ
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
			step[i][j] = 0;
		}
	}

	// �ʱ� ��ġ�� queue�� ����ֱ�
	queue<pair<int, int>> q;
	int sy = start_pos.first, sx = start_pos.second;
	q.push(start_pos);
	visited[sy][sx] = true;
	step[sy][sx] = 0;

	// BFS�� ����
	while (!q.empty()) {
		// ���� �տ� ���Ҹ� �����
		pair<int, int> curr_pos = q.front();
		q.pop();

		// ������ ĭ�� ���� ���� �湮���� ���� ĭ�� ť�� �ִ´�.
		int y = curr_pos.first, x = curr_pos.second;
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i], nx = x + dx[i];
			// �� �� �ִ� ��쿡�� ����
			if (ny >= 0 && ny < n && nx >= 0 && nx < n && !visited[ny][nx] && grid[ny][nx] != 2) {
				visited[ny][nx] = true;
				step[ny][nx] = step[y][x] + 1;
				q.push(make_pair(ny, nx));
			}
		}
	}
}

void Simulate() {
	// Step 1. ���ڿ� �ִ� ����鿡 ���Ͽ� ������ ������ ���� 1ĭ ������
	for (int i = 0; i < m; i++) {
		// ���ڿ� �ִ� ����� ���ϱ� ���ؼ�, �ۿ��ִ»���� �������� �ִ� ����� ����
		if (people[i] == make_pair(-1, -1) || people[i] == cvs_list[i])
			continue;

		BFS(cvs_list[i]); // ���������� �����ϴ� BFS�� ������

		int py, px;
		tie(py, px) = people[i];
		int min_dist = INT_MAX;
		int min_y = -1;
		int min_x = -1;
		for (int j = 0; j < 4; j++) {
			int ny = py + dy[j];
			int nx = px + dx[j];
			if (ny >= 0 && ny < n && nx >= 0 && nx < n && visited[ny][nx] && min_dist > step[ny][nx]) {
				min_dist = step[ny][nx];
				min_y = ny;
				min_x = nx;
			}
		}
		// �켱������ ���� ���� ĭ���� �� ĭ �����̱�
		people[i] = make_pair(min_y, min_x);
		

	}
	
	// Step 2. �������� �����Ѵٸ� �ش� �������� ���߰�, �ٸ� ����� �� ������ ��������
	for (int i = 0; i < m; i++) {
		if (people[i] == cvs_list[i]) {
			int py, px;
			tie(py, px) = people[i];
			grid[py][px] = 2;
		}
	}

	// Step 3. ���� �ð� curr_t�� ���ؼ� curr_t <= m�� �����Ҷ���
	if (curr_t > m)
		return;
	// Step 3-1. ���������� BFS ����
	BFS(cvs_list[curr_t - 1]);

	// Step 3-2. ���������� ���� ����� ���̽� ķ���� ����
	//			 i, j�� �����ϴ� ������ ���� -> ���� ����� ��, �� �켱����
	int min_dist = INT_MAX;
	int min_y = -1;
	int min_x = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// �湮 ������ ���̽� ķ�� ��
			// ���尡��� ķ�� -> BFS���� ��Ȱ�, baseķ��(1)�̸�, min_dist����
			if (visited[i][j] && grid[i][j] == 1 && min_dist > step[i][j]) {
				min_dist = step[i][j];
				min_y = i, min_x = j;
			}
		}
	}
	// �켱������ ���� ���� ���̽�ķ���� �̵�
	people[curr_t - 1] = make_pair(min_y, min_x);
	grid[min_y][min_x] = 2;
}

bool End() {
	for (int i = 0; i < m; i++) {
		if (people[i] != cvs_list[i])
			return false;
	}
	return true;
}

int main() {
	// �Է�
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}
	
	for (int i = 0; i < m; i++) {
		int y, x;
		cin >> y >> x;
		cvs_list[i] = make_pair(y - 1, x - 1);
	}

	// �ʱ⿡�� ��� ����� ���� �ۿ� ����
	for (int i = 0; i < m; i++) {
		people[i] = make_pair(-1, -1);
	}

	// 1�п� �ѹ��� �ùķ��̼��� �����մϴ�.
	while (true) {
		curr_t++;
		Simulate();
		// ���� �̵��� �������� �����մϴ�.
		if (End()) break;
	}

	cout << curr_t;
	return 0;
}