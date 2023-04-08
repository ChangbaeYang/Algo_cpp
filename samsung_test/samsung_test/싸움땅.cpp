#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, k;	// n(2~20), m(1~30), k(1~500), 총공격력(1~10만), s(1~100), x,y(1~n)
int grid[20][20];
// direction 상-우-하-좌(0 1 2 3)
int player[30][5];	// x, y, d, s, 총
vector<int> visiting[20][20];	// 해당 그리드에 존재하는 플레이어 리스트
int ret[30];	// [0, 0, 0, 0, ..., 0]
// cf) 초기의 빈 격자에는 플레이어가 존재

// 플레이어 없을 때 이동
void Go(int p_num) {
	// visiting에서 기존자리의 p_num 삭제하기
	int px = player[p_num][0];
	int py = player[p_num][1];
	// ** 벡터에서 특정 원소를 찾아 지우는 것을 공부해보자! ** //
	int p_num_idx = find(visiting[px][py].begin(), visiting[px][py].end(), p_num) - visiting[px][py].begin();
	visiting[px][py].erase(visiting[px][py].begin() + p_num_idx);
	// 상 우 하 좌
	// 상
	if (player[p_num][2] == 0) {
		// 위로 갈 수 있다면 위로 가기, 위로 갈 수 없다면 아래로 가기
		if (player[p_num][0] - 1 >= 0) {
			player[p_num][0]--;
		}
		else player[p_num][0]++;
	}
	// 우
	else if (player[p_num][2] == 1) {
		// 오른쪽으로 갈 수 있다면 오른쪽으로, 갈 수 없다면 왼쪽으로
		if (player[p_num][1] + 1 < n) {
			player[p_num][1]++;
		}
		else player[p_num][1]--;
	}
	// 하
	else if (player[p_num][2] == 2) {
		// 아래로 갈 수 있다면 아래로, 갈 수 없다면 위로
		if (player[p_num][0] + 1 < n) {
			player[p_num][0]++;
		}
		else player[p_num][0]--;
	}
	// 좌
	else {
		// 왼쪽으로 갈 수 있다면 왼쪽으로, 갈 수 없다면 오른쪽으로
		if (player[p_num][1] - 1 >= 0) {
			player[p_num][1]--;
		}
		else player[p_num][1]++;
	}
	// 이동한 자리에 해당 유저를 추가해놓기
	int nx = player[p_num][0];
	int ny = player[p_num][1];
	visiting[nx][ny].push_back(p_num);
}

