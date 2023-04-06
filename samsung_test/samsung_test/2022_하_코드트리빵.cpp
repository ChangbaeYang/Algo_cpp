#include <iostream>
#include <tuple>
#include <queue>
#include <climits>
#include <fstream>

#define MAX_N 15
#define MAX_M 30
#define DIR_NUM 4   // ���� ��ȣ
#define EMPTY make_pair(-1, -1)

using namespace std;

// ���� ����
int n, m;

// 0�̸� �� ĭ, 1�̸� ���̽� ķ��, 2��� �ƹ��� �� �� ���� ���� ����
int grid[MAX_N][MAX_N];

// ������ ��� ���� -> ��� �� ��ŭ ������(max�� �̸� ������)
pair<int, int> cvs_list[MAX_M];

// ���� ����� ��ġ ���� -> ��� ��(max�� �̸� �����)
pair<int, int> people[MAX_M];

// ���� �ð� ���
int curr_t;

// dy, dx�� ���� �켱���� ���� -> ���¿���
int dy[DIR_NUM] = { -1, 0, 0, 1 };
int dx[DIR_NUM] = { 0, -1, 1, 0 };

// bfs���� ����ϴ� ������
int step[MAX_N][MAX_N];     // �ִܰŸ� ��� ���
bool visited[MAX_N][MAX_N]; // �湮 ���� ǥ��

// start_pos�� �������� �ϴ� BFS�� ������
// ���������κ����� �ִܰŸ� ����� step�迭�� ��ϵ�
void BFS(pair<int, int> start_pos) {
    // visited, step ���� ���� �ʱ�ȭ
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = false;
            step[i][j] = 0;
        }
    }

    // �ʱ���ġ�� �־���
    queue<pair<int, int>> q;
    int sy = start_pos.first, sx = start_pos.second;
    q.push(start_pos);
    visited[sy][sx] = true;
    step[sy][sx] = 0;

    // BFS�� ����
    while (!q.empty()) {
        // ���� ���� ����
        pair<int, int> curr_pos = q.front();
        q.pop();

        // ������ ĭ�� ���� ���� �湮���� ���� ĭ�� ť�� ����
        int y = curr_pos.first, x = curr_pos.second;
        for (int i = 0; i < DIR_NUM; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            // 1. ���� ���� ���� ���̰�
            // 2. �鸰 ���� �ƴϸ�
            // 3. �� �� ���� ���� �ƴ϶��
            if (ny >= 0 && ny < n && nx >= 0 && nx < n && !visited[ny][nx] && grid[ny][nx] != 2) {
                visited[ny][nx] = true;
                step[ny][nx] = step[y][x] + 1;
                q.push(make_pair(ny, nx));
            }
        }
    }
}

// �ùķ��̼� ����
void Simulate() {
    // Step 1. ���ڿ� �ִ� ����鿡 ���Ͽ� ������ ������ ���� 1ĭ ������
    for (int i = 0; i < m; i++) {
        // ���� ���� �ۿ� �ִ� ����̳� �̹� �������� ������ ����̶�� �н�
        if (people[i] == EMPTY || people[i] == cvs_list[i])
            continue;

        // ������ ���� ��ġ���� ������ ��ġ������ �ִܰŸ��� ������� �Ѵ�.
        // �ٸ� �ִܰŸ��� �Ǳ� ���� �� ���� ��ġ�� ���ϱ� ���ؼ���
        // �Ųٷ� ������ ��ġ�� �������� ���� ��ġ���� ���� �ִܰŸ��� �����ִ� ���� �ʿ���??
        // ���� ������ ��ġ�� �������� �ϴ� BFS�� ����
        BFS(cvs_list[i]);

        int py, px;                 // ����� ������ġ
        tie(py, px) = people[i];
        // ���� ��ġ���� ���¿��� �� �ִܰŸ� ���� ���� ���� ���� ����
        // �� ������ �̵��ϴ� ���� �ִܰŸ� ��� �̵��� ���� ��
        // �׷��� ��ġ �� ���¿��� �켱������� ���� ������ ���� �����
        int min_dist = INT_MAX;
        int min_y = -1, min_x = -1;
        for (int j = 0; j < DIR_NUM; j++) {
            int ny = py + dy[j];
            int nx = px + dx[j];
            // �������� ���� �ȿ� �ְ�, visited�� ���̸�, �ּҰ� ������ �ȴٸ�
            if (ny >= 0 && ny < n && nx >= 0 && nx < n && visited[ny][nx] && min_dist > step[ny][nx]) {
                min_dist = step[ny][nx];
                min_y = ny;
                min_x = nx;
            }
        }

        // �켱������ ���� ���� ��ġ�� �� ĭ �����δ�.
        people[i] = make_pair(min_x, min_y);
    }


    // Step 2. �������� ������ ����� ���Ͽ�
    //         ������ �̵� �Ұ����ϴٴ� ǥ�÷�
    //         grid���� 2�� �ٲ��ֱ�
    for (int i = 0; i < m; i++) {
        if (people[i] == cvs_list[i]) {
            int py, px;
            tie(py, px) = people[i];
            grid[py][px] = 2;
        }
    }


    // Step 3. ���� �ð� curr_t�� ���� curr_t <= m�� �����Ѵٸ�
    //         t�� ����� ���̽� ķ���� �̵�

    // curr_t�� m���� ũ�ٸ� �н�
    if (curr_t > m)
        return;

    // Step 3-1. ���������κ��� ���� ����� ���̽� ķ���� ���� ����
    //           �������� �������� �ϴ� BFS�� ����
    BFS(cvs_list[curr_t - 1]);

    // Step 3-2. ���������� ���� ����� ���̽� ķ���� ����
    //           i, j�� �����ϴ� ������ ������ ������
    //           ���� ����� ���̽� ķ���� ���� ��������
    //           �˾Ƽ� (��, ��) �켱������� �����
    int min_dist = INT_MAX;
    int min_y = -1, min_x = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // �湮 ������ ���̽� ķ�� ��
            // �Ÿ��� ���� ����� ķ���� ã����
            if (visited[i][j] && grid[i][j] == 1 && min_dist > step[i][j]) {
                min_dist = step[i][j];
                min_y = i; min_x = j;
            }
        }
    }

    // �켱������ ���� ���� ���̽� ķ���� �̵��մϴ�.
    people[curr_t - 1] = make_pair(min_y, min_x);
    // �ش� ���̽� ķ���� ������ �̵��� �Ұ����� į
    grid[min_y][min_x] = 2;
}


// ���� �������� �����ߴ��� Ȯ��
bool End() {
    // �� �ѻ���̶�
    // �������� �������� ���ߴٸ�
    // ���� ������ ���� ��
    for (int i = 0; i < m; i++) {
        if (people[i] != cvs_list[i])
            return false;
    }

    // ���� �������� �����ߴٸ� ��
    return true;
}

int main() {
    // �Է�
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    for (int i = 0; i < m; i++) {
        int y, x;
        cin >> y >> x;
        cvs_list[i] = make_pair(y - 1, x - 1);
    }

    // �ʱ������� ���� �ۿ� �����Ƿ�
    // ��ġ�� EMPTY�� ����
    for (int i = 0; i < m; i++)
        people[i] = EMPTY;

    // 1�п� �ѹ��� �ùķ��̼� ����
    while (true) {
        curr_t++;
        Simulate();
        // ���� �̵��� �������� ����
        if (End()) break;
    }

    cout << curr_t;
    return 0;
}
