#include<iostream>
#include<deque>

using namespace std;

int main() {
	deque<int> DQ;
	DQ.push_front(10);
	DQ.push_back(50);
	DQ.push_front(24);
	for (auto x : DQ) cout << x << " ";
	cout << DQ.size() << "\n";
	if (DQ.empty()) cout << "DQ is empty\n";
	else cout << "DQ is not empty\n";
	DQ.pop_front();
	DQ.pop_back();
	cout << DQ.back() << "\n";
	DQ.push_back(72);				// 10 72
	cout << DQ.front() << "\n";
	DQ.push_back(12);				// 10 72 12
	DQ[2] = 17;	// deque는 인덱스로 접근이 가능하다.	// 10 72 17
	DQ.insert(DQ.begin() + 1, 33);	// 10 33 72 17
	DQ.insert(DQ.begin() + 4, 60);	// 10 33 72 17 60
	for (auto x : DQ) cout << x << " ";
	cout << "\n";
	DQ.erase(DQ.begin() + 3);		// 10 33 72 60
	cout << DQ[3] << "\n";			// 60
	DQ.clear();

	return 0;
}