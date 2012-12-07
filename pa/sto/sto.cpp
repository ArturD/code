#include<iostream>

using namespace std;
typedef long long ll;

ll test(ll a, ll b) {
  if(a>b) swap(a,b);
  if(a == 0) return 0;
  if(a == 1) return b;
  return b*2 + (a-2)*2;
}

int main() {
  ll a,b,k;
  cin >> a >> b >> k;
  cout << test(a/k, b/k) << endl;
  return 0;
}
