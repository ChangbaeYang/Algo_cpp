#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

vector<vector<int>> fish;	// 물고기 좌표를 담을 변수({물고기 크기, y좌표, x좌표})
int n;				// 공간의 크기
int a[21][21];		// 물고기 자리를 담을 배열
int baby_size = 2;	// 아기상어의 크기
int baby_ex = 0;	// 아기상어 성장 경험치
pair<int, int> baby_idx;	// 아기 상어의 좌표
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };
int visited[21][21];
int ret = 0;

// 아기 상어가 목적지 물고기까지 가는 최단 거리를 구한다.(거리가 시간으로 더해짐)
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
			// 목적지에 도달했다면
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
			// 아기 상어 좌표 추출
			if (a[i][j] == 9) {
				baby_idx.first = i;
				baby_idx.second = j;
				a[i][j] = 0;
			}
			// 다른 물고기 좌표 추출
			else if (a[i][j] != 0 && a[i][j] != 9) {
				fish.push_back({ a[i][j], i, j });
			}
		}
	}
	sort(fish.begin(), fish.end()); // 물고기 크기별로 정렬 된다.-> 위에서 아래로는 이미 정렬되어 있음
	while (true) {

		// 0. 먹을 수 있는 물고기의 수를 센다. + 물고기의 좌표값
		int can_eat = 0;
		vector<vector<int>> can_eat_idx;
		for (int i = 0; i < fish.size(); i++) {
			if (fish[i][0] < baby_size) {
				can_eat++;
				can_eat_idx.push_back({ i, fish[i][1], fish[i][2] });
			}
		}

		// 1. 먹을 수 있는 물고기가 없는 경우
		if (can_eat == 0) break;

		// 2. 먹을 수 있는 물고기가 한 마리인 경우 -> 그 물고기를 먹으러간다.
		else if (can_eat == 1) {
			// 해당 물고기까지 갈 수 있는지를 파악한다.(함수)
			int min_dist = 999; // 가게 되는 거리
			pair<int, int> cash_can_eat = { can_eat_idx[0][1], can_eat_idx[0][2] };
			bfs(baby_idx, cash_can_eat, min_dist);
			if (min_dist == 999)break; // 해당 물고기까지 갈 수 없다면

			ret += min_dist;
			// 아기 상어 ex늘어남 - ex가 크기만큼 되면, 크기 늘어남, ex초기화
			baby_ex++;
			if (baby_ex == baby_size) {
				baby_ex = 0;
				baby_size++;
			}
			// 아기 상어 위치 바뀜 -> 먹은 위치로
			baby_idx.first = cash_can_eat.first;
			baby_idx.second = cash_can_eat.second;
			// 먹힌 물고기 좌표 0으로 바꾸기
			a[baby_idx.first][baby_idx.second] = 0;
			fish.erase(fish.begin());	// 맨 앞에 있는 값이 먹을 수 있는 물고기였음
		}

		// 3. 먹을 수 있는 물고기가 여러마리인 경우 -> 가장 가까운 물고기 먹으러간다.
		else {
			// 가장 가까운 거리와 해당 좌표를 찾아야함
			int min_dist2 = 999;
			pair<int, int> where_to_eat;
			int where_to_eat_idx;
			for (int i = 0; i < can_eat_idx.size(); i++) {
				int temp = min_dist2;
				pair<int, int> cash_can_eat2 = { can_eat_idx[i][1], can_eat_idx[i][2] };
				bfs(baby_idx, cash_can_eat2, min_dist2);
				// min_dist 가 생긴 됬다면, 이동할 물고기 좌표가 바뀐다.
				if (temp != min_dist2) {
					where_to_eat = cash_can_eat2;
					where_to_eat_idx = can_eat_idx[i][0];	// fish에서의 인덱스
				}
			}
			// 갈 수 있는 곳이 없는 경우 break
			if (min_dist2 == 999)break;
			// 갈 수 있다면 상어는 이동
			ret += min_dist2;
			// 아기 상어 ex늘어남 - ex가 크기만큼 되면, 크기 늘어남. ex초기화
			baby_ex++;
			if (baby_ex == baby_size) {
				baby_ex = 0;
				baby_size++;
			}
			// 아기 상어 위치 바뀜 -> 먹은 위치로
			baby_idx.first = where_to_eat.first;
			baby_idx.second = where_to_eat.second;
			// 먹힌 물고기 좌표 0으로 바꾸기
			a[baby_idx.first][baby_idx.second] = 0;
			// fish값도 갱신해줘야한다.
			fish.erase(fish.begin() + where_to_eat_idx);
		}
	}
	cout << ret << "\n";
	return 0;
}