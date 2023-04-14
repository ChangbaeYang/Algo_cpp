#include<iostream>
using namespace std;

int a[4];

int main() {
	int b[4];
	for (int i = 0; i < 4; i++)
		cout << a[i] << " ";
	cout << "\n";
	for (int i = 0; i < 4; i++)
		cout << b[i] << " ";
}