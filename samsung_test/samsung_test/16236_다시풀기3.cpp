#include<iostream>
#include<queue>
#define INF 987654321

using namespace std;
// N*N ũ���� ������ ����� M����-> M�� ���־��� **
// �Ʊ��� 1���� - �ʱ� ũ�� 2, 1�ʿ� �����¿� **
// ���κ��� ���� ����� ���� **
// ũ�Ⱑ ���� ������ ���� �� ������, ������ �� �ִ�. ** 
// �� ĭ�� ����� �ִ� 1���� **
// ���� �� �ִ� ����� 1 -> �� ����� **
// ����� 1���� ���� ���ٸ� -> ���� ����� ����� **
// ���� ����� ����� ���ٸ� ������ ���� -> ���ʿ��� ���� **
// �Ʊ��� -> ����� �̵��� �� ���������ϴ� ĭ�� ������ �Ÿ� **

int N;
int Map[20][20];
int Dr[4] = { -1, 1, 0, 0 };	// �����¿�
int Dc[4] = { 0, 0, -1, 1 };	// �����¿�

struct Point {
	int r, c, d;	// Point struct�� �������
};

int solve(int r, int c) {
	int ret = 0;
	int size = 2, cnt = 2;
	Point minPt = { r, c, 0 };
	do {
		// BFS ������ Ȱ���� ���̴�.
		bool visited[20][20] = { false };
		queue<Point> myqueue;
		myqueue.push({ minPt.r, minPt.c, 0 });	// ���ŵ� minPt�� ��
		visited[minPt.r][minPt.c] = true;	// �ʱ��� �湮ó��
		minPt.d = INF;	// ó����ġ�� ���Ѵ�� ��´�.
		while (!myqueue.empty()) {
			Point curr = myqueue.front();
			myqueue.pop();

			// ���� ���� �ʹ� �ִٸ�
			if (curr.d > minPt.d)break;	// �� �̻� BFS�� �����ϴ� �ǹ̾���
			// ���� ���� ����Ⱑ ���� ũ�ٸ�
			if (Map[curr.r][curr.c] > size)continue; // ������ �� �����Ƿ� ��Ƽ��
			// ���� ����⸦ ���� �� �ִ� �����
			if (Map[curr.r][curr.c] != 0 && Map[curr.r][curr.c] < size) {
				// ����Ⱑ ������ �ͺ��� ������ �ִ� ���
				if (curr.d < minPt.d) {
					minPt = curr;
				}
				// �Ÿ��� �Ȱ��� ��
				else if (curr.d == minPt.d) {
					// ���� �ִ� ����� ����
					if (curr.r < minPt.r) {
						minPt = curr;
					}
					// ���� ���̰� ���ٸ� ���ʺ���
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
				visited[nr][nc] = true;	// �湮ó��
				myqueue.push({ nr, nc, curr.d + 1 });	// ���� �� ť�� ����
			}
		}

		// ����⸦ ���� ���
		if (minPt.d != INF) {
			ret += minPt.d;
			cnt--;
			if (cnt == 0) {
				size++;
				cnt = size;
			}
			Map[minPt.r][minPt.c] = 0;
		}
	} while (minPt.d != INF);	// ����⸦ ã�� ���� ����� ���̴�.
	return ret;
}

int main() {
	cin >> N;
	int sr, sc;	// sr : �Ʊ����� ��, sc : �Ʊ����� ��
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