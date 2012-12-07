#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int maxn=500005;
vector<int>nast[maxn];
vector<int>wynik;
int visit[maxn];
int pre[maxn];
int prze[maxn];
int prev[maxn];

queue<int>Q,Q2;

int n;
int aktpre=0;

void dfs(int a)
{
aktpre++;
visit[a]=1;
pre[a]=aktpre;
for(int i=0; i<nast[a].size(); i++){
		if(!visit[nast[a][i]]){
			dfs(nast[a][i]);
			}
		}
prze[a]=aktpre;
}

int funkcja1(int a){
	int pocz=a;
	wynik.push_back(a);
	visit[a]=2;
	while(true){
		
		int dalej=0;
		int droga=0;
		int nr=0;
		for(int i=0; i<nast[a].size(); i++){
			int aktnast=nast[a][i];
			if(aktnast==prev[a]) continue;
			if(visit[aktnast]==2) continue;
			if(pre[aktnast]==prze[aktnast]){
				droga=aktnast;
				wynik.push_back(aktnast);
				prev[aktnast]=a;
				visit[aktnast]=2;
				}
			else{
				nr++;
				if(nr==2) return 0;
				if(visit[a]==2){
					prev[aktnast]=a;
					dalej=aktnast;
					}
				else{
					prev[aktnast]=a;
					wynik.push_back(aktnast);
					visit[aktnast]=2;
					dalej=aktnast;
					}
				}
			}
			
		if(dalej!=0) a=dalej;
		else{
			if(droga!=0) a=droga;
			}
		if(pre[a]==prze[pocz]) break;
		}
	while(true){
		a=prev[a];
		if(visit[a]!=2){
			wynik.push_back(a);
			visit[a]=2;
			}
		if(a==pocz) return 1;
		}
}

int funkcja2(int a){
	int pocz=a;
	while(true){
		int dalej=0;
		int droga=0;
		int nr=0;
		for(int i=0; i<nast[a].size(); i++){
			int aktnast=nast[a][i];
			if(aktnast==prev[a]) continue;
			if(visit[aktnast]==2) continue;
			if(pre[aktnast]==prze[aktnast]){
				droga=aktnast;
				wynik.push_back(aktnast);
				prev[aktnast]=a;
				visit[aktnast]=2;
				}
			else{
				nr++;
				if(nr==2) return 0;
				if(visit[a]==2){
					prev[aktnast]=a;
					dalej=aktnast;
					}
				else{
					prev[aktnast]=a;
					wynik.push_back(aktnast);
					visit[aktnast]=2;
					dalej=aktnast;
					}
				}
			}
		if(dalej!=0) a=dalej;
		else{
			if(droga!=0) a=droga;
			}
		if(pre[a]==prze[pocz]) break;
		}
	while(true){
		a=prev[a];
		if(visit[a]!=2){
			wynik.push_back(a);
			visit[a]=2;
			}
		if(a==pocz) return 1;
		}	
}


int funkcja(int a)
{
visit[a]=2;
wynik.push_back(a);
while(true){
	if(visit[a]==1){
		int droga=a;
		for(int i=0; i<nast[a].size(); i++){
			int aktnast=nast[a][i];
			if(visit[aktnast]==2) continue;
				if(prze[aktnast]>=pre[n]&&pre[aktnast]<=pre[n]){
					droga=aktnast;
					continue;
					}
				if(pre[aktnast]==prze[aktnast]){
					visit[aktnast]=2;
					wynik.push_back(aktnast);
					}
				else{
					Q.push(aktnast);
					}
			}
		if(Q.size()>0){
				if(Q.size()>2){
					wynik.clear();
					return 0;
					}
				else{
					if(Q.size()==1){
						prev[Q.front()]=a;
						int dec=funkcja1(Q.front());
						Q.pop();
						if(dec==0){
							wynik.clear();
							return 0;
							}
						}
					else{
						prev[Q.front()]=a;
						int dec=funkcja1(Q.front());
						if(dec==0){
							wynik.clear();
							return 0;
							}
						Q.pop();
						visit[a]=2;
						wynik.push_back(a);
						prev[Q.front()]=a;
						dec=funkcja2(Q.front());
						if(dec==0){
							wynik.clear();
							return 0;
							}
						visit[droga]=2;
						wynik.push_back(droga);
						Q.pop();
						}
					}	
			}
		if(visit[a]!=2) wynik.push_back(a);	
		visit[a]=2;
		a=droga;
		if(a==n){
			wynik.push_back(a);
			return 1;
			}	
		}
		else{
			int droga=a;
			bool dalej=false;
			for(int i=0; i<nast[a].size(); i++){
				int aktnast=nast[a][i];
				if(visit[aktnast]==2) continue;
				if(prze[aktnast]>=pre[n]&&pre[aktnast]<=pre[n]){
					droga=aktnast;
					continue;
					}
				if(pre[aktnast]==prze[aktnast]){
					Q2.push(aktnast);
					}
				else{
					Q.push(aktnast);
					}
				}
			if(Q.size()>0){
				if(Q.size()>1){
					wynik.clear();
					return 0;
					}
				else{
					prev[Q.front()]=a;
					int dec=funkcja2(Q.front());
					if(dec==0){
						wynik.clear();
						return 0;
						}
					while(!Q2.empty()){
						wynik.push_back(Q2.front());
						visit[Q2.front()]=2;
						Q2.pop();
						 }
					visit[droga]=2;
					wynik.push_back(droga);
					Q.pop();
					}
				}
			while(!Q2.empty()){
				dalej=true;
				wynik.push_back(Q2.front());
				visit[Q2.front()]=2;
				Q2.pop();
				}
			if(visit[a]!=2) wynik.push_back(a);	
			visit[a]=2;
			a=droga;
			if(dalej==true){
				wynik.push_back(a);
				visit[a]=2;
				}
			if(a==n){
			wynik.push_back(a);
			return 1;
			}	
		}
	}
}

int main()
{
ios_base::sync_with_stdio(0);
cin >> n;
for(int i=0; i<n-1; i++){
	int a,b;
	cin >> a >> b;
	nast[a].push_back(b);
	nast[b].push_back(a);
	}
dfs(1);
int dec=funkcja(1);
if(dec==1){
	for(int i=0; i<n; i++) cout << wynik[i] << endl;
	}
else cout << "BRAK" << endl;
return 0;
}

