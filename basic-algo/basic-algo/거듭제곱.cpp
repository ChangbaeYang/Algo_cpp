#include<iostream>
using ll = long long;

using namespace std;

ll func1(ll a, ll b, ll m) {
	ll val = 1;
	while (b--) val = val * a % m;
	return val;
}

// a^b를 m으로 나눈 나머지를 구해라
int main() {

}