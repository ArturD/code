#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

const int maxn=1000005;

char kol[maxn];
int next[2*maxn][2]; // 0 czarne 1 bia³e
int prev[2*maxn][2];
int us[maxn];

int n,k,pot=1;

list<int>czarne;
vector<int>wynik;

void drzewo(){
	for(int i=0; i<k; i++){
		int pocz=wynik[i]+1+pot;
		int kon=wynik[i+1]-1+pot;

		int nextc=0;
		int nextb=0;
		int prevc=0;
		int prevb=0;
		nextc+=next[kon][0];
		nextb+=next[kon][1];
		prevc+=prev[pocz][0];
		prevb+=prev[pocz][1];
		kon/=2;
		while(kon!=0){
		nextc-=next[kon][0];
		nextb-=next[kon][1];
		kon/=2;
		}
		pocz/=2;
		while(pocz!=0){
			prevc-=prev[pocz][0];
			prevb-=prev[pocz][1];
			pocz/=2;
			}
		pocz=wynik[i]+1+pot;
		kon=wynik[i+1]-1+pot;
		while(pocz<kon){
			if(pocz%2==0) pocz/=2;
			else{
				if(pocz>=pot){
					next[pocz][0]-=nextc;
					next[pocz][1]-=nextb;
					prev[pocz][0]-=prevc;
					prev[pocz][1]-=prevb;
					} 
				else{
					next[pocz][0]+=nextc;
					next[pocz][1]+=nextb;
					prev[pocz][0]+=prevc;
					prev[pocz][1]+=prevb;
					}
				pocz=(pocz+1)/2;
				}
			if(kon%2==1) kon/=2;
			else{
				if(kon>=pot){
						next[kon][0]-=nextc;
						next[kon][1]-=nextb;
						prev[kon][0]-=prevc;
						prev[kon][1]-=prevb;
						} 
				else{
					next[kon][0]+=nextc;
					next[kon][1]+=nextb;
					prev[kon][0]+=prevc;
					prev[kon][1]+=prevb;
					}
				kon=(kon-1)/2;
				}
			}
		if(pocz==kon){
			next[pocz][0]+=nextc;
			next[pocz][1]+=nextb;
			prev[pocz][0]+=prevc;
			prev[pocz][1]+=prevb;
			}
		}	
	int pocz=wynik[k]+1+pot;
	while(us[pocz-pot]==1) pocz++;
	int aktpocz=pocz;
	int nextc=next[pocz][0];
	int nextb=next[pocz][1];
	int prevc=prev[pocz][0];
	int prevb=prev[pocz][1];
	pocz/=2;
	while(pocz!=0){
			nextc-=next[pocz][0];
			nextb-=next[pocz][1];
			prevc-=prev[pocz][0];
			prevb-=prev[pocz][1];
			pocz/=2;
			}
	pocz=aktpocz;
	int kon=pocz+nextc+nextb;
	while(pocz<kon){
	if(pocz%2==0) pocz/=2;
	else{
		if(pocz>=pot){
			prev[pocz][1]-=prevb;
			prev[pocz][0]-=prevc;
			pocz=(pocz+1)/2;
			} 
		else{
			prev[pocz][1]+=prevb;
			prev[pocz][0]+=prevc;
			pocz=(pocz+1)/2;
			}
		}
	if(kon%2==1) kon/=2;
	else{
		if(kon>=pot){
				prev[kon][1]-=prevb;
				prev[kon][0]-=prevc;
				kon=(kon-1)/2;
				} 
		else{
			prev[kon][1]+=prevb;
			prev[kon][0]+=prevc;
			kon=(kon-1)/2;
			}
		}

	}	
	if(pocz==kon){
			prev[pocz][0]+=prevc;
			prev[pocz][1]+=prevb;
			}		
}


void funkcja1(int p, int poz, int prevc, int prevb){
	poz=poz-(prevb+prevc)-1;
	
			while(wynik.size()<k+1){
				poz++;
				int i=wynik.size();
				if(kol[poz]=='c') continue;
				int nextc=0;
				int nextb=0;
				int prevc=0;
				int prevb=0;
				int akt=poz+pot;
				nextc+=next[akt][0];
				nextb+=next[akt][1];
				prevc+=prev[akt][0];
				prevb+=prev[akt][1];
				akt/=2;
				while(akt!=0){
					nextc-=next[akt][0];
					nextb-=next[akt][1];
					prevc-=prev[akt][0];
					prevb-=prev[akt][1];
						akt/=2;
					}
			if(k*nextc==nextb+i){
				us[poz]=1;
				wynik.push_back(poz);
				}
			}
	sort(wynik.begin(), wynik.end());
	drzewo();	
}

void funkcja2(int p, int poz, int prevc, int prevb){
			while(wynik.size()<k+1){
				int i=wynik.size();
				poz++;
				if(kol[poz]=='c') continue;
				int nextc=0;
				int nextb=0;
				int prevc=0;
				int prevb=0;
				int akt=poz+pot;
				nextc+=next[akt][0];
				nextb+=next[akt][1];
				prevc+=prev[akt][0];
				prevb+=prev[akt][1];
				akt/=2;
				while(akt!=0){
					nextc-=next[akt][0];
					nextb-=next[akt][1];
					prevc-=prev[akt][0];
					prevb-=prev[akt][1];
						akt/=2;
					}
			if(k*nextc==nextb-(k-i-1)||k*(prevc-1)==prevb-(i-1)){
				us[poz]=1;
				wynik.push_back(poz);
				} 
			}
	sort(wynik.begin(), wynik.end());
	drzewo();	
}

