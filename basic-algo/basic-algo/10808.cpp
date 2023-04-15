#include<iostream>

using namespace std;
int a[26];

int main() {
	string S;
	cin >> S;
	for (char s : S) {
		a[s - 'a']++;
	}
	for (int i = 0; i < 26; i++)
		cout << a[i] << " ";
	
	return 0;
}