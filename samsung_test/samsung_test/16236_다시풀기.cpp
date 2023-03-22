#include<iostream>
#include<queue>
#define INF 987654321
using namespace std;

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
	// 상어 조건
	int size = 2, cnt = 2;
	Point minPt = { r, c, 0 };

	// 하나의 물고기를 찾는 과정
	do {
		bool visited[20][20] = { false };
		queue<Point> myqueue;					// 큐만들기
		myqueue.push({ minPt.r, minPt.c, 0 });	// 큐에 첫번째 점 넣기
		visited[minPt.r][minPt.c] = true;		// 처음 점 방문처리
		minPt.d = INF;

		while (!myqueue.empty()) {
			Point curr = myqueue.front();
			myqueue.pop();
			// 이미 최소 거리 보다 먼 경우
			if (minPt.d < curr.d) break;
			// 물고기가 아기상어보다 크다면 진행 못함
			if (Map[curr.r][curr.c] > size)continue;
			// 물고기가 있는 경우
			if (Map[curr.r][curr.c] != 0 && Map[curr.r][curr.c] < size) {
				// 가까운 게 먼저
				if (curr.d < minPt.d) {
					minPt = curr;
				}
				// 같은 거리
				else if (curr.d == minPt.d) {
					if (curr.r < minPt.r) {
						minPt = curr;
					}
					// 왼쪽에 있는 것 먼저
					else if (curr.r == minPt.r && curr.c < minPt.c) {
						minPt = curr;
					}
				}
				continue;
			}

			for (int i = 0; i < 4; i++) {
				int nr = curr.r + Dr[i];
				int nc = curr.c + Dc[i];
				if (nr < 0 || nr > N - 1 || nc < 0 || nc > N - 1)continue;
				if (visited[nr][nc] != false)continue;
				visited[nr][nc] = true;
				myqueue.push({ nr, nc, curr.d + 1 });
			}
		}
		// 위의 과정에서 가장 가까운 물고기를 찾은경우
		if (minPt.d != INF) {
			ret += minPt.d;
			--cnt;
			if (cnt == 0) {
				size++;
				cnt = size;
			}
			Map[minPt.r][minPt.c] = 0;
		}
	} while (minPt.d != INF);
	return ret;
}

int main() {
	cin >> N;
	int sr, sc;		// sr : 상어의 행위치, sc : 상어의 열위치
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