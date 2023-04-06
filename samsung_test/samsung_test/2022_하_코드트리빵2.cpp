#include <iostream>
#include <tuple>
#include <queue>
#include <climits>

using namespace std;

int n, m;
int grid[15][15];
int curr_t = 0;
pair<int, int> cvs_list[30];	// 편의점 위치
pair<int, int> people[30];		// 사람의 위치 - 인덱스로 편의점과 매칭시킴
int dy[4] = { -1, 0, 0, 1 };
int dx[4] = { 0, -1, 1, 0 };

// bfs에서 사용하는 변수들
int step[15][15];			// 최단거리 결과 기록
int visited[15][15];		// 방문 여부 표시

// start_pos를 시작으로 BFS를 진행
// 시작점으로부터의 최단거리 결과는 step배열에 기록됩니다.
void BFS(pair<int, int> start_pos) {
	// visited, step값 초기화
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			visited[i][j] = false;
			step[i][j] = 0;
		}
	}

	// 초기 위치를 queue에 집어넣기
	queue<pair<int, int>> q;
	int sy = start_pos.first, sx = start_pos.second;
	q.push(start_pos);
	visited[sy][sx] = true;
	step[sy][sx] = 0;

	// BFS를 진행
	while (!q.empty()) {
		// 가장 앞에 원소를 골라줌
		pair<int, int> curr_pos = q.front();
		q.pop();

		// 인접한 칸을 보며 아직 방문하지 않은 칸을 큐에 넣는다.
		int y = curr_pos.first, x = curr_pos.second;
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i], nx = x + dx[i];
			// 갈 수 있는 경우에만 진행
			if (ny >= 0 && ny < n && nx >= 0 && nx < n && !visited[ny][nx] && grid[ny][nx] != 2) {
				visited[ny][nx] = true;
				step[ny][nx] = step[y][x] + 1;
				q.push(make_pair(ny, nx));
			}
		}
	}
}

void Simulate() {
	// Step 1. 격자에 있는 사람들에 한하여 편의점 방향을 향해 1칸 움직임
	for (int i = 0; i < m; i++) {
		// 격자에 있는 사람에 한하기 위해서, 밖에있는사람과 편의점에 있는 사람을 제외
		if (people[i] == make_pair(-1, -1) || people[i] == cvs_list[i])
			continue;

		BFS(cvs_list[i]); // 편의점에서 시작하는 BFS를 수행함

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
		// 우선순위가 가장 높은 칸으로 한 칸 움직이기
		people[i] = make_pair(min_y, min_x);
		

	}
	
	// Step 2. 편의점에 도착한다면 해당 편의점에 멈추고, 다른 사람은 이 편의점 못지나감
	for (int i = 0; i < m; i++) {
		if (people[i] == cvs_list[i]) {
			int py, px;
			tie(py, px) = people[i];
			grid[py][px] = 2;
		}
	}

	// Step 3. 현재 시간 curr_t에 대해서 curr_t <= m을 만족할때만
	if (curr_t > m)
		return;
	// Step 3-1. 편의점에서 BFS 진행
	BFS(cvs_list[curr_t - 1]);

	// Step 3-2. 편의점에서 가장 가까운 베이스 캠프를 선택
	//			 i, j가 증가하는 순으로 돌림 -> 가장 가까운 행, 열 우선순위
	int min_dist = INT_MAX;
	int min_y = -1;
	int min_x = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// 방문 가능한 베이스 캠프 중
			// 가장가까운 캠프 -> BFS동안 들렸고, base캠프(1)이며, min_dist갱신
			if (visited[i][j] && grid[i][j] == 1 && min_dist > step[i][j]) {
				min_dist = step[i][j];
				min_y = i, min_x = j;
			}
		}
	}
	// 우선순위가 가장 높은 베이스캠프로 이동
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
	// 입력
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

	// 초기에는 모든 사람이 격자 밖에 있음
	for (int i = 0; i < m; i++) {
		people[i] = make_pair(-1, -1);
	}

	// 1분에 한번씩 시뮬레이션을 진행합니다.
	while (true) {
		curr_t++;
		Simulate();
		// 전부 이동이 끝났으면 종료합니다.
		if (End()) break;
	}

	cout << curr_t;
	return 0;
}