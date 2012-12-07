#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int,int> PII;

int n,m,k,a,b;

const int maxn=100005;

priority_queue<PII> Q;
vector<int> nast[maxn];

int distances[maxn][2];
int visit[maxn];
int prev[maxn];

void dijkstra(int aa){
	PII akt;
	int akta, aktb;
	distances[aa][0]=0;
	Q.push(PII(0,aa));
	while(!Q.empty()){
		akt=Q.top();
		Q.pop();
		aktb=akt.second;
	  visit[aktb]=1;
	  for(int i=0; i<nast[aktb].size(); i++){
				int aktnast=nast[aktb][i];
				if(visit[aktnast]==1) continue;
				int best=min(distances[aktb][0]+a,distances[aktb][1]+a);
				if(distances[aktnast][0]>best){
					 distances[aktnast][0]=best;
					 if(distances[aktnast][0]<distances[aktnast][1]) prev[aktnast]=aktb;
					}
				if(aktb!=k){
					int pp=0;
					while(pp<nast[aktb].size()){
						int aktpp=nast[aktb][pp];
						if(aktpp!=aktnast&&min(distances[aktpp][0],distances[aktpp][1])==distances[aktb][0]-a&&visit[aktpp]==1&&aktpp!=prev[aktnast]){
							if(distances[aktnast][1]>distances[aktb][0]-a+b){
								distances[aktnast][1]=distances[aktb][0]-a+b;
								break;
								}
							}
						pp++;
						}	
				}
			best=min(distances[aktnast][0], distances[aktnast][1]);
			Q.push(PII(-best, aktnast));
		}
	}
}


int main(){
	ios_base::sync_with_stdio(0);
	cin >> n >> m >> k >> a >> b;
	for(int i=0; i<m; i++){
		int aa, bb;
		cin >> aa >> bb;
		nast[aa].push_back(bb);
		nast[bb].push_back(aa);
		}	 
	for(int i=1; i<=n; i++){
		distances[i][0]=1000000000;
		distances[i][1]=1000000000;
		prev[i]=maxn;	
		}
	dijkstra(k);
	for(int i=1; i<=n; i++) cout << min(distances[i][0],distances[i][1]) << endl;
	return 0;
}
