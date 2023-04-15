#include<iostream>
#include<vector>
using namespace std;

// Ư���� ������ �־����� ��
// �ش��� ������ 100�� ���� �� �ִ����� O(N)���� Ȯ���ϱ�
vector<int> V;
int n;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		V.push_back(temp);
	}
	int occur[101] = {};
	for (int i = 0; i < n; i++) {
		if (occur[100 - V[i]] == 1) {
			cout << "100�� ����";
			return 0;
		}
		occur[V[i]]++;
	}
	cout << "100�� ������";
	return 0;
}