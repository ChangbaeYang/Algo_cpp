#include<iostream>
#include<queue>
#define INF 987654321

using namespace std;
// N*N 크기의 공간에 물고기 M마리-> M은 안주어짐 **
// 아기상어 1마리 - 초기 크기 2, 1초에 상하좌우 **
// 본인보다 작은 물고기 먹음 **
// 크기가 같은 물고기는 먹을 수 없지만, 지나갈 수 있다. ** 
// 한 칸에 물고기 최대 1마리 **
// 먹을 수 있는 물고기 1 -> 그 물고기 **
// 물고기 1마리 보다 많다면 -> 가장 가까운 물고기 **
// 가장 가까운 물고기 많다면 위에서 부터 -> 왼쪽에서 부터 **
// 아기상어 -> 물고기 이동할 때 지나가야하는 칸의 개수가 거리 **

int N;
int Map[20][20];
int Dr[4] = { -1, 1, 0, 0 };	// 상하좌우
int Dc[4] = { 0, 0, -1, 1 };	// 상하좌우

struct Point {
	int r, c, d;	// Point struct의 멤버변수
};

int solve(int r, int c) {
	int ret = 0;
	int size = 2, cnt = 2;
	Point minPt = { r, c, 0 };
	do {
		// BFS 로직을 활용할 것이다.
		bool visited[20][20] = { false };
		queue<Point> myqueue;
		myqueue.push({ minPt.r, minPt.c, 0 });	// 갱신된 minPt의 점
		visited[minPt.r][minPt.c] = true;	// 초기점 방문처리
		minPt.d = INF;	// 처음위치를 무한대로 잡는다.
		while (!myqueue.empty()) {
			Point curr = myqueue.front();
			myqueue.pop();

			// 만약 점이 너무 멀다면
			if (curr.d > minPt.d)break;	// 더 이상 BFS를 진행하는 의미없음
			// 만약 점의 물고기가 상어보다 크다면
			if (Map[curr.r][curr.c] > size)continue; // 지나갈 수 없으므로 컨티뉴
			// 만약 물고기를 먹을 수 있는 경우라면
			if (Map[curr.r][curr.c] != 0 && Map[curr.r][curr.c] < size) {
				// 물고기가 기존의 것보다 가까이 있는 경우
				if (curr.d < minPt.d) {
					minPt = curr;
				}
				// 거리가 똑같을 때
				else if (curr.d == minPt.d) {
					// 위에 있는 물고기 부터
					if (curr.r < minPt.r) {
						minPt = curr;
					}
					// 둘이 높이가 같다면 왼쪽부터
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
				visited[nr][nc] = true;	// 방문처리
				myqueue.push({ nr, nc, curr.d + 1 });	// 다음 점 큐에 삽입
			}
		}

		// 물고기를 먹은 경우
		if (minPt.d != INF) {
			ret += minPt.d;
			cnt--;
			if (cnt == 0) {
				size++;
				cnt = size;
			}
			Map[minPt.r][minPt.c] = 0;
		}
	} while (minPt.d != INF);	// 물고기를 찾은 동안 진행될 것이다.
	return ret;
}

int main() {
	cin >> N;
	int sr, sc;	// sr : 아기상어의 행, sc : 아기상어의 열
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> Map[i][j];
			if (Map[i][j] == 9) {
				sr = i, sc = j;
				Map[i][j] = 0;
			}
		}
	}
	cout << solve(sr, sc) << "\n";
	return 0;
}