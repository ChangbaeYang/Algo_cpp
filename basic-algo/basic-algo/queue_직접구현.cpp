#include<iostream>
using namespace std;

const int MX = 1000005;
int dat[MX];
int head = 0, tail = 0;	// tail은 원소의 인덱스 + 1
// dat[head]부터 dat[tail-1]까지가 큐의 원소들이 들어있는 자리
// 큐의 크기 : tail - head
// 문제: 큐의 앞 공간이 계속해서 남게된다.
// 이런 문제를 해결하기 위해서 tail+1이 MX가 될 때, 0으로 돌아오도록함
// -> 원형 큐(Circular Queue)(직접 구현 시 원형 큐로)

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