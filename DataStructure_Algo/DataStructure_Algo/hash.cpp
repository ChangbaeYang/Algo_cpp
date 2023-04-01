#include<iostream>
#define MAX_KEY 64		//	최대 64개 문자열(key)
#define MAX_DATA 128	//  최대 128개 문자열(data)
#define MAX_TABLE 4096	// q개의 키를 입력받아 해당하는 data
using namespace std;

struct Hash {
	char key[MAX_KEY + 1];		// 문자형 64
	char data[MAX_DATA + 1];	// 문자형 128
};
Hash tb[MAX_TABLE];

unsigned long hash(const char* str) {
	unsigned long hash = 5381;
	int c;
	while (c = *str++) {
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}
	return hash % MAX_TABLE;
}

int find(const char* key, char* data) {
	unsigned long h = hash(key);

}

int add(const char* key, char* data) {
	unsigned long h = hash(key);

}

int main() {
	int T, N, Q;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		memset(tb, 0, sizeof(tb));
		cin >> N;
		char k[MAX_KEY + 1];
		char d[MAX_DATA + 1];
		
		for (int i = 0; i < N; i++) {
			cin >> k >> d;
			add(k, d);
		}
		cout << "#" << tc << " ";
		cin >> Q;

	}
}