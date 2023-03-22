#include<iostream>
#include<queue>
#define INF 987654321
using namespace std;

// 아기상어 초기크기 2
// 1초에 상화좌우 인접한 한 칸씩 이동 *
// 자신보다 큰 물고기 못지나감 *
// 자신 크기보다 작은 물고기만 먹을 수 있음 *
// 물고기 1마리 -> 그 물고기 *
// 물고기 여러마리, 가장 가까운 물고기 부터 *
// 가까운 물고기 많을 때 -> 가장 위 물고기 -> 가장 왼쪽 물고기 *
// 물고기를 먹으면 해당 칸은 빈칸이 된다. *

int N;
int Map[20][20];
int Dr[4] = { -1, 1, 0, 0 };
int Dc[4] = { 0, 0, -1, 1 };

struct Point {
	int r, c, d;
};

int solve(int r, int c) {
	// 결과값
	int ret = 0;
	// 상어의 초기 사이즈와 먹어야하는 고기
	int size = 2, cnt = 2;
	// 최초의 점
	Point minPt = { r, c, 0 };

	// 물고기를 못찾을 때까지 반복해야한다.
	// 물고기를 못찾았다는 기준 -> minPt.d(거리가 무한대인 경우)
	do {
		// BFS를 수행한다.
		bool visited[20][20] = { false };	// 물고기를 찾을 때마다 visited 초기화
		queue<Point> myqueue;
		myqueue.push({ minPt.r, minPt.c, 0 });	// 최초의 점을 큐에 넣는다.
		visited[minPt.r][minPt.c] = true;		// 최초의 점 방문 처리
		minPt.d = INF;	// 최소값을 구하기 위해 최대에서 시작한다.
		while (!myqueue.empty()) {
			Point curr = myqueue.front();
			myqueue.pop();
			
			// 최소거리보다 지금 거리가 먼 경우 더 이상 진행할 필요가 없음
			if (curr.d > minPt.d)break;
			// 자신보다 큰 물고기 일 경우 더 이상 진행할 수 없음
			if (Map[curr.r][curr.c] > size)continue;
			// 물고기를 만난 경우
			if (Map[curr.r][curr.c] != 0 &&  Map[curr.r][curr.c] < size) {
				// 물고기가 가장 가까운 경우
				if (curr.d < minPt.d) {
					minPt = curr;
				}
				// 해당 물고기가 거리가 같은 경우
				else if (curr.d == minPt.d) {
					// 위의 물고기부터 처리
					if (curr.r < minPt.r) {
						minPt = curr;
					}
					// 높이가 같은 경우 왼쪽 물고기 부터 처리
					else if (curr.r == minPt.r && curr.c < minPt.c) {
						minPt = curr;
					}
				}
				continue;	// 물고기를 만났다면 더이상 해당 점에서 뻗어나가는 것을 확인할 필요가 없다.
			}
			// 다음 점을 찾는 로직
			for (int i = 0; i < 4; i++) {
				int nr = curr.r + Dr[i];
				int nc = curr.c + Dc[i];
				if (nr < 0 || nr > N - 1 || nc < 0 || nc > N - 1)continue;
				if (visited[nr][nc] != false)continue;
				myqueue.push({ nr, nc, curr.d + 1 });	// 다음 점을 큐에 넣는다.(거리 + 1)
				visited[nr][nc] = true;
			}
		}

		// 물고기를 찾았을 경우의 행동
		if (minPt.d != INF) {
			ret += minPt.d;
			cnt--;
			if (cnt == 0) {
				size++;
				cnt = size;
			}
			Map[minPt.r][minPt.c] = 0;	// 고기를 먹으면 해당 자리는 0
		}
	} while (minPt.d != INF);
	return ret;
}

int main() {
	cin >> N;
	int sr, sc;		// sr : 상어의 행, sc : 상어의 열
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 9) {
				sr = i;
				sc = j;
				Map[i][j] = 0;
			}
		}
	}
	cout << solve(sr, sc) << "\n";
	return 0;
}