// 싸움 로직
// 입력값은 싸움이 일어난 격자의 위치
// 이긴 플레이어-진플레이어 player의 번호를 반환한다.
pair<int, int> fight(int fx, int fy) {
	// 결과로 내보낼 정보
	pair<int, int> win_lose;

	// 해당좌표에 있는 모든 유저의 정보를 가져오기
	int player1[6];	// 플레이어 번호 + 정보
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

	// 1. 능력치, 총의 공격력 비교하기
	int player1_power = player1[4] + player1[5];
	int player2_power = player2[4] + player2[5];
	// 1-1. player1이 파워 수치가 더 높은 경우
	if (player1_power > player2_power) {
		win_lose.first = player1[0];
		win_lose.second = player2[0];
		ret[player1[0]]++;
		return win_lose;
	}
	// 1-2. 파워 수치가 같다면 능력치를 비교
	else if (player1_power == player2_power) {
		// 능력치 비교
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
	// 1-3. player2가 파워 수치가 더 높은 경우
	else {
		win_lose.first = player2[0];
		win_lose.second = player1[0];
		ret[player2[0]]++;
		return win_lose;
	}
}

// 진 사람의 움직임 로직
void loserGo(int loserNum) {
	// 진 플레이어 방향이동
	// 만약 다른 플레이어가 있거나 격자범위 밖인 경우 오른쪽 
	// 90도 회전하여 빈 칸이 보이는 순간 이동
	// 총이 보이면 가장 높은 총 획득, 나머지 총은 내려놓는다.
	int lx = player[loserNum][0];
	int ly = player[loserNum][1];
	int ld = player[loserNum][2];
	int ls = player[loserNum][4];
	while (true) {
		// 위로
		if (ld == 0) {
			// 해당 방향으로 움직였을 때, 플레이어가 있거나 격자범위 밖인 경우 90도 회전
			if (lx - 1 < 0 || visiting[lx][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// 해당 방향으로 움직일 수 있다면 다음 로직 수행
			else {
				// 해당 방향으로 이동
				lx--;
				// 총이 있다면 가장 높은 총 획득, 나머지 총은 내려놓기
				if (ls < grid[lx][ly]) {
					int temp_loser_gun = ls;
					int temp_grid_gun = grid[lx][ly];
					ls = temp_grid_gun;
					grid[lx][ly] = temp_loser_gun;
				}
				break;
			}
		}
		// 오른쪽으로
		else if (ld == 1) {
			// 해당 방향으로 움직였을 때, 플레이어가 있거나 격자범위 밖인 경우 90도 회전
			if (ly + 1 >= n || visiting[lx][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// 해당 방향으로 움직일 수 있다면 다음 로직 수행
			else {
				// 해당 방향으로 이동
				ly++;
				// 총이 있다면 가장 높은 총 획득, 나머지 총은 내려놓기
				if (ls < grid[lx][ly]) {
					int temp_loser_gun = ls;
					int temp_grid_gun = grid[lx][ly];
					ls = temp_grid_gun;
					grid[lx][ly] = temp_loser_gun;
				}
				break;
			}
		}
		// 아래로
		else if (ld == 2) {
			// 해당 방향으로 움직였을 때, 플레이어가 있거나 격자범위 밖인 경우 90도 회전
			if (lx + 1 >= n || visiting[lx][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// 해당 방향으로 움직일 수 있다면 다음 로직 수행
			else {
				// 해당 방향으로 이동
				lx++;
				// 총이 있다면 가장 높은 총 획득, 나머지 총은 내려놓기
				if (ls < grid[lx][ly]) {
					int temp_loser_gun = ls;
					int temp_grid_gun = grid[lx][ly];
					ls = temp_grid_gun;
					grid[lx][ly] = temp_loser_gun;
				}
				break;
			}
		}
		// 왼쪽으로
		else {
			// 해당 방향으로 움직였을 때, 플레이어가 있거나 격자범위 밖인 경우 90도 회전
			if (ly - 1 < 0 || visiting[lx][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// 해당 방향으로 움직일 수 있다면 다음 로직 수행
			else {
				// 해당 방향으로 이동
				ly--;
				// 총이 있다면 가장 높은 총 획득, 나머지 총은 내려놓기
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
		// 1-1. 플레이어 이동하기
		Go(i);
		int px = player[i][0];
		int py = player[i][1];

		// 2-1. 이동한 곳에 플레이어가 없다면 총이 있는지 확인
		if (visiting[px][py].size() < 2) {
			// 이동한 자리에 더 쎈 총이 있다면, 총을 획득
			if (grid[px][py] > player[i][4]) {
				int temp = grid[px][py];
				int temp2 = player[i][4];
				player[i][4] = temp;
				grid[px][py] = temp;
			}
		}

		// 2-2-1. 이동한 곳에 플레이어가 있는 경우 싸움
		else {
			pair<int, int> winner_loser = fight(px, py);
			int winner = winner_loser.first;
			int loser = winner_loser.second;
			// 2-2-2. 진 플레이어는 총을 내려놓음
			int gun = player[loser][4];
			player[loser][4] = 0;
			grid[px][py] = gun;
			// 진 플레이어는 방향 이동
			loserGo(loser);
			// 2-2-3. 이긴 플레이어는 가장 강력한 총으로 교체
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
	// 입력
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
		}
	}
	
	// visiting -> -1 이면 플레이어 없음
	// -1이 아니면 해당 칸에 플레이어 번호가 들어감(0에서 시작)

	for (int i = 0; i < m; i++) {
		int x, y, d, s;	// s: 초기능력
		cin >> x >> y >> d >> s;
		player[i][0] = x;
		player[i][1] = y;
		player[i][2] = d;
		player[i][3] = s;
		visiting[x][y].push_back(i);
	}

	
	// 로직 수행
	for (int i = 0; i < k; i++) {
		Simulate();
	}

	// 출력
	for (int i = 0; i < m; i++) {
		cout << ret[i] << " ";
	}

	return 0;
}