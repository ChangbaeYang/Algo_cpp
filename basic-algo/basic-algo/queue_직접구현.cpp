#include<iostream>
using namespace std;

const int MX = 1000005;
int dat[MX];
int head = 0, tail = 0;	// tail�� ������ �ε��� + 1
// dat[head]���� dat[tail-1]������ ť�� ���ҵ��� ����ִ� �ڸ�
// ť�� ũ�� : tail - head
// ����: ť�� �� ������ ����ؼ� ���Եȴ�.
// �̷� ������ �ذ��ϱ� ���ؼ� tail+1�� MX�� �� ��, 0���� ���ƿ�������
// -> ���� ť(Circular Queue)(���� ���� �� ���� ť��)

void push(int x) {
	dat[tail++] = x;
}
void pop() {
	head++;
}
int front() {
	return dat[head];
}
int back() {
	return dat[tail - 1];
}

int main() {

}