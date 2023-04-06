#include <iostream>
#include <tuple>
#include <queue>
#include <climits>
#include <fstream>

#define MAX_N 15
#define MAX_M 30
#define DIR_NUM 4   // 방향 번호
#define EMPTY make_pair(-1, -1)

using namespace std;

// 변수 선언
int n, m;

// 0이면 빈 칸, 1이면 베이스 캠프, 2라면 아무도 갈 수 없는 곳을 뜻함
int grid[MAX_N][MAX_N];

// 편의점 목록 관리 -> 사람 수 만큼 편의점(max로 미리 만들어둠)
pair<int, int> cvs_list[MAX_M];

// 현재 사람의 위치 관리 -> 사람 수(max로 미리 만들기)
pair<int, int> people[MAX_M];

// 현재 시간 기록
int curr_t;

// dy, dx는 문제 우선순위 순서 -> 상좌우하
int dy[DIR_NUM] = { -1, 0, 0, 1 };
int dx[DIR_NUM] = { 0, -1, 1, 0 };

// bfs에서 사용하는 변수들
int step[MAX_N][MAX_N];     // 최단거리 결과 기록
bool visited[MAX_N][MAX_N]; // 방문 여부 표시

// start_pos를 시작으로 하는 BFS를 진행함
// 시작점으로부터의 최단거리 결과는 step배열에 기록됨
void BFS(pair<int, int> start_pos) {
    // visited, step 값을 전부 초기화
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = false;
            step[i][j] = 0;
        }
    }

    // 초기위치를 넣어줌
    queue<pair<int, int>> q;
    int sy = start_pos.first, sx = start_pos.second;
    q.push(start_pos);
    visited[sy][sx] = true;
    step[sy][sx] = 0;

    // BFS를 진행
    while (!q.empty()) {
        // 가장 앞의 원소
        pair<int, int> curr_pos = q.front();
        q.pop();

        // 인접한 칸을 보며 아직 방문하지 않은 칸을 큐에 넣음
        int y = curr_pos.first, x = curr_pos.second;
        for (int i = 0; i < DIR_NUM; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            // 1. 다음 점이 범위 안이고
            // 2. 들린 점이 아니며
            // 3. 갈 수 없는 점이 아니라면
            if (ny >= 0 && ny < n && nx >= 0 && nx < n && !visited[ny][nx] && grid[ny][nx] != 2) {
                visited[ny][nx] = true;
                step[ny][nx] = step[y][x] + 1;
                q.push(make_pair(ny, nx));
            }
        }
    }
}

// 시뮬레이션 진행
void Simulate() {
    // Step 1. 격자에 있는 사람들에 한하여 편의점 방향을 향해 1칸 움직임
    for (int i = 0; i < m; i++) {
        // 아직 격자 밖에 있는 사람이나 이미 편의점에 도착한 사람이라면 패스
        if (people[i] == EMPTY || people[i] == cvs_list[i])
            continue;

        // 원래는 현재 위치에서 편의점 위치까지의 최단거리를 구해줘야 한다.
        // 다만 최단거리가 되기 위한 그 다음 위치를 구하기 위해서는
        // 거꾸로 편의점 위치를 시작으로 현재 위치까지 오는 최단거리를 구해주는 것이 필요함??
        // 따라서 편의점 위치를 시작으로 하는 BFS를 진행
        BFS(cvs_list[i]);

        int py, px;                 // 사람의 현재위치
        tie(py, px) = people[i];
        // 현재 위치에서 상좌우하 중 최단거리 값이 가장 작은 곳을 고르면
        // 그 곳으로 이동하는 것이 최단거리 대로 이동한 것이 됨
        // 그러한 위치 중 상좌우하 우선순위대로 가장 적적한 곳을 골라줌
        int min_dist = INT_MAX;
        int min_y = -1, min_x = -1;
        for (int j = 0; j < DIR_NUM; j++) {
            int ny = py + dy[j];
            int nx = px + dx[j];
            // 다음점이 범위 안에 있고, visited한 곳이며, 최소값 갱신이 된다면
            if (ny >= 0 && ny < n && nx >= 0 && nx < n && visited[ny][nx] && min_dist > step[ny][nx]) {
                min_dist = step[ny][nx];
                min_y = ny;
                min_x = nx;
            }
        }

        // 우선순위가 가장 높은 위치로 한 칸 움직인다.
        people[i] = make_pair(min_x, min_y);
    }


    // Step 2. 편의점에 도착한 사람에 한하여
    //         앞으로 이동 불가능하다는 표시로
    //         grid값을 2로 바꿔주기
    for (int i = 0; i < m; i++) {
        if (people[i] == cvs_list[i]) {
            int py, px;
            tie(py, px) = people[i];
            grid[py][px] = 2;
        }
    }


    // Step 3. 현재 시간 curr_t에 대해 curr_t <= m을 만족한다면
    //         t번 사람이 베이스 캠프로 이동

    // curr_t가 m보다 크다면 패스
    if (curr_t > m)
        return;

    // Step 3-1. 편의점으로부터 가장 가까운 베이스 캠프를 고르기 위해
    //           편의점을 시작으로 하는 BFS를 진행
    BFS(cvs_list[curr_t - 1]);

    // Step 3-2. 편의점에서 가장 가까운 베이스 캠프를 선택
    //           i, j가 증가하는 순으로 돌리기 때문에
    //           가장 가까운 베이스 캠프가 여러 가지여도
    //           알아서 (행, 열) 우선순위대로 골라짐
    int min_dist = INT_MAX;
    int min_y = -1, min_x = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // 방문 가능한 베이스 캠프 중
            // 거리가 가장 가까운 캠프를 찾아줌
            if (visited[i][j] && grid[i][j] == 1 && min_dist > step[i][j]) {
                min_dist = step[i][j];
                min_y = i; min_x = j;
            }
        }
    }

    // 우선순위가 가장 높은 베이스 캠프로 이동합니다.
    people[curr_t - 1] = make_pair(min_y, min_x);
    // 해당 베이스 캠프는 앞으로 이동이 불가능한 캄
    grid[min_y][min_x] = 2;
}


// 전부 편의점에 도착했는지 확인
bool End() {
    // 단 한사람이라도
    // 편의점에 도착하지 못했다면
    // 아직 끝나지 않은 것
    for (int i = 0; i < m; i++) {
        if (people[i] != cvs_list[i])
            return false;
    }

    // 전부 편의점에 도착했다면 끝
    return true;
}

int main() {
    // 입력
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    for (int i = 0; i < m; i++) {
        int y, x;
        cin >> y >> x;
        cvs_list[i] = make_pair(y - 1, x - 1);
    }

    // 초기사람들은 격자 밖에 있으므로
    // 위치를 EMPTY로 놓기
    for (int i = 0; i < m; i++)
        people[i] = EMPTY;

    // 1분에 한번씩 시뮬레이션 진행
    while (true) {
        curr_t++;
        Simulate();
        // 전부 이동이 끝났으면 종료
        if (End()) break;
    }

    cout << curr_t;
    return 0;
}
