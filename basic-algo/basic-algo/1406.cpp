#include<iostream>
#include<list>
using namespace std;

string S;	// ������ ���ڿ�(10�� ����)
int M;		// ��ɾ� ����(1 ~ 50��)
list<char> L;

int main() {
	cin >> S;
	for (char s : S) {
		L.push_back(s);
	}
	auto t = L.end();
	
	cin >> M;
	for (int i = 0; i < M; i++) {
		char temp;
		cin >> temp;
		if (temp == 'L') {
			if (t != L.begin()) t--;
		}
		else if (temp == 'D') {
			if (t != L.end()) t++;
		}
		else if (temp == 'B') {
			if (t == L.begin())continue;
			t--;
			t = L.erase(t);
		}
		else if (temp == 'P') {
			char temc;
			cin >> temc;
			L.insert(t, temc);
		}
	}
	for (auto it = L.begin(); it != L.end(); it++)
		cout << *it;
	return 0;
}