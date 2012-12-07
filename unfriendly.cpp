#include<cstdio>
#include<vector>
#include<cmath>
#include<iostream>
using namespace std;
#define PB push_back
typedef long long ll;
vector<int> primes;

const int maxp = 3200000;
int div2[maxp];

void compute_primes(int mx) {
  primes.PB(2);
  for(int c=3; c<=mx; c+=2) {
    bool isprime = true;
    for(int i=0; primes[i] < sqrt(c); i++) {
      if(i>=primes.size()) cerr << "zonk!" << endl;
      if(c%primes[i] == 0) { div2[c] = primes[i]; isprime = false; break; }
    }
    if(isprime) primes.PB(c);
  }
}

ll gcd(ll a, ll b) {
  while(true) {
    a %= b;
    if(a == 0) return b;
    b %= a;
    if(b == 0) return a;
  }
}

vector<int> P,T,TT;

int Q[1000000];

int index(ll x) {
  ll xxx = x;
  int ix = 0;
  for(int i=0; i<T.size(); i++) {
    int t = 0;
    while(x % P[i] == 0 && x) {
      x /= P[i];
      t++;
    }
    ix += t*TT[i];
  }
  //cerr << " index " << xxx << " : " << ix << endl;
  return ix;
}

int count(int x) {
  // cerr << "  count " << x << endl;
  if(x == 0) return 0;
  if(Q[x]) return 0;
  Q[x] = 1;
  int total = 1;
  int xx = x;
  for(int i=T.size()-1; i>=0 ;i--) {
    if(xx >= TT[i]) {
      xx %= TT[i];
      total += count(x-TT[i]);
    }
  }
  //cerr << " count : " << x << " : " << total << endl;
  return total;
}

int main () {
  long long n, k;
  scanf("%lld%lld",&n,&k);
  compute_primes(sqrt(k)+1);
  
  ll kk = k;
  int tt = 1;
  for(int i=0; i<primes.size() ;i++) {
    int t = 0;
    while(kk % primes[i] == 0 && kk) {
      kk /= primes[i];
      t++;
    }
    if(t) {
      T.PB(t);
      P.PB(primes[i]);
      //cerr << "tt" << tt << endl;
      TT.PB(tt);
      tt *= t+1;
    }
  }
  for(int i=0; i<n ;i++) {
    ll un;
    scanf("%lld", &un);
    un = gcd(un, k);
    //cerr << un << " - " << k << endl;
    
    int idx = index(un);
    count(idx);
  }
  printf("%d\n", count(index(k)));
  return 0;
}
