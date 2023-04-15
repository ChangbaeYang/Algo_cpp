#include<iostream>
#include<vector>

using namespace std;

int main() {

	vector<int> v(3, 5);	// {5, 5, 5}
	cout << v.size() << "\n";
	v.push_back(7);			// {5, 5, 5, 7}

	vector<int> v2(2);		// {0, 0}
	v2.insert(v2.begin() + 1, 3);	// {0, 3, 0}

	vector<int> v3 = { 1, 2, 3, 4 };
	v3.erase(v3.begin() + 2);

	vector<int> v4;	// {}
	v4 = v3;	//{1, 2, 4}
	cout << v4[0] << v4[1] << v4[2] << "\n";
	v4.pop_back();	// {1, 2}
	v4.clear();


	vector<int> v1 = { 1, 2, 3, 4, 5, 6 };

	// 1. range-based for loop (since C++11)
	for (int e : v1)
		cout << e << " ";

	// 2. not bad
	for (int i = 0; i < v1.size(); i++)
		cout << v1[i] << " ";

	// 3. ***wrong***
	for (int i = 0; i <= v1.size() - 1; i++)
		cout << v1[i] << " ";
}