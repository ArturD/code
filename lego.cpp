#include<iostream>

using namespace std;

#define rep(i,n) for(int i=0; i<(n); i++)

typedef long long ll;
int maxn = 1001;
ll NM[maxn][maxn];
ll S[maxn];

ll modulo = 1000000007;
void computeS() {
  S[1] = 1;
  S[2] = 2;
  S[3] = 4;
  for(int i = 4; i<1001; i++) {
    rep(x,4) S[i] += S[i-1-x];
    S[i] %= modulo;
  }
}
int main() {

}
