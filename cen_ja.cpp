#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int,int> PII;

int n,m,k,a,b;

const int maxn=100005;

vector<int> nast[maxn];
vector<int> EX  [maxn];
int distances[maxn];
int visit[maxn];

struct Visitor {
  int from,to,cost;
  bool extra;

  Visitor(int f, int t, int c, bool e = false) {
    from = f;
    to = t;
    cost = c;
    extra = e;
  }
  bool operator>(const Visitor& o) const {
    return cost > o.cost;
  }

  bool operator<(const Visitor& o) const {
    return cost < o.cost;
  }
};

priority_queue<Visitor,vector<Visitor>, greater<Visitor> > Q;

bool exhas(int a, int b) {
  typeof(nast[a].begin()) it = lower_bound(nast[a].begin(), nast[a].end(), b);
  if(it == nast[a].end()) return false;
  return b == *it;
}

void dijkstra(int aa){
	distances[aa]=0;
	Q.push(Visitor(aa,aa,0));
	
        while(!Q.empty()){
	  Visitor akt=Q.top();
	  Q.pop();
          if(!akt.extra) {
            if(visit[akt.to]) continue;
            visit[akt.to]=1;
            distances[akt.to]=akt.cost;
            for(int i=0; i<nast[akt.to].size(); i++){
                  int aktnast=nast[akt.to][i];
                  Q.push(Visitor(akt.to,aktnast,akt.cost+b,true));
                  if(visit[aktnast]==1) continue;
                  Q.push(Visitor(akt.to,aktnast,akt.cost+a));
            }
          } else {
            int left = 0;
            for(int i=0; i<EX[akt.to].size(); i++){
                  int aktnast=EX[akt.to][i];
                  if(akt.from == aktnast || exhas(akt.from, aktnast)) {
                    if(distances[aktnast] > akt.cost) {
                      EX[akt.to][left++] = aktnast;
                    }
                  } else {
                    if(visit[aktnast]==1) continue;
                    Q.push(Visitor(akt.to,aktnast,akt.cost));
                  }
            }
            if(left != EX[akt.to].size()) EX[akt.to].resize(left);
          }
	}
}
int main(){
	cin >> n >> m >> k >> a >> b;
        for(int i=1; i<=m; i++) {
                int aa,bb;
		cin >> aa >> bb;

                nast[aa].push_back(bb);
		EX  [aa].push_back(bb);

		nast[bb].push_back(aa);
		EX  [bb].push_back(aa);
	}
	for(int i=1; i<=n; i++){
		distances[i]=1000000000;
                sort(EX[i].begin(),EX[i].end());
                sort(nast[i].begin(),nast[i].end());
	}
	dijkstra(k);
	for(int i=1; i<=n; i++) cout << distances[i] << endl;
}
