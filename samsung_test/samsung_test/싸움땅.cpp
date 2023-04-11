#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, k;	// n(2~20), m(1~30), k(1~500), �Ѱ��ݷ�(1~10��), s(1~100), x,y(1~n)
vector<int> grid[20][20];
// direction ��-��-��-��(0 1 2 3)
int player[30][5];	// x, y, d, s, ��
vector<int> visiting[20][20];	// �ش� �׸��忡 �����ϴ� �÷��̾� ����Ʈ
int ret[30];	// [0, 0, 0, 0, ..., 0]
// cf) �ʱ��� �� ���ڿ��� �÷��̾ ����

// �ش� ĭ�� �ְ��� ���� ã�� �Լ�
int find_best_gun(int gx, int gy) {
	int ret = 0;
	for (int i = 0; i < grid[gx][gy].size(); i++) {
		if (grid[gx][gy][i] > ret) ret = grid[gx][gy][i];
	}
	return ret;
}

// �÷��̾� ���� �� �̵�
void Go(int p_num) {
	// visiting���� �����ڸ��� p_num �����ϱ�
	int px = player[p_num][0];
	int py = player[p_num][1];
	// ** ���Ϳ��� Ư�� ���Ҹ� ã�� ����� ���� �����غ���! ** //
	int p_num_idx = find(visiting[px][py].begin(), visiting[px][py].end(), p_num) - visiting[px][py].begin();
	visiting[px][py].erase(visiting[px][py].begin() + p_num_idx);
	// �� �� �� ��
	// ��
	if (player[p_num][2] == 0) {
		// ���� �� �� �ִٸ� ���� ����, ���� �� �� ���ٸ� �Ʒ��� ����
		if (player[p_num][0] - 1 >= 0) {
			player[p_num][0]--;
		}
		else {
			// ���⵵ �ٲٱ�
			player[p_num][2] = 2;
			player[p_num][0]++;
		}
	}
	// ��
	else if (player[p_num][2] == 1) {
		// ���������� �� �� �ִٸ� ����������, �� �� ���ٸ� ��������
		if (player[p_num][1] + 1 < n) {
			player[p_num][1]++;
		}
		else {
			// ���⵵ �ٲٱ�
			player[p_num][2] = 3;
			player[p_num][1]--;
		}
	}
	// ��
	else if (player[p_num][2] == 2) {
		// �Ʒ��� �� �� �ִٸ� �Ʒ���, �� �� ���ٸ� ����
		if (player[p_num][0] + 1 < n) {
			player[p_num][0]++;
		}
		else {
			player[p_num][2] = 0;
			player[p_num][0]--;
		}
	}
	// ��
	else {
		// �������� �� �� �ִٸ� ��������, �� �� ���ٸ� ����������
		if (player[p_num][1] - 1 >= 0) {
			player[p_num][1]--;
		}
		else {
			player[p_num][2] = 1;
			player[p_num][1]++;
		}
	}
	// �̵��� �ڸ��� �ش� ������ �߰��س���
	int nx = player[p_num][0];
	int ny = player[p_num][1];
	visiting[nx][ny].push_back(p_num);
}

// �ο� ����
// �Է°��� �ο��� �Ͼ ������ ��ġ
// �̱� �÷��̾�-���÷��̾� player�� ��ȣ�� ��ȯ�Ѵ�.
pair<int, int> fight(int fx, int fy) {
	// ����� ������ ����
	pair<int, int> win_lose;

	// �ش���ǥ�� �ִ� ��� ������ ������ ��������
	int player1[6];	// �÷��̾� ��ȣ + ����
	int player2[6];

	vector<int> players = visiting[fx][fy];
	player1[0] = players[0];
	player2[0] = players[1];
	for (int player_num : players) {
		for (int i = 0; i < 5; i++) {
			player1[i + 1] = player[player1[0]][i];
			player2[i + 1] = player[player2[0]][i];
		}
	}

	// 1. �ɷ�ġ, ���� ���ݷ� ���ϱ�
	int player1_power = player1[4] + player1[5];
	int player2_power = player2[4] + player2[5];
	// 1-1. player1�� �Ŀ� ��ġ�� �� ���� ���
	if (player1_power > player2_power) {
		win_lose.first = player1[0];
		win_lose.second = player2[0];
		ret[player1[0]] = ret[player1[0]] + player1_power - player2_power;
		return win_lose;
	}
	// 1-2. �Ŀ� ��ġ�� ���ٸ� �ɷ�ġ�� ��
	else if (player1_power == player2_power) {
		// �ɷ�ġ ��
		if (player1[4] > player2[4]) {
			win_lose.first = player1[0];
			win_lose.second = player2[0];
			ret[player1[0]] = ret[player1[0]] + player1_power - player2_power;
			return win_lose;
		}
		else {
			win_lose.first = player2[0];
			win_lose.second = player1[0];
			ret[player2[0]] = ret[player2[0]] + player2_power - player1_power;
			return win_lose;
		}
	}
	// 1-3. player2�� �Ŀ� ��ġ�� �� ���� ���
	else {
		win_lose.first = player2[0];
		win_lose.second = player1[0];
		ret[player2[0]] = ret[player2[0]] + player2_power - player1_power;
		return win_lose;
	}
}

