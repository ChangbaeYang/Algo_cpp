#include<iostream>
using namespace std;

int big(int a, int b) {
	if (a > b) return a;
	else return b;
}

// 배열 a중에서 제일 큰 수 리턴
int big(int a[], int size) {
	int res = a[0];
	for (int i = 0; i < size; i++) {
		if (res < a[i]) {
			res = a[i];
		}
	}
	return res;
}

int main() {
	int array[5] = { 1, 9, -2, 8, 6 };
	cout << big(2, 3) << "\n";
	cout << big(array, 5) << "\n";
	return 0;
}