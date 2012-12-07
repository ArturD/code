#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;

const int maxn = 42;
const int maxp = maxn*maxn/2;

int DP[maxp][maxn][maxn];
int Epoch[maxp][maxn][maxn];
int C[maxn];
int C_max;
int e,n;
long long FACT[maxn][maxn];
long long fact(int pp, int jj) {
        if(FACT[pp][jj] != -1) return FACT[pp][jj];
        long long ff = 1;
        int fdiv = 1;
        //for(int f=1; f<=jj; f++) ff/=f;
        for(int f = pp+1; f<=pp+jj; f++) {
          long long backup = ff;
          ff*=f;
          if(ff/f != backup) cerr << "WARN !" << ff << " "  << f << " " << backup <<endl;
          while(fdiv <= jj && ff%fdiv == 0) { ff/=fdiv++; }
          if(fdiv>jj) { ff %= 1000000007; }
  
        }
        FACT[pp][jj] = ff;
        return ff;
}
long long get(int used, int level, int pos, int ctotal) {
  if(used + (n-pos)*level > n*(n-1)/2) return 0;
  if(Epoch[used][level][pos] == e) return DP[used][level][pos];
  long long result = 0;
  if(used < pos*(pos-1)/2) {
    result = 0;
  } else if(pos == n) {
    //cerr << "C_max" << C_max << endl;
    if(used == n*(n-1)/2 && level > C_max) result =  1;
    else result = 0;
  } else {
    for(int i=level; i<n; i++) {
      int jump = 1;
      jump = max(jump, C[i]);
      //if(n==2) cerr << " jump" << jump << endl;
      for(jump; pos+jump <= n; jump++) {
        long long rr = get(used+jump*i, i+1, pos+jump, ctotal+C[i]);
        int jj = jump - C[i];
        int pp = pos - ctotal;
        //if(n == 3) {  cerr << "pos = " << pos << " jj=" << jj << " ff " << ff << endl; }
        result +=rr * fact(pp,jj);
        result %= 1000000007;
      }
      //if(n==2) cerr << " result" << result << endl;
      if(C[i]) break; // must use !!
    }
  }

  //if(n==4)cerr << used << " " << level << " " << pos  << " = " << result << endl;
  result %= 1000000007;
  Epoch[used][level][pos] = e;
  DP[used][level][pos] = result;
  return result;
}

int main() {
  for(int i=0; i<maxn; i++)
    for(int j=0; j<maxn; j++) FACT[i][j] = -1;
  //cerr << fact(40,20) << endl;
  int t;
  scanf("%d", &t);
  for(e = 1; e<=t ;e++) {
    memset(C, 0, sizeof(int) * maxn);
    scanf("%d", &n);
    C_max = 0;
    for(int i=0; i<n; i++) {
      int x;
      scanf("%d", &x);
      if(x!=-1) C[x]++;
      C_max = max(C_max, x);
    }
    int result = get(0,0,0,0);
    printf("%d\n",  result);
  }
  return 0;
}
