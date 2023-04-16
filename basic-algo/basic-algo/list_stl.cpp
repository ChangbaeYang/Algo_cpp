#include<iostream>
#include<list>
using namespace std;


int main() {
	list<int> L = { 1, 2 }; // 1 2
	list<int>::iterator t = L.begin();	// t�� 1�� ����Ŵ
	L.push_front(10);	// 10 1 2 O(1)
	cout << *t << "\n";	// t�� ����Ű�� �� = 1�� ���
	L.push_back(5);		// 10 1 2 5 O(1)
	L.insert(t, 6);		// t�� ����Ű�� ���� 6 ����
	cout << *t << "\n";
	t++;	// t�� 1ĭ ������ ����. t�� ����Ű�� �� 2
	t = L.erase(t);	// t�� ����Ű�� �� ����, �״��� ������ 5�� ��ġ�� ��ȯ
	
	cout << *t << "\n"; // 5
	for (auto i : L) cout << i << " ";
	cout << "\n";
	for (list<int>::iterator it = L.begin(); it != L.end(); it++)
		cout << *it << " ";
	
}	