#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, k;	// n(2~20), m(1~30), k(1~500), 총공격력(1~10만), s(1~100), x,y(1~n)
vector<int> grid[20][20];
// direction 상-우-하-좌(0 1 2 3)
int player[30][5];	// x, y, d, s, 총
vector<int> visiting[20][20];	// 해당 그리드에 존재하는 플레이어 리스트
int ret[30];	// [0, 0, 0, 0, ..., 0]
// cf) 초기의 빈 격자에는 플레이어가 존재

// 해당 칸의 최고의 총을 찾는 함수
int find_best_gun(int gx, int gy) {
	int ret = 0;
	for (int i = 0; i < grid[gx][gy].size(); i++) {
		if (grid[gx][gy][i] > ret) ret = grid[gx][gy][i];
	}
	return ret;
}

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
		else {
			// 방향도 바꾸기
			player[p_num][2] = 2;
			player[p_num][0]++;
		}
	}
	// 우
	else if (player[p_num][2] == 1) {
		// 오른쪽으로 갈 수 있다면 오른쪽으로, 갈 수 없다면 왼쪽으로
		if (player[p_num][1] + 1 < n) {
			player[p_num][1]++;
		}
		else {
			// 방향도 바꾸기
			player[p_num][2] = 3;
			player[p_num][1]--;
		}
	}
	// 하
	else if (player[p_num][2] == 2) {
		// 아래로 갈 수 있다면 아래로, 갈 수 없다면 위로
		if (player[p_num][0] + 1 < n) {
			player[p_num][0]++;
		}
		else {
			player[p_num][2] = 0;
			player[p_num][0]--;
		}
	}
	// 좌
	else {
		// 왼쪽으로 갈 수 있다면 왼쪽으로, 갈 수 없다면 오른쪽으로
		if (player[p_num][1] - 1 >= 0) {
			player[p_num][1]--;
		}
		else {
			player[p_num][2] = 1;
			player[p_num][1]++;
		}
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
			player2[i + 1] = player[player2[0]][i];
		}
	}

	// 1. 능력치, 총의 공격력 비교하기
	int player1_power = player1[4] + player1[5];
	int player2_power = player2[4] + player2[5];
	// 1-1. player1이 파워 수치가 더 높은 경우
	if (player1_power > player2_power) {
		win_lose.first = player1[0];
		win_lose.second = player2[0];
		ret[player1[0]] = ret[player1[0]] + player1_power - player2_power;
		return win_lose;
	}
	// 1-2. 파워 수치가 같다면 능력치를 비교
	else if (player1_power == player2_power) {
		// 능력치 비교
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
	// 1-3. player2가 파워 수치가 더 높은 경우
	else {
		win_lose.first = player2[0];
		win_lose.second = player1[0];
		ret[player2[0]] = ret[player2[0]] + player2_power - player1_power;
		return win_lose;
	}
}

