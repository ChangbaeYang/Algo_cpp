#include<iostream>
#define MAX_NODE_NUM 10000
#define MAX_CHILD_NUM 2

using namespace std;

int N;	// ����� ����
int E;	// ������ ����(��� ������ ����)
int root;	// ��Ʈ ��� ����

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
		// ���̻� �θ� ���ٸ� -1�� �����
		if (tree[i].parent == -1) {
			return i;
		}
	}
	return -1;
}

// ã�� root���� �������� ���� ��ȸ
void preOrder(int root) {
	int child;
	cout << root << " ";
	for (int i = 0; i < MAX_CHILD_NUM; i++) {
		child = tree[root].child[i];
		if (child != -1) {
			preOrder(child);	// ��������� child�� root�� �ؼ� Ÿ�� ����
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
		initTree();	// Ʈ�� ����
		// Ʈ���� ���� ����ֱ�
		for (int i = 0; i < E; i++) {
			cin >> parent >> child;
			addChild(parent, child);	// parent-child �̾��ֱ�
		}
		root = getRoot();
		cout << "#" << tc << " ";
		preOrder(root);
		cout << "\n";
	}
	return 0;
}