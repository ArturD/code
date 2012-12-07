#include<iostream>
#include<vector>

using namespace std;
int n,s,k;
const int maxn = 100005;
const int maxk = 22;
vector<int> next[maxn];
int B[maxn][maxk]; // sale bez gasnicy
int W[maxn][maxk]; // wolne koncowki
int wyn;
vector<int> S;
int was[maxn];
void dfs(int start) {
  S.push_back(start);
  while(!S.empty()) {
    int cur = S[S.size()-1];
    S.pop_back();
    if(cur>0) {
      was[cur] = 1;
      S.push_back(-cur);
      for(int i=0; i<next[cur].size(); i++) {
        if(!was[next[cur][i]])
          S.push_back(next[cur][i]);
      }
    } else {
      cur = -cur;
      was[cur] = 2;
      for(int i=0; i<next[cur].size(); i++)
        if(was[next[cur][i]] == 2) {
          for(int ik=0; ik<k; ik++) {
            B[cur][ik+1] += B[next[cur][i]][ik];
            W[cur][ik+1] += W[next[cur][i]][ik];
          }
        }
      B[cur][0] = 1;
      for(int i=k; i>-1; i--) {
        int t = min(W[cur][k-i], B[cur][i]);
        B[cur][i] -= t;
        W[cur][k-i] -= t;
        if(t) cerr << cur << " używa " << t << endl;
      }
      for(int i=k; i>0; i--) {
        int t = min(W[cur][k-i-1], B[cur][i]);
        B[cur][i] -= t;
        W[cur][k-i-1] -= t;
        if(t) cerr << cur << " używa_b " << t << endl;
      }
      int ss = (B[cur][k]+s-1)/s;
      wyn += ss;
      int gas = ss*s;
      if(ss)cerr << " cof " << cur << " wstawiam " << ss << endl;
      //cerr << "     " << W[cur][k] << ":" << B[cur][k] << "" << endl;
      

      int t = min(gas, B[cur][k]);
      B[cur][k] -= t;
      W[cur][0] += gas - t;
       
      for(int i=0; i>-1; i--) {
        t = min(W[cur][k], B[cur][i]);
        B[cur][i] -= t;
        W[cur][k] -= t;

        t = min(W[cur][k-1], B[cur][i]);
        B[cur][i] -= t;
        W[cur][k-1] -= t;
      }
        //if(t) cerr << cur << " używa_c " << t << endl;
      /*
      if(cur == 9)
        cerr << " 9 zostawia " << W[cur][0] << endl;
      if(cur == 12)
        cerr << " 12 zostawia " << W[cur][0] << endl;
      */
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> n>> s >>k;
  for(int i=1; i<n; i++) {
    int a,b;
    cin >>a>>b;
    next[a].push_back(b);
    next[b].push_back(a);
  }
  const int start = 1;  
  dfs(start);
  int rest = 0;
  for(int i=k; i>-1; i--)
  {
    if(i!=k) W[start][k-i] += W[start][k-i-1];
    int t = min(W[start][k-i], B[start][i]);
    B[start][i] -= t;
    W[start][k-i] -= t;

    rest += B[start][i];
  }
  int t = (rest+s-1) / s;
  cerr << wyn << ":" << t << endl;
  cout << (wyn+t) << endl;
  return 0;
}
