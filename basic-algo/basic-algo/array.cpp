#include<iostream>
using namespace std;

void insert(int idx, int num, int arr[], int& len) {
	for (int i = len; i > idx; i--) {
		arr[i] = arr[i - 1];
	}
	arr[idx] = num;
	len++;
}

void erase(int idx, int arr[], int& len) {
	len--;
	for (int i = idx; i < len; i++) {
		arr[i] = arr[i + 1];
	}
}

int main() {
	int arr[10] = { 10, 50, 40, 30, 70, 20 };
	int len = 6;
	insert(3, 60, arr, len);	// 10 50 40 60 30 70 20
	erase(4, arr, len);	// 10 50 40 60 70 20
	
	int a[21];
	int b[21][21];

	// 1.memset
	memset(a, 0, sizeof a);
	memset(b, 0, sizeof b);

	// 2.for
	for (int i = 0; i < 21; i++) {
		a[i] = 0;
	}
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			b[i][j] = 0;
		}
	}

	// 3. fill
	fill(a, a + 21, 0);
	for (int i = 0; i < 21; i++) {
		fill(b[i], b[i] + 21, 0);
	}
}