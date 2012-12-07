#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef pair<char,int> PPI;
typedef pair<int,int> PII;
const int maxn = 405;
int n,m;
int inf = 500;
vector<PPI> next[maxn],prev[maxn];
int  COST[maxn][maxn];
char CHAR[maxn][maxn];
PII  PAIR[maxn][maxn];

char TAB[maxn];

int main() {
  cin >> n >> m;
  for(int i=0; i<m;i++) {
    int a,b;
    char c;
    cin >> a >> b >> c;
    a--;
    b--;
    next[a].push_back(PPI(c,b));
    prev[b].push_back(PPI(c,a));
  }
  for(int i=0;i<n;i++) {
    sort(next[i].begin(), next[i].end());
    sort(prev[i].begin(), prev[i].end());
  }
  for(int i=0;i<n;i++) {
    for(int j=0;j<n;j++) {
      COST[i][j] = inf;
    }
  }
  queue<PII> Q;
  for(int i=0; i<n; i++) {
    COST[i][i] = 0;
    Q.push(PII(i,i));
  }
  for(int i=0; i<n; i++) {
    for(int j=0;j<next[i].size(); j++) {
      COST[i][next[i][j].second] = 1;
      CHAR[i][next[i][j].second] = next[i][j].first;
      Q.push(PII(i,next[i][j].second));
    }
  }
  while(!Q.empty()) {
    PII akt = Q.front();
    Q.pop();
    int from = akt.first;
    int to   = akt.second;
    
    int ip = 0;
    for(int i = 0; i<next[to].size(); i++) {
      char litera = next[to][i].first;
      while(ip < prev[from].size() && 
        prev[from][ip].first < litera) ip++;
      if(ip == prev[from].size() || prev[from][ip].first != litera) continue;
      for(int ii =i; ii<next[to].size() && next[to][ii].first == litera; ii++) {
        for(int iip =ip; iip<prev[from].size() && prev[from][iip].first == litera; iip++) {
          int cost = COST[from][to] + 2;
          int nfrom = prev[from][iip].second;
          int nto   = next[to][ii].second;
          if(COST[nfrom][nto] > cost) {
            COST[nfrom][nto] = cost;
            CHAR[nfrom][nto] = litera;
            PAIR[nfrom][nto] = PII(from,to);
            Q.push(PII(nfrom,nto));
          }
        }
      }
      while(i<next[to].size() && next[to][i].first == litera) i++;
      i--;
    }
  }
  /*
  for(int j=0;j<n;j++) {
    for(int i=0;i<n;i++) {
      cerr.width(5);
      cerr << COST[i][j] << " ";
    }
    cerr << endl;
  }
  */
  int d;
  cin >> d;
  int prev = -1;
  while(d--) {
    int akt;
    cin >> akt; akt --;
    if(prev != -1) {
      if(COST[prev][akt] == inf) {
        cout << "-1" << endl;
      } else { 
        int cost = COST[prev][akt];
        PII aktp = PII(prev,akt);
        for(int i=0; i<(cost+1)/2; i++) {
          //cerr << " --  " << aktp.first << " , " << aktp.second << endl;
          TAB[i] = CHAR[aktp.first][aktp.second];
          TAB[cost-1-i] = CHAR[aktp.first][aktp.second];
          aktp = PAIR[aktp.first][aktp.second];
        }
        TAB[cost] = 0;
        cout << cost;
        cout << " " << TAB << endl;
      }
    }
    prev = akt;
  }
  return 0;
}
