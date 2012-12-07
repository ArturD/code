#include<iostream>
#include<algorithm>
using namespace std;

typedef long long ll;

const int maxn = 500005;
ll TAB[maxn];
ll d,m;
int n;

int main() {
  cin >> d >> m >> n;
  if(n> 20) return 1;
  for(int i=0; i<n; i++) cin >> TAB[i];
  sort(TAB,TAB+n);
  
  int best = n+1;
  do {
    ll pos = 0;
    for(int i=0; i<n; i++) {
      ll t = TAB[i] - abs(pos-m);
      if(t > 0) {
        pos += t;
      }
      if(pos >= d) {
        if(i+1 < best) {
          best = i+1;
          break;
        }
      }
    }
  } while(next_permutation(TAB, TAB+n));

  if(best == n+1) best = 0;
  cout << best << endl;
  return 0;
}
