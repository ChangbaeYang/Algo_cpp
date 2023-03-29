#include<iostream>
#define MAX_NODE_NUM 10000
#define MAX_CHILD_NUM 2

using namespace std;

int N;	// 노드의 갯수
int E;	// 엣지의 갯수(노드 사이의 연결)
int root;	// 루트 노드 설정

struct TreeNode {
	int parent;
	int child[MAX_CHILD_NUM];
};

TreeNode tree[MAX_NODE_NUM];

void initTree() {
	int i;
	int j;
	for (i = 0; i <= N; i++) {
		tree[i].parent = -1;
		for (j = 0; j < MAX_CHILD_NUM; j++) {
			tree[i].child[j] = -1;
		}
	}
}

void addChild(int parent, int child) {
	int i;
	for (i = 0; i < MAX_CHILD_NUM; i++) {
		if (tree[parent].child[i] == -1)break;
	}
	tree[parent].child[i] = child;   
	tree[child].parent = parent;
}

int getRoot() {
	for (int i = 1; i <= N; i++) {
		// 더이상 부모가 없다면 -1을 내뱉기
		if (tree[i].parent == -1) {
			return i;
		}
	}
	return -1;
}

// 찾은 root값을 바탕으로 전위 순회
void preOrder(int root) {
	int child;
	cout << root << " ";
	for (int i = 0; i < MAX_CHILD_NUM; i++) {
		child = tree[root].child[i];
		if (child != -1) {
			preOrder(child);	// 재귀적으로 child를 root로 해서 타고 들어가기
		}
	}
}

int main() {
	int T;
	int parent;
	int child;

	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> N >> E;
		initTree();	// 트리 생성
		// 트리에 값을 집어넣기
		for (int i = 0; i < E; i++) {
			cin >> parent >> child;
			addChild(parent, child);	// parent-child 이어주기
		}
		root = getRoot();
		cout << "#" << tc << " ";
		preOrder(root);
		cout << "\n";
	}
	return 0;
}