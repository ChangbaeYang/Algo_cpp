#include<iostream>
#include<queue>

using namespace std;

#define INF 987654321

// d는 포인트까지 이동하기 위한 거리
struct Point {
	int r, c, d;	// 멤버변수, c++ 구조체는 public이 디폴트 접근 지정으로 되어있다.
};

int N;
int Map[20][20];
int Dr[4] = {-1, 1, 0, 0}; // 상하좌우
int Dc[4] = {0, 0, -1, 1}; // 상하좌우

int solve(int r, int c) {
	int ret = 0;
	int size = 2, cnt = 2;
	Point minPt = { r, c, 0 }; // 최초값

	do {
		bool visited[20][20] = { false }; // 선언과 초기화
		queue<Point> myqueue;
		visited[minPt.r][minPt.c] = true;
		myqueue.push({ minPt.r, minPt.c, 0 }); // 최초의 0 - 상어가 이동한 거리
		minPt.d = INF;

		while (!myqueue.empty()) {
			Point curr = myqueue.front();	// 현재 위치의 점
			myqueue.pop();					// 빼주기
			
			if (curr.d > minPt.d) break;	// 더이상 탐색하지 않아도 되는 경우
			// 물고기가 상어보다 크다면
			if (Map[curr.r][curr.c] > size) continue;
			// 먹을 수 있는 고기를 찾은 경우
			if (Map[curr.r][curr.c] != 0 && Map[curr.r][curr.c] < size) {
				if (curr.d < minPt.d) {
					minPt = curr;
				}
				else if (curr.d == minPt.d) {
					// 위쪽부터
					if (curr.r < minPt.r) {
						minPt = curr;
					}
					// 왼쪽부터
					else if (curr.r == minPt.r && curr.c < minPt.c) {
						minPt = curr;
					}
				}
				continue;
			}

			for (int i = 0; i < 4; ++i) {
				int nr = curr.r + Dr[i];
				int nc = curr.c + Dc[i];
				if (nr < 0 || nr > N - 1 || nc < 0 || nc > N - 1)continue;
				if (visited[nr][nc]) continue;
				visited[nr][nc] = true;
				myqueue.push({ nr, nc, curr.d + 1 });
			}
		}

		// 위의 과정에서 물고기를 찾았다면
		if (minPt.d != INF) {
			ret += minPt.d; // 시간 더해주기
			--cnt;
			if (cnt == 0) {
				size++;
				cnt = size;
			}
			Map[minPt.r][minPt.c] = 0;	// 물고기 지워주기
		}

	} while (minPt.d != INF); // 물고기한테 갈 수 없을 때까지

	return ret;
}

int main() {
	cin >> N;
	int sr, sc;	// sr: 상어의 행, sc: 상어의 열
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> Map[i][j];
			if (Map[i][j] == 9) {
				sr = i;
				sc = j;
				Map[i][j] = 0;	// 이동을 용이하게 하기 위함
			}
		}
	}
	cout << solve(sr, sc) << "\n";
	return 0;
}