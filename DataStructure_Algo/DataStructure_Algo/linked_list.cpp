#include<iostream>
using namespace std;

class Node {
public:
	int data;
	Node* next;
};

class LinkedList {
	Node* head;
	// 첫 연결리스트 구현
	LinkedList() {
		head = NULL;
	}

	void insert(int data) {
		Node* newNode = new Node();
		newNode->data = data;
		newNode->next = NULL;
	
		if (head == NULL) {
			head = newNode;
		}
		else {
			Node* curr = head;
			while (curr->next != NULL) {
				curr = curr->next;
			}
			curr->next - newNode;
		}
	}

	void remove(int data) {
		if (head == NULL) {
			return;
		}
		if (head->data == data) {

		}
	}
};