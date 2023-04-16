#include<iostream>
using namespace std;

const int MX = 1000005;
int dat[MX], pre[MX], nxt[MX];
int	unused = 1;

void insert(int addr, int num) {
	dat[unused] = num;		// �ش� ĭ�� ���� �ֱ�
	pre[unused] = addr;		// ���� �����Ϳ� addr�ֱ�
	nxt[unused] = nxt[addr];
	if (nxt[addr] != -1) pre[nxt[addr]] = unused;
	nxt[addr] = unused;
	unused++;
}

void insert_test() {
	cout << "***** insert_test *****\n";
	insert(0, 10);	// 10(address=1)
}

int main() {
	fill(pre, pre + MX, -1);
	fill(nxt, nxt + MX, -1);
	insert_test();
	erase_test();
}