void funkcja3(int p, int poz, int prec, int preb, int nexc, int nexb){
	int aktpoz=poz-(preb+prec)-1;
	int i=1;
	while(wynik.size()<preb-k*prec+1){
		aktpoz++; 
		if(kol[aktpoz]=='c') continue;
		int nextc=0;
		int nextb=0;
		int prevc=0;
		int prevb=0;
		int akt=aktpoz+pot;
		nextc+=next[akt][0];
		nextb+=next[akt][1];
		prevc+=prev[akt][0];
		prevb+=prev[akt][1];
		akt/=2;
		while(akt!=0){
			nextc-=next[akt][0];
			nextb-=next[akt][1];
			prevc-=prev[akt][0];
			prevb-=prev[akt][1];
			akt/=2;
			}
		akt=aktpoz+pot;
		if(k*nextc==nextb+i){
			i++;
			us[akt-pot]=1;
			wynik.push_back(akt-pot);
			}
	}		
	i=1;
	aktpoz=poz+nexc+nexb+1;
	while(wynik.size()<k+1){
		aktpoz--; 
		if(kol[aktpoz]=='c') continue;
		int nextc=0;
		int nextb=0;
		int prevc=0;
		int prevb=0;
		int akt=aktpoz+pot;
		nextc+=next[akt][0];
		nextb+=next[akt][1];
		prevc+=prev[akt][0];
		prevb+=prev[akt][1];
		akt/=2;
		while(akt!=0){
			nextc-=next[akt][0];
			nextb-=next[akt][1];
			prevc-=prev[akt][0];
			prevb-=prev[akt][1];
			akt/=2;
			}
		akt=aktpoz+pot;
		if(k*prevc==prevb+i){
		i++;
		us[akt-pot]=1;
		wynik.push_back(akt-pot);
		}

	}
sort(wynik.begin(), wynik.end());
drzewo();	
}

void szuk(){
for(int i=1; i<pot; i++){
	prev[i][0]=0;
	prev[i][1]=0;
	next[i][0]=0;
	next[i][1]=0;
	}
list<int>::iterator iter=czarne.begin();
int nr=0;
while(!czarne.empty()){
	int poz=(*iter);
			int nextc=0;
			int nextb=0;
			int prevc=0;
			int prevb=0;
			int akt=poz+pot;
			nextc+=next[akt][0];
			nextb+=next[akt][1];
			prevc+=prev[akt][0];
			prevb+=prev[akt][1];
			akt/=2;
			while(akt!=0){
				nextc-=next[akt][0];
				nextb-=next[akt][1];
				prevc-=prev[akt][0];
				prevb-=prev[akt][1];
					akt/=2;
				}
	if(k*(prevc+1)==prevb){
		wynik.push_back(poz);
		us[poz]=1;
		funkcja1(nr,poz, prevc, prevb);
		czarne.erase(iter);
		iter=czarne.begin();
		for(int i=0; i<k+1; i++) cout << wynik[i]+1 << " ";
		cout << endl;
		wynik.clear();
		} 
	else{
		if(k*(nextc+1)==nextb){
			wynik.push_back(poz);
			us[poz]=1;
			funkcja2(nr,poz, prevc, prevb);
			czarne.erase(iter);
			iter=czarne.begin();
			for(int i=0; i<k+1; i++) cout << wynik[i]+1 << " ";
			cout << endl;
			wynik.clear();
			} 
		else{
			if(nextb-nextc*k+(prevb-prevc*k)==k&&(nextb-nextc*k)>0&&(prevb-prevc*k)>0){
				wynik.push_back(poz);
				us[poz]=1;
				funkcja3(nr,poz, prevc, prevb,nextc, nextb);
				czarne.erase(iter);
				iter=czarne.begin();
				for(int i=0; i<k+1; i++) cout << wynik[i]+1 << " ";
				cout << endl;
				wynik.clear();
				} 
			else{
				  iter++; 
				}
			}
		}
	}
}

int main(){
        ios_base::sync_with_stdio(false);
	cin >> n >> k;
	while(pot<n) pot*=2;
	int c=n/(k+1);
	int b=n-c;
	prev[0][0]=0;
	prev[0][1]=0;
	char akt;
	for(int i=0; i<n; i++){
		cin >> kol[i];
		if(kol[i]=='c') czarne.push_back(i); 
		if(kol[i]=='c'&&i>0){
			if(akt=='c'){
				prev[pot+i][0]=prev[pot+i-1][0]+1;
				prev[pot+i][1]=prev[pot+i-1][1];
				}
			else{
				prev[pot+i][0]=prev[pot+i-1][0];
				prev[pot+i][1]=prev[pot+i-1][1]+1;
				}
			next[pot+i][0]=c-prev[pot+i][0]-1;
			next[pot+i][1]=b-prev[pot+i][1];
			}
		if(kol[i]=='b'&&i>0){
			if(akt=='c'){
				prev[pot+i][0]=prev[pot+i-1][0]+1;
				prev[pot+i][1]=prev[pot+i-1][1];
				}
			else{
				prev[pot+i][0]=prev[pot+i-1][0];
				prev[pot+i][1]=prev[pot+i-1][1]+1;
				}
			next[pot+i][0]=c-prev[pot+i][0];
			next[pot+i][1]=b-prev[pot+i][1]-1;
			}
		akt=kol[i];
		} 
	if(kol[0]=='c'){
		next[pot][0]=c-1;
		next[pot][1]=b;
		}	
	else{
		next[pot][0]=c;
		next[pot][1]=b-1;
		}
	szuk();
return 0;
}
