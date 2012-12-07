#include<iostream>
#include<vector>

int n;
const int maxn = 305;

bool E[maxn][maxn];

int prev[maxn];
bool was[maxn];

int dfs(int x, int from = -1) {
  if(was[x]) return -1;
  was[x] = true;
  prev[x] = from;
  for(int i=0; i<n; i++) {
    if(E[x][i]) {
      int dfs(i,x);
    }
  }
}

int go() {
  for(int i=0; i<n; i++) {
    int x = dfs(i);
    if(x != -1) {
      popraw(x);
    }
  }
}

int main() {
  int t;
  cin >> t;
  while(t--) {
    cin >> n;
    for(int i=0; i<n ;i++) {
      char tmp[maxn];
      cin >> tmp;
      for(int j=0; j<n; j++) E[i][j] = (tmp[j] == '1');

      int x = go();
      if(x % 2 == 1) cerr << "Odd\n";
      else cerr << "Even";
    }
  }
  return 0;
}
