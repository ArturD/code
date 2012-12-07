#include<iostream>
#include<queue>
using namespace std;
int n,m;
const int maxn = 55;
const int maxm = 1005;

int C[maxn][maxn];
int BACK[maxn];

void BFS() {
  for(int i=0; i<n;i++) BACK[i] = -1;
  queue<int> q;
  q.push(0);
  BACK[0] = 0;
  while(!q.empty()) {
    int cur = q.front();
    q.pop();
    for(int i=0; i<n; i++) {
      if(C[cur][i] && BACK[i] == -1) {
        //cerr << "  " << cur << " : " << i << endl;
        BACK[i] = cur;
        q.push(i);
      }
    }
  }
}

int main() {
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int a,b,c;
    cin >> a>> b>> c;
    a--; b--;
    C[a][b] = c;
  }
  int flow = 0;
  while(true) {
    /*
    for(int i=0;i<n; i++) {
      for(int j=0; j<n; j++) cerr << C[i][j] << ' ';
      cerr << endl;
    }
    */
    BFS();

    if(BACK[n-1] == -1) break;
    int minf = 10000;

    for(int i=BACK[n-1],j=n-1; j != 0; j=i,i=BACK[i]) {
      minf = min(minf,C[i][j]);
      //cerr << "(" << j << ", " << i << " : " << C[i][j] << " ), " ;
    }
    //cerr << endl;
    for(int i=BACK[n-1],j=n-1; j != 0; j=i,i=BACK[i]) {
      C[i][j] -= minf;
      C[j][i] += minf;
    }
    flow += minf;
  }
  cout << flow<<endl;
  return 0;
}
