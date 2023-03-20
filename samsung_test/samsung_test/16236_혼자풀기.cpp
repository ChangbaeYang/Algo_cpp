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
	int ret = 0;
	int size = 2, cnt = 2;
	Point minPt = { r, c, 0 }; // 최초의 점
	do {
		bool visited[20][20] = { false };
		queue<Point> myqueue;
		myqueue.push({ minPt.r, minPt.c, 0 });
		visited[minPt.r][minPt.c] = true; // 최초의 점 방문처리
		minPt.d = INF;

		while (!myqueue.empty()) {
			Point curr = myqueue.front();
			myqueue.pop();

			// 이미 거리가 너무 멀어져버린 경우
			if (curr.d > minPt.d) break;
			// 물고기가 상어보다 큰 경우
			if (Map[curr.r][curr.c] > size) continue;
			// 먹을 수 있는 물고기를 찾은 경우
			if (Map[curr.r][curr.c] != 0 && Map[curr.r][curr.c] < size) {
				// 더 가까운 거리가 있다면 가까운거 먼저
				if (curr.d < minPt.d) {
					minPt = curr;
				}
				// 같은 거리인 경우
				else if (curr.d == minPt.d) {
					// 위에꺼 먼저
					if (curr.r < minPt.r) {
						minPt = curr;
					}
					// 왼쪽꺼 먼저
					else if (curr.r == minPt.r && curr.c < minPt.c) {
						minPt = curr;
					}
				}
				continue; // 더이상 탐색을 진행할 필요가 없음
				// 더 탐색을 진행해 봐야 더 멀리있는 물고기임
			}


			// 다음 점 찾는 로직
			for (int i = 0; i < 4; i++) {
				int nr = curr.r + Dr[i];
				int nc = curr.c + Dc[i];
				if (nr < 0 || nr > N - 1 || nc < 0 || nc > N - 1)continue;
				if (visited[nr][nc] != 0)continue;
				visited[nr][nc] = true;	// 방문처리
				myqueue.push({ nr, nc, curr.d + 1 });
			}
		}

		// 위의 과정에서 가장 가까운 물고기를 찾은 경우
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
	return ret;	// 결과값을 반환하기
}

int main() {
	cin >> N;
	int sr, sc;	// sr : 아기 상어의 행, sc : 아기 상어의 열
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			// 아기상어의 위치는 0으로 바꿔주기(for 움직이기)
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