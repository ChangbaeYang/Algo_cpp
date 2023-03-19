#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

vector<vector<int>> fish;	// ����� ��ǥ�� ���� ����({����� ũ��, y��ǥ, x��ǥ})
int n;				// ������ ũ��
int a[21][21];		// ����� �ڸ��� ���� �迭
int baby_size = 2;	// �Ʊ����� ũ��
int baby_ex = 0;	// �Ʊ��� ���� ����ġ
pair<int, int> baby_idx;	// �Ʊ� ����� ��ǥ
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int visited[21][21];
int ret = 0;

// �Ʊ� �� ������ �������� ���� �ִ� �Ÿ��� ���Ѵ�.(�Ÿ��� �ð����� ������)
void bfs(pair<int, int> baby_idx, pair<int, int> can_eat_idx, int min_dist) {
	memset(visited, 0, sizeof(visited));
	queue<pair<int, int>> q;
	q.push(baby_idx);
	while (q.size()) {
		int y = q.front().first;
		int x = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (ny < 0 || ny >= n || nx < 0 || nx >= n || a[ny][nx] > baby_size || visited[ny][nx] != 0)continue;
			visited[ny][nx] = visited[y][x] + 1;
			// �������� �����ߴٸ�
			if (ny == can_eat_idx.first && nx == can_eat_idx.second) {
				min_dist = min(visited[ny][nx], min_dist);
			}
		}
	}
}

int main() {
	cin >> n;
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
			// �Ʊ� ��� ��ǥ ����
			if (a[i][j] == 9) {
				baby_idx.first = i;
				baby_idx.second = j;
				a[i][j] = 0;
			}
			// �ٸ� ����� ��ǥ ����
			else if (a[i][j] != 0 && a[i][j] != 9) {
				fish.push_back({ a[i][j], i, j });
			}
		}
	}
	sort(fish.begin(), fish.end()); // ����� ũ�⺰�� ���� �ȴ�.-> ������ �Ʒ��δ� �̹� ���ĵǾ� ����
	while (true) {

		// 0. ���� �� �ִ� ������� ���� ����. + ������� ��ǥ��
		int can_eat = 0;
		vector<vector<int>> can_eat_idx;
		for (int i = 0; i < fish.size(); i++) {
			if (fish[i][0] < baby_size) {
				can_eat++;
				can_eat_idx.push_back({ i, fish[i][1], fish[i][2] });
			}
		}

		// 1. ���� �� �ִ� ����Ⱑ ���� ���
		if (can_eat == 0) break;

		// 2. ���� �� �ִ� ����Ⱑ �� ������ ��� -> �� ����⸦ ����������.
		else if (can_eat == 1) {
			// �ش� �������� �� �� �ִ����� �ľ��Ѵ�.(�Լ�)
			int min_dist = 999; // ���� �Ǵ� �Ÿ�
			pair<int, int> cash_can_eat = { can_eat_idx[0][1], can_eat_idx[0][2] };
			bfs(baby_idx, cash_can_eat, min_dist);
			if (min_dist == 999)break; // �ش� �������� �� �� ���ٸ�

			ret += min_dist;
			// �Ʊ� ��� ex�þ - ex�� ũ�⸸ŭ �Ǹ�, ũ�� �þ, ex�ʱ�ȭ
			baby_ex++;
			if (baby_ex == baby_size) {
				baby_ex = 0;
				baby_size++;
			}
			// �Ʊ� ��� ��ġ �ٲ� -> ���� ��ġ��
			baby_idx.first = cash_can_eat.first;
			baby_idx.second = cash_can_eat.second;
			// ���� ����� ��ǥ 0���� �ٲٱ�
			a[baby_idx.first][baby_idx.second] = 0;
			fish.erase(fish.begin());	// �� �տ� �ִ� ���� ���� �� �ִ� ����⿴��
		}

		// 3. ���� �� �ִ� ����Ⱑ ���������� ��� -> ���� ����� ����� ����������.
		else {
			// ���� ����� �Ÿ��� �ش� ��ǥ�� ã�ƾ���
			int min_dist2 = 999;
			pair<int, int> where_to_eat;
			int where_to_eat_idx;
			for (int i = 0; i < can_eat_idx.size(); i++) {
				int temp = min_dist2;
				pair<int, int> cash_can_eat2 = { can_eat_idx[i][1], can_eat_idx[i][2] };
				bfs(baby_idx, cash_can_eat2, min_dist2);
				// min_dist �� ���� ��ٸ�, �̵��� ����� ��ǥ�� �ٲ��.
				if (temp != min_dist2) {
					where_to_eat = cash_can_eat2;
					where_to_eat_idx = can_eat_idx[i][0];	// fish������ �ε���
				}
			}
			// �� �� �ִ� ���� ���� ��� break
			if (min_dist2 == 999)break;
			// �� �� �ִٸ� ���� �̵�
			ret += min_dist2;
			// �Ʊ� ��� ex�þ - ex�� ũ�⸸ŭ �Ǹ�, ũ�� �þ. ex�ʱ�ȭ
			baby_ex++;
			if (baby_ex == baby_size) {
				baby_ex = 0;
				baby_size++;
			}
			// �Ʊ� ��� ��ġ �ٲ� -> ���� ��ġ��
			baby_idx.first = where_to_eat.first;
			baby_idx.second = where_to_eat.second;
			// ���� ����� ��ǥ 0���� �ٲٱ�
			a[baby_idx.first][baby_idx.second] = 0;
			// fish���� ����������Ѵ�.
			fish.erase(fish.begin() + where_to_eat_idx);
		}
	}
	cout << ret << "\n";
	return 0;
}