// �� ����� ������ ����
void loserGo(int loserNum) {
	// visiting���� �����ڸ��� loserNum ����
	int px = player[loserNum][0];
	int py = player[loserNum][1];
	// ** ���Ϳ��� Ư�� ���Ҹ� ã�� ����� ���� �����غ���! ** //
	int p_num_idx = find(visiting[px][py].begin(), visiting[px][py].end(), loserNum) - visiting[px][py].begin();
	visiting[px][py].erase(visiting[px][py].begin() + p_num_idx);

	while (true) {
		int lx = player[loserNum][0];
		int ly = player[loserNum][1];
		int ld = player[loserNum][2];
		int ls = player[loserNum][4];
		// ����
		if (ld == 0) {
			// �ش� �������� �������� ��, �÷��̾ �ְų� ���ڹ��� ���� ��� 90�� ȸ��
			if (lx - 1 < 0 || visiting[lx - 1][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// �ش� �������� ������ �� �ִٸ� ���� ���� ����
			else {
				// �ش� �������� �̵�
				player[loserNum][0]--;
				// ���� �ִٸ� ���� ���� �� ȹ��, ������ ���� ��������
				int best_gun_a = find_best_gun(player[loserNum][0], player[loserNum][1]);
				if (ls < best_gun_a) {
					int temp_loser_gun = ls;
					player[loserNum][4] = best_gun_a;
					// grid���� �ش� �� ����, ������� ������ ��ü
					int best_gun_a_idx = find(grid[lx - 1][ly].begin(), grid[lx - 1][ly].end(), best_gun_a) - grid[lx - 1][ly].begin();
					grid[lx - 1][ly].erase(grid[lx - 1][ly].begin() + best_gun_a_idx);
					grid[lx - 1][ly].push_back(temp_loser_gun);
				}
				break;
			}
		}
		// ����������
		else if (ld == 1) {
			// �ش� �������� �������� ��, �÷��̾ �ְų� ���ڹ��� ���� ��� 90�� ȸ��
			if (ly + 1 >= n || visiting[lx][ly + 1].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// �ش� �������� ������ �� �ִٸ� ���� ���� ����
			else {
				// �ش� �������� �̵�
				player[loserNum][1]++;
				// ���� �ִٸ� ���� ���� �� ȹ��, ������ ���� ��������
				int best_gun_b = find_best_gun(player[loserNum][0], player[loserNum][1]);
				if (ls < best_gun_b) {
					int temp_loser_gun = ls;
					player[loserNum][4] = best_gun_b;
					// grid���� �ش� �� ����, ������� ������ ��ü
					int best_gun_b_idx = find(grid[lx][ly + 1].begin(), grid[lx][ly + 1].end(), best_gun_b) - grid[lx][ly + 1].begin();
					grid[lx][ly + 1].erase(grid[lx][ly + 1].begin() + best_gun_b_idx);
					grid[lx][ly + 1].push_back(temp_loser_gun);
				}
				break;
			}
		}
		// �Ʒ���
		else if (ld == 2) {
			// �ش� �������� �������� ��, �÷��̾ �ְų� ���ڹ��� ���� ��� 90�� ȸ��
			if (lx + 1 >= n || visiting[lx + 1][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// �ش� �������� ������ �� �ִٸ� ���� ���� ����
			else {
				// �ش� �������� �̵�
				player[loserNum][0]++;
				// ���� �ִٸ� ���� ���� �� ȹ��, ������ ���� ��������
				int best_gun_c = find_best_gun(player[loserNum][0], player[loserNum][1]);
				if (ls < best_gun_c) {
					int temp_loser_gun = ls;
					player[loserNum][4] = best_gun_c;
					// grid���� �ش� �� ����, ������� ������ ��ü
					int best_gun_c_idx = find(grid[lx + 1][ly].begin(), grid[lx + 1][ly].end(), best_gun_c) - grid[lx + 1][ly].begin();
					grid[lx + 1][ly].erase(grid[lx + 1][ly].begin() + best_gun_c_idx);
					grid[lx + 1][ly].push_back(temp_loser_gun);
				}
				break;
			}
		}
		// ��������
		else {
			// �ش� �������� �������� ��, �÷��̾ �ְų� ���ڹ��� ���� ��� 90�� ȸ��
			if (ly - 1 < 0 || visiting[lx][ly - 1].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// �ش� �������� ������ �� �ִٸ� ���� ���� ����
			else {
				// �ش� �������� �̵�
				player[loserNum][1]--;
				// ���� �ִٸ� ���� ���� �� ȹ��, ������ ���� ��������
				int best_gun_d = find_best_gun(player[loserNum][0], player[loserNum][1]);
				if (ls < best_gun_d) {
					int temp_loser_gun = ls;
					player[loserNum][4] = best_gun_d;
					// grid���� �ش� �� ����, ������� ������ ��ü
					int best_gun_d_idx = find(grid[lx][ly - 1].begin(), grid[lx][ly - 1].end(), best_gun_d) - grid[lx][ly - 1].begin();
					grid[lx][ly - 1].erase(grid[lx][ly - 1].begin() + best_gun_d_idx);
					grid[lx][ly - 1].push_back(temp_loser_gun);
				}
				break;
			}
		}
	}
	// �̵��� �ڸ��� �ش� ������ �߰��س���
	int nx = player[loserNum][0];
	int ny = player[loserNum][1];
	visiting[nx][ny].push_back(loserNum);
}

void Simulate() {
	for (int i = 0; i < m; i++) {
		// 1-1. �÷��̾� �̵��ϱ�
		Go(i);
		int px = player[i][0];
		int py = player[i][1];

		// 2-1. �̵��� ���� �÷��̾ ���ٸ� ���� �ִ��� Ȯ��
		if (visiting[px][py].size() < 2) {
			// �̵��� �ڸ��� �� �� ���� �ִٸ�, ���� ȹ��
			int best_gun = find_best_gun(px, py);
			if (best_gun > player[i][4]) {
				int temp = player[i][4];
				player[i][4] = best_gun;
				// �ش� ĭ���� ���� �� ���� ���ְ�, player�� ���� ���� �߰��ϱ�
				int best_gun_idx = find(grid[px][py].begin(), grid[px][py].end(), best_gun) - grid[px][py].begin();
				grid[px][py].erase(grid[px][py].begin() + best_gun_idx);
				grid[px][py].push_back(temp);
			}
		}

		// 2-2-1. �̵��� ���� �÷��̾ �ִ� ��� �ο�
		else {
			pair<int, int> winner_loser = fight(px, py);
			int winner = winner_loser.first;
			int loser = winner_loser.second;
			// 2-2-2. �� �÷��̾�� ���� ��������
			int gun = player[loser][4];
			player[loser][4] = 0;
			grid[px][py].push_back(gun);	// �������� �� �߰�
			// �� �÷��̾�� ���� �̵�
			loserGo(loser);
			// 2-2-3. �̱� �÷��̾�� ���� ������ ������ ��ü
			int best_gun_2 = find_best_gun(px, py);
			if (best_gun_2 > player[winner][4]) {
				int temp_gun2 = player[winner][4];
				player[winner][4] = best_gun_2;
				// ��ü ����.
				int best_gun_2_idx = find(grid[px][py].begin(), grid[px][py].end(), best_gun_2) - grid[px][py].begin();
				grid[px][py].erase(grid[px][py].begin() + best_gun_2_idx);
				grid[px][py].push_back(temp_gun2);
			}
		}
	}
}

int main() {
	// �Է�
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int temp;
			cin >> temp;
			grid[i][j].push_back(temp);
		}
	}

	for (int i = 0; i < m; i++) {
		int x, y, d, s;	// s: �ʱ�ɷ�
		cin >> x >> y >> d >> s;
		player[i][0] = x - 1;
		player[i][1] = y - 1;
		player[i][2] = d;
		player[i][3] = s;
		visiting[x - 1][y - 1].push_back(i);
	}
	
	// ���� ����
	for (int i = 0; i < k; i++) {
		Simulate();
	}

	// ���
	for (int i = 0; i < m; i++) {
		cout << ret[i] << " ";
	}

	return 0;
}