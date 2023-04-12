#include<iostream>
#include<stack>
using namespace std;

int n;
int temp;
string ret;
stack<int> S;

int main() {
	cin >> n;
	int cnt = 1;
	while (n--) {
		cin >> temp;
		if (S.empty() || temp > S.top()) {
			S.push(cnt);
			cnt++;
			ret += "+\n";
			while (temp != S.top()) {
				S.push(cnt);
				cnt++;
				ret += "+\n";
			}
			S.pop();
			ret += "-\n";
		}
		else if (temp == S.top()) {
			S.pop();
			ret += "-\n";
		}
		else {
			cout << "NO\n";
			return 0;
		}
	}
	cout << ret;
	return 0;
}