// 진 사람의 움직임 로직
void loserGo(int loserNum) {
	// visiting에서 기존자리의 loserNum 삭제
	int px = player[loserNum][0];
	int py = player[loserNum][1];
	// ** 벡터에서 특정 원소를 찾아 지우는 것을 공부해보자! ** //
	int p_num_idx = find(visiting[px][py].begin(), visiting[px][py].end(), loserNum) - visiting[px][py].begin();
	visiting[px][py].erase(visiting[px][py].begin() + p_num_idx);

	while (true) {
		int lx = player[loserNum][0];
		int ly = player[loserNum][1];
		int ld = player[loserNum][2];
		int ls = player[loserNum][4];
		// 위로
		if (ld == 0) {
			// 해당 방향으로 움직였을 때, 플레이어가 있거나 격자범위 밖인 경우 90도 회전
			if (lx - 1 < 0 || visiting[lx - 1][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// 해당 방향으로 움직일 수 있다면 다음 로직 수행
			else {
				// 해당 방향으로 이동
				player[loserNum][0]--;
				// 총이 있다면 가장 높은 총 획득, 나머지 총은 내려놓기
				int best_gun_a = find_best_gun(player[loserNum][0], player[loserNum][1]);
				if (ls < best_gun_a) {
					int temp_loser_gun = ls;
					player[loserNum][4] = best_gun_a;
					// grid에서 해당 총 삭제, 사용자의 총으로 대체
					int best_gun_a_idx = find(grid[lx - 1][ly].begin(), grid[lx - 1][ly].end(), best_gun_a) - grid[lx - 1][ly].begin();
					grid[lx - 1][ly].erase(grid[lx - 1][ly].begin() + best_gun_a_idx);
					grid[lx - 1][ly].push_back(temp_loser_gun);
				}
				break;
			}
		}
		// 오른쪽으로
		else if (ld == 1) {
			// 해당 방향으로 움직였을 때, 플레이어가 있거나 격자범위 밖인 경우 90도 회전
			if (ly + 1 >= n || visiting[lx][ly + 1].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// 해당 방향으로 움직일 수 있다면 다음 로직 수행
			else {
				// 해당 방향으로 이동
				player[loserNum][1]++;
				// 총이 있다면 가장 높은 총 획득, 나머지 총은 내려놓기
				int best_gun_b = find_best_gun(player[loserNum][0], player[loserNum][1]);
				if (ls < best_gun_b) {
					int temp_loser_gun = ls;
					player[loserNum][4] = best_gun_b;
					// grid에서 해당 총 삭제, 사용자의 총으로 대체
					int best_gun_b_idx = find(grid[lx][ly + 1].begin(), grid[lx][ly + 1].end(), best_gun_b) - grid[lx][ly + 1].begin();
					grid[lx][ly + 1].erase(grid[lx][ly + 1].begin() + best_gun_b_idx);
					grid[lx][ly + 1].push_back(temp_loser_gun);
				}
				break;
			}
		}
		// 아래로
		else if (ld == 2) {
			// 해당 방향으로 움직였을 때, 플레이어가 있거나 격자범위 밖인 경우 90도 회전
			if (lx + 1 >= n || visiting[lx + 1][ly].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// 해당 방향으로 움직일 수 있다면 다음 로직 수행
			else {
				// 해당 방향으로 이동
				player[loserNum][0]++;
				// 총이 있다면 가장 높은 총 획득, 나머지 총은 내려놓기
				int best_gun_c = find_best_gun(player[loserNum][0], player[loserNum][1]);
				if (ls < best_gun_c) {
					int temp_loser_gun = ls;
					player[loserNum][4] = best_gun_c;
					// grid에서 해당 총 삭제, 사용자의 총으로 대체
					int best_gun_c_idx = find(grid[lx + 1][ly].begin(), grid[lx + 1][ly].end(), best_gun_c) - grid[lx + 1][ly].begin();
					grid[lx + 1][ly].erase(grid[lx + 1][ly].begin() + best_gun_c_idx);
					grid[lx + 1][ly].push_back(temp_loser_gun);
				}
				break;
			}
		}
		// 왼쪽으로
		else {
			// 해당 방향으로 움직였을 때, 플레이어가 있거나 격자범위 밖인 경우 90도 회전
			if (ly - 1 < 0 || visiting[lx][ly - 1].size() != 0) {
				player[loserNum][2] = (player[loserNum][2] + 1) % 4;
			}
			// 해당 방향으로 움직일 수 있다면 다음 로직 수행
			else {
				// 해당 방향으로 이동
				player[loserNum][1]--;
				// 총이 있다면 가장 높은 총 획득, 나머지 총은 내려놓기
				int best_gun_d = find_best_gun(player[loserNum][0], player[loserNum][1]);
				if (ls < best_gun_d) {
					int temp_loser_gun = ls;
					player[loserNum][4] = best_gun_d;
					// grid에서 해당 총 삭제, 사용자의 총으로 대체
					int best_gun_d_idx = find(grid[lx][ly - 1].begin(), grid[lx][ly - 1].end(), best_gun_d) - grid[lx][ly - 1].begin();
					grid[lx][ly - 1].erase(grid[lx][ly - 1].begin() + best_gun_d_idx);
					grid[lx][ly - 1].push_back(temp_loser_gun);
				}
				break;
			}
		}
	}
	// 이동한 자리에 해당 유저를 추가해놓기
	int nx = player[loserNum][0];
	int ny = player[loserNum][1];
	visiting[nx][ny].push_back(loserNum);
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
			int best_gun = find_best_gun(px, py);
			if (best_gun > player[i][4]) {
				int temp = player[i][4];
				player[i][4] = best_gun;
				// 해당 칸에서 가장 쎈 총을 없애고, player가 떨군 총을 추가하기
				int best_gun_idx = find(grid[px][py].begin(), grid[px][py].end(), best_gun) - grid[px][py].begin();
				grid[px][py].erase(grid[px][py].begin() + best_gun_idx);
				grid[px][py].push_back(temp);
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
			grid[px][py].push_back(gun);	// 내려놓은 총 추가
			// 진 플레이어는 방향 이동
			loserGo(loser);
			// 2-2-3. 이긴 플레이어는 가장 강력한 총으로 교체
			int best_gun_2 = find_best_gun(px, py);
			if (best_gun_2 > player[winner][4]) {
				int temp_gun2 = player[winner][4];
				player[winner][4] = best_gun_2;
				// 교체 과정.
				int best_gun_2_idx = find(grid[px][py].begin(), grid[px][py].end(), best_gun_2) - grid[px][py].begin();
				grid[px][py].erase(grid[px][py].begin() + best_gun_2_idx);
				grid[px][py].push_back(temp_gun2);
			}
		}
	}
}

int main() {
	// 입력
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int temp;
			cin >> temp;
			grid[i][j].push_back(temp);
		}
	}

	for (int i = 0; i < m; i++) {
		int x, y, d, s;	// s: 초기능력
		cin >> x >> y >> d >> s;
		player[i][0] = x - 1;
		player[i][1] = y - 1;
		player[i][2] = d;
		player[i][3] = s;
		visiting[x - 1][y - 1].push_back(i);
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