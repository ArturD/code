#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef pair<int,int> PII;

int n,m,k,a,b;

const int maxn=100005;

priority_queue<PII> Q;
vector<int> nast[maxn];

int distances[maxn][2];
int visit[maxn];

void dijkstra(int aa){
	PII akt;
	int akta, aktb;
	distances[aa][0]=0;
	Q.push(PII(0,aa));
	while(!Q.empty()){
		akt=Q.top();
		Q.pop();
		aktb=akt.second;
		if(visit[aktb]==2) continue;
	  visit[aktb]=2;
	  for(int i=0; i<nast[aktb].size(); i++){
				int aktnast=nast[aktb][i];
				if(visit[aktnast]==2) continue;
				if(visit[aktnast]==1){
					int best=min(distances[aktnast][0], distances[aktnast][1]);
					Q.push(PII(-best, aktnast));
					}
				int best=min(distances[aktb][0]+a,distances[aktb][1]+a);
				if(distances[aktnast][0]>best) distances[aktnast][0]=best; 
				
				for(int i=0; i<nast[aktnast].size(); i++){
					int nast2=nast[aktnast][i];
					if(visit[nast2]==2)continue;
					if(nast2==aktb) continue;
					if(min(distances[aktb][0], distances[aktb][1])+b>distances[nast2][1]) continue;
					bool bb=binary_search(nast[nast2].begin(), nast[nast2].end(), aktb);
					if(bb==false){
						distances[nast2][1]=min(distances[aktb][0], distances[aktb][1])+b;
						visit[nast2]=1;
						}
					}	
				
				best=min(distances[aktnast][0], distances[aktnast][1]);
				Q.push(PII(-best, aktnast));
		}
	}	
}



int main(){
	cin >> n >> m >> k >> a >> b;
	for(int i=0; i<m; i++){
		int aa, bb;
		cin >> aa >> bb;
		nast[aa].push_back(bb);
		nast[bb].push_back(aa);
		}	 
	for(int i=1; i<=n; i++) sort(nast[i].begin(), nast[i].end());
	for(int i=1; i<=n; i++){
		distances[i][0]=1000000000;
		distances[i][1]=1000000000;
		}
	dijkstra(k);
	for(int i=1; i<=n; i++) cout << min(distances[i][0], distances[i][1]) << endl;
}
