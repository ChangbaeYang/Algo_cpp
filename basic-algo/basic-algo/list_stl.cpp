#include<iostream>
#include<list>
using namespace std;


int main() {
	list<int> L = { 1, 2 }; // 1 2
	list<int>::iterator t = L.begin();	// t는 1을 가르킴
	L.push_front(10);	// 10 1 2 O(1)
	cout << *t << "\n";	// t가 가리키는 값 = 1을 출력
	L.push_back(5);		// 10 1 2 5 O(1)
	L.insert(t, 6);		// t가 가리키는 곳에 6 삽입
	cout << *t << "\n";
	t++;	// t를 1칸 앞으로 전진. t가 가리키는 값 2
	t = L.erase(t);	// t가 가리키는 값 제거, 그다음 원소인 5의 위치를 반환
	
	cout << *t << "\n"; // 5
	for (auto i : L) cout << i << " ";
	cout << "\n";
	for (list<int>::iterator it = L.begin(); it != L.end(); it++)
		cout << *it << " ";
	
}	