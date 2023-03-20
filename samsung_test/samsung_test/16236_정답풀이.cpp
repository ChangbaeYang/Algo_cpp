#include<iostream>
#include<queue>

using namespace std;

#define INF 987654321

// d�� ����Ʈ���� �̵��ϱ� ���� �Ÿ�
struct Point {
	int r, c, d;	// �������, c++ ����ü�� public�� ����Ʈ ���� �������� �Ǿ��ִ�.
};

int N;
int Map[20][20];
int Dr[4] = {-1, 1, 0, 0}; // �����¿�
int Dc[4] = {0, 0, -1, 1}; // �����¿�

int solve(int r, int c) {
	int ret = 0;
	int size = 2, cnt = 2;
	Point minPt = { r, c, 0 }; // ���ʰ�

	do {
		bool visited[20][20] = { false }; // ����� �ʱ�ȭ
		queue<Point> myqueue;
		visited[minPt.r][minPt.c] = true;
		myqueue.push({ minPt.r, minPt.c, 0 }); // ������ 0 - �� �̵��� �Ÿ�
		minPt.d = INF;

		while (!myqueue.empty()) {
			Point curr = myqueue.front();	// ���� ��ġ�� ��
			myqueue.pop();					// ���ֱ�
			
			if (curr.d > minPt.d) break;	// ���̻� Ž������ �ʾƵ� �Ǵ� ���
			// ����Ⱑ ���� ũ�ٸ�
			if (Map[curr.r][curr.c] > size) continue;
			// ���� �� �ִ� ��⸦ ã�� ���
			if (Map[curr.r][curr.c] != 0 && Map[curr.r][curr.c] < size) {
				if (curr.d < minPt.d) {
					minPt = curr;
				}
				else if (curr.d == minPt.d) {
					// ���ʺ���
					if (curr.r < minPt.r) {
						minPt = curr;
					}
					// ���ʺ���
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

		// ���� �������� ����⸦ ã�Ҵٸ�
		if (minPt.d != INF) {
			ret += minPt.d; // �ð� �����ֱ�
			--cnt;
			if (cnt == 0) {
				size++;
				cnt = size;
			}
			Map[minPt.r][minPt.c] = 0;	// ����� �����ֱ�
		}

	} while (minPt.d != INF); // ��������� �� �� ���� ������

	return ret;
}

int main() {
	cin >> N;
	int sr, sc;	// sr: ����� ��, sc: ����� ��
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> Map[i][j];
			if (Map[i][j] == 9) {
				sr = i;
				sc = j;
				Map[i][j] = 0;	// �̵��� �����ϰ� �ϱ� ����
			}
		}
	}
	cout << solve(sr, sc) << "\n";
	return 0;
}