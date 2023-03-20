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
	// 시작 조건 설정
	bool visited[20][20] = { false };
	int size = 2, cnt = 2;

	// 하나의 물고기를 찾는 과정
	do {
		Point minPt = { r, c, 0 };
		minPt.d = INF;
		queue<Point> myqueue;
		myqueue.push({ r, c, 0 });
		visited[minPt.r][minPt.c] = true;
		while (!myqueue.empty()) {
			Point curr = myqueue.front();
			myqueue.pop();

			// 
			

			for (int i = 0; i < 4; i++) {
				int nr = curr.r + Dr[i];
				int nc = curr.c + Dr[i];
				if (nr < 0 || nr > N - 1 || nc < 0 || nc > N - 1)continue;
				if (visited[nr][nc] != false)continue;
				visited[nr][nc] = true;
			}
		}
	} while ()
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
}