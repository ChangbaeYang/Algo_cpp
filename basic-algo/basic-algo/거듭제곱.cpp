#include<iostream>
using ll = long long;

using namespace std;

ll func1(ll a, ll b, ll m) {
	ll val = 1;
	while (b--) val = val * a % m;
	return val;
}

// a^b�� m���� ���� �������� ���ض�
int main() {

}