#include<iostream>

using namespace std;
int n,k;
const int maxn = 100002;
typedef long long ll;
ll N[maxn], S[maxn];
ll Q[maxn], V[maxn];
int main() {
  ios_base::sync_with_stdio(false);
  cin >> n >> k;
  for(int i=1; i<=n; i++) {
    cin >> N[i];
    S[i] = N[i];
    S[i] += S[i-1];
  }
  int qi =0, qj = 1;
  for(int i=1; i<=n; i++) {
    ll best = 0;
    if(Q[qi] < i-k-1) qi++;
    //for(int x=qi; x<qj; x++) cerr << Q[x] << " "; cerr << endl;
    
    ll diff = S[i-1] - S[Q[qi]];
    best = V[Q[qi]] + diff;
    V[i] = best;
    /*
    cerr << i << " : " << best << endl;
    cerr << " Q[qi]=" << Q[qi] << endl;
    cerr << "   V[Q[qi]]  = " << V[Q[qi]] << endl;
    cerr << "   diff = " << diff << endl;
    cerr << "   S[Q[i]] = " << S[Q[i]] << endl;
    */
    while(qi<qj && best >= S[i] - S[Q[qj-1]] + V[Q[qj-1]]) { qj--; }
    Q[qj++] = i;
  }
  
  if(Q[qi] < n-k) qi++;
  cout << V[Q[qi]] + S[n] - S[Q[qi]] << endl;
  return 0;
}
