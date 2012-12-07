#include<vector>
#include<cmath>
#include<iostream>
using namespace std;
#define PB push_back
typedef long long ll;
vector<int> primes;

const int maxp = 3200000;

void compute_primes(int mx) {
  primes.PB(2);
  for(int c=3; c<=mx; c+=2) {
    bool isprime = true;
    for(int i=0; primes[i] <= sqrt(c) + 0.0000001; i++) {
      if(i>=primes.size()) cerr << "zonk!" << endl;
      if(c%primes[i] == 0) { isprime = false; break; }
    }
    if(isprime) primes.PB(c);
  }
}

int main () {
  ll n;
  cin >> n;
  compute_primes(n + 100);
 
  ll res = 1;
  for(int i=0; i<primes.size(); i++) {
    ll x = 0;
    ll nn = n;
    while(nn) {
      nn /= primes[i];
      x += nn;
    }
    res *= (x*2+1);
    res %= 1000007;
  }
  cout << res << endl;
  return 0;
}
