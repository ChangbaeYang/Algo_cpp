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
	// �����
	int ret = 0;
	// ��� ����
	int size = 2, cnt = 2;
	Point minPt = { r, c, 0 };

	// �ϳ��� ����⸦ ã�� ����
	do {
		bool visited[20][20] = { false };
		queue<Point> myqueue;					// ť�����
		myqueue.push({ minPt.r, minPt.c, 0 });	// ť�� ù��° �� �ֱ�
		visited[minPt.r][minPt.c] = true;		// ó�� �� �湮ó��
		minPt.d = INF;

		while (!myqueue.empty()) {
			Point curr = myqueue.front();
			myqueue.pop();
			// �̹� �ּ� �Ÿ� ���� �� ���
			if (minPt.d < curr.d) break;
			// ����Ⱑ �Ʊ���� ũ�ٸ� ���� ����
			if (Map[curr.r][curr.c] > size)continue;
			// ����Ⱑ �ִ� ���
			if (Map[curr.r][curr.c] != 0 && Map[curr.r][curr.c] < size) {
				// ����� �� ����
				if (curr.d < minPt.d) {
					minPt = curr;
				}
				// ���� �Ÿ�
				else if (curr.d == minPt.d) {
					if (curr.r < minPt.r) {
						minPt = curr;
					}
					// ���ʿ� �ִ� �� ����
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
		// ���� �������� ���� ����� ����⸦ ã�����
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
	int sr, sc;		// sr : ����� ����ġ, sc : ����� ����ġ
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