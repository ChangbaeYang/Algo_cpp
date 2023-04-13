#include<iostream>
#include<queue>
using namespace std;

int main() {
	queue<int> Q;
	Q.push(10);	// 10
	Q.push(20);	// 10 20
	Q.push(30);	// 10 20 30
	cout << Q.size() << "\n";
	if (Q.empty()) cout << "Q is empty\n";
	else cout << "Q is not empty\n";
	Q.pop();
	cout << Q.front() << "\n";
	cout << Q.back() << "\n";
	Q.push(40);
	Q.pop();
	cout << Q.front() << "\n";

	return 0;
	// ** 주의 사항 ** //
	// Queue가 비어져있는데 back이나 pop을 호출하지 않도록하자.
}