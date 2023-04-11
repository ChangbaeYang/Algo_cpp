#include<iostream>
using namespace std;

int func1(int N) {
	int ret = 0;
	for (int i = 1; i <= N; i++) {
		if (i % 3 == 0 || i % 5 == 0) ret += i;
	}
	return ret;
}

int func2(int arr[], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (arr[i] + arr[j] == 100) return 1;
		}
	}
	return 0;
}

int func3(int N) {
	for (int i = 1; i * i < N; i++) {
		if (i * i == N) return 1;
	}
	return 0;
}


int main() {
	int a = func1(34567);
	cout << "a : " << a << "\n";
	int bin[3] = { 1, 52, 48 };
	int b = func2(bin, 3);
	cout << "b : " << b << "\n";

}

