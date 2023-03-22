#include<iostream>
#include<queue>
#define INF 987654321
using namespace std;

// �Ʊ��� �ʱ�ũ�� 2
// 1�ʿ� ��ȭ�¿� ������ �� ĭ�� �̵� *
// �ڽź��� ū ����� �������� *
// �ڽ� ũ�⺸�� ���� ����⸸ ���� �� ���� *
// ����� 1���� -> �� ����� *
// ����� ��������, ���� ����� ����� ���� *
// ����� ����� ���� �� -> ���� �� ����� -> ���� ���� ����� *
// ����⸦ ������ �ش� ĭ�� ��ĭ�� �ȴ�. *

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
	// ����� �ʱ� ������� �Ծ���ϴ� ���
	int size = 2, cnt = 2;
	// ������ ��
	Point minPt = { r, c, 0 };

	// ����⸦ ��ã�� ������ �ݺ��ؾ��Ѵ�.
	// ����⸦ ��ã�Ҵٴ� ���� -> minPt.d(�Ÿ��� ���Ѵ��� ���)
	do {
		// BFS�� �����Ѵ�.
		bool visited[20][20] = { false };	// ����⸦ ã�� ������ visited �ʱ�ȭ
		queue<Point> myqueue;
		myqueue.push({ minPt.r, minPt.c, 0 });	// ������ ���� ť�� �ִ´�.
		visited[minPt.r][minPt.c] = true;		// ������ �� �湮 ó��
		minPt.d = INF;	// �ּҰ��� ���ϱ� ���� �ִ뿡�� �����Ѵ�.
		while (!myqueue.empty()) {
			Point curr = myqueue.front();
			myqueue.pop();
			
			// �ּҰŸ����� ���� �Ÿ��� �� ��� �� �̻� ������ �ʿ䰡 ����
			if (curr.d > minPt.d)break;
			// �ڽź��� ū ����� �� ��� �� �̻� ������ �� ����
			if (Map[curr.r][curr.c] > size)continue;
			// ����⸦ ���� ���
			if (Map[curr.r][curr.c] != 0 &&  Map[curr.r][curr.c] < size) {
				// ����Ⱑ ���� ����� ���
				if (curr.d < minPt.d) {
					minPt = curr;
				}
				// �ش� ����Ⱑ �Ÿ��� ���� ���
				else if (curr.d == minPt.d) {
					// ���� �������� ó��
					if (curr.r < minPt.r) {
						minPt = curr;
					}
					// ���̰� ���� ��� ���� ����� ���� ó��
					else if (curr.r == minPt.r && curr.c < minPt.c) {
						minPt = curr;
					}
				}
				continue;	// ����⸦ �����ٸ� ���̻� �ش� ������ ������� ���� Ȯ���� �ʿ䰡 ����.
			}
			// ���� ���� ã�� ����
			for (int i = 0; i < 4; i++) {
				int nr = curr.r + Dr[i];
				int nc = curr.c + Dc[i];
				if (nr < 0 || nr > N - 1 || nc < 0 || nc > N - 1)continue;
				if (visited[nr][nc] != false)continue;
				myqueue.push({ nr, nc, curr.d + 1 });	// ���� ���� ť�� �ִ´�.(�Ÿ� + 1)
				visited[nr][nc] = true;
			}
		}

		// ����⸦ ã���� ����� �ൿ
		if (minPt.d != INF) {
			ret += minPt.d;
			cnt--;
			if (cnt == 0) {
				size++;
				cnt = size;
			}
			Map[minPt.r][minPt.c] = 0;	// ��⸦ ������ �ش� �ڸ��� 0
		}
	} while (minPt.d != INF);
	return ret;
}

int main() {
	cin >> N;
	int sr, sc;		// sr : ����� ��, sc : ����� ��
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