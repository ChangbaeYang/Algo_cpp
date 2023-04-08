#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, k;	// n(2~20), m(1~30), k(1~500), �Ѱ��ݷ�(1~10��), s(1~100), x,y(1~n)
int grid[20][20];
// direction ��-��-��-��(0 1 2 3)
int player[30][5];	// x, y, d, s, ��
vector<int> visiting[20][20];	// �ش� �׸��忡 �����ϴ� �÷��̾� ����Ʈ
int ret[30];	// [0, 0, 0, 0, ..., 0]
// cf) �ʱ��� �� ���ڿ��� �÷��̾ ����

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
		else player[p_num][0]++;
	}
	// ��
	else if (player[p_num][2] == 1) {
		// ���������� �� �� �ִٸ� ����������, �� �� ���ٸ� ��������
		if (player[p_num][1] + 1 < n) {
			player[p_num][1]++;
		}
		else player[p_num][1]--;
	}
	// ��
	else if (player[p_num][2] == 2) {
		// �Ʒ��� �� �� �ִٸ� �Ʒ���, �� �� ���ٸ� ����
		if (player[p_num][0] + 1 < n) {
			player[p_num][0]++;
		}
		else player[p_num][0]--;
	}
	// ��
	else {
		// �������� �� �� �ִٸ� ��������, �� �� ���ٸ� ����������
		if (player[p_num][1] - 1 >= 0) {
			player[p_num][1]--;
		}
		else player[p_num][1]++;
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
			player2[i + 1] = player[player1[0]][i];
		}
	}

	// 1. �ɷ�ġ, ���� ���ݷ� ���ϱ�
	int player1_power = player1[4] + player1[5];
	int player2_power = player2[4] + player2[5];
	// 1-1. player1�� �Ŀ� ��ġ�� �� ���� ���
	if (player1_power > player2_power) {
		win_lose.first = player1[0];
		win_lose.second = player2[0];
		ret[player1[0]]++;
		return win_lose;
	}
	// 1-2. �Ŀ� ��ġ�� ���ٸ� �ɷ�ġ�� ��
	else if (player1_power == player2_power) {
		// �ɷ�ġ ��
		if (player1[4] > player2[4]) {
			win_lose.first = player1[0];
			win_lose.second = player2[0];
			ret[player1[0]]++;
			return win_lose;
		}
		else {
			win_lose.first = player2[0];
			win_lose.second = player1[0];
			ret[player2[0]]++;
			return win_lose;
		}
	}
	// 1-3. player2�� �Ŀ� ��ġ�� �� ���� ���
	else {
		win_lose.first = player2[0];
		win_lose.second = player1[0];
		ret[player2[0]]++;
		return win_lose;
	}
}

// �� ����� ������ ����
void loserGo(int loserNum) {
	// �� �÷��̾� �����̵�
	// ���� �ٸ� �÷��̾ �ְų� ���ڹ��� ���� ��� ������ 
	// 90�� ȸ���Ͽ� �� ĭ�� ���̴� ���� �̵�
	// ���� ���̸� ���� ���� �� ȹ��, ������ ���� �������´�.
	int lx = player[loserNum][0];
	int ly = player[loserNum][1];
	int ld = player[loserNum][2];
	int ls = player[loserNum][4];
	while (true) {
		// ����
		if (ld == 0) {
			// �ش� �������� �������� ��, �÷��̾ �ְų� ���ڹ��� ���� ��� 90�� ȸ��
			if (lx - 1 < 0 || visiting[lx][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// �ش� �������� ������ �� �ִٸ� ���� ���� ����
			else {
				// �ش� �������� �̵�
				lx--;
				// ���� �ִٸ� ���� ���� �� ȹ��, ������ ���� ��������
				if (ls < grid[lx][ly]) {
					int temp_loser_gun = ls;
					int temp_grid_gun = grid[lx][ly];
					ls = temp_grid_gun;
					grid[lx][ly] = temp_loser_gun;
				}
				break;
			}
		}
		// ����������
		else if (ld == 1) {
			// �ش� �������� �������� ��, �÷��̾ �ְų� ���ڹ��� ���� ��� 90�� ȸ��
			if (ly + 1 >= n || visiting[lx][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// �ش� �������� ������ �� �ִٸ� ���� ���� ����
			else {
				// �ش� �������� �̵�
				ly++;
				// ���� �ִٸ� ���� ���� �� ȹ��, ������ ���� ��������
				if (ls < grid[lx][ly]) {
					int temp_loser_gun = ls;
					int temp_grid_gun = grid[lx][ly];
					ls = temp_grid_gun;
					grid[lx][ly] = temp_loser_gun;
				}
				break;
			}
		}
		// �Ʒ���
		else if (ld == 2) {
			// �ش� �������� �������� ��, �÷��̾ �ְų� ���ڹ��� ���� ��� 90�� ȸ��
			if (lx + 1 >= n || visiting[lx][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// �ش� �������� ������ �� �ִٸ� ���� ���� ����
			else {
				// �ش� �������� �̵�
				lx++;
				// ���� �ִٸ� ���� ���� �� ȹ��, ������ ���� ��������
				if (ls < grid[lx][ly]) {
					int temp_loser_gun = ls;
					int temp_grid_gun = grid[lx][ly];
					ls = temp_grid_gun;
					grid[lx][ly] = temp_loser_gun;
				}
				break;
			}
		}
		// ��������
		else {
			// �ش� �������� �������� ��, �÷��̾ �ְų� ���ڹ��� ���� ��� 90�� ȸ��
			if (ly - 1 < 0 || visiting[lx][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// �ش� �������� ������ �� �ִٸ� ���� ���� ����
			else {
				// �ش� �������� �̵�
				ly--;
				// ���� �ִٸ� ���� ���� �� ȹ��, ������ ���� ��������
				if (ls < grid[lx][ly]) {
					int temp_loser_gun = ls;
					int temp_grid_gun = grid[lx][ly];
					ls = temp_grid_gun;
					grid[lx][ly] = temp_loser_gun;
				}
				break;
			}
		}
	}
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
			if (grid[px][py] > player[i][4]) {
				int temp = grid[px][py];
				int temp2 = player[i][4];
				player[i][4] = temp;
				grid[px][py] = temp;
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
			grid[px][py] = gun;
			// �� �÷��̾�� ���� �̵�
			loserGo(loser);
			// 2-2-3. �̱� �÷��̾�� ���� ������ ������ ��ü
			if (grid[px][py] > player[winner][4]) {
				int temp_gun = grid[px][py];
				int temp_gun2 = player[winner][4];
				player[winner][4] = temp_gun;
				grid[px][py] = temp_gun2;
			}
		}
	}
}

int main() {
	// �Է�
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}
	
	// visiting -> -1 �̸� �÷��̾� ����
	// -1�� �ƴϸ� �ش� ĭ�� �÷��̾� ��ȣ�� ��(0���� ����)

	for (int i = 0; i < m; i++) {
		int x, y, d, s;	// s: �ʱ�ɷ�
		cin >> x >> y >> d >> s;
		player[i][0] = x;
		player[i][1] = y;
		player[i][2] = d;
		player[i][3] = s;
		visiting[x][y].push_back(i);
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