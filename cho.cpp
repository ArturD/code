#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int maxn=205;
const int maxs=100005;
int n,m;
char tab[maxn][maxs];
vector<int> P[maxn];
typedef long long ll;
ll roz[maxn];
ll pre[maxn][maxn];

ll P2[32][maxn][maxn];
ll PM[maxn][maxn];
ll TMP[maxn][maxn];


void copyM(ll (&a)[maxn][maxn], ll (&o)[maxn][maxn]) {
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      o[i][j] = a[i][j];
    }
  }
}

void mult(ll (&a)[maxn][maxn], ll (&b)[maxn][maxn], ll (&o)[maxn][maxn]) {
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      ll best = 1LL<<60LL;
      for(int k=0; k<n; k++) {
        ll akt = a[i][k] + b[k][j];
        if(akt < best) best = akt;
      }
      o[i][j] = best;
    }
  }
}
void getM(int m) {
  if(m==0) {
    //copyM(pre, PM);
    return;
  }
  copyM(pre, P2[0]);
  for(int i=1; (1<<i) <= m; i++) {
    mult(P2[i-1],P2[i-1], P2[i]);
  }
  bool first = true;
  for(int i=0; (1<<i) <= m; i++) {
    if(m & (1<<i)) {
      if(first) {
        first = false;
        copyM(P2[i], PM);
      } else {
        copyM(PM, TMP);
        mult(TMP, P2[i], PM);
      }
    }
  }
}

void printM(ll (&a)[maxn][maxn]) {
for(int i=0; i<n; i++) 
	for(int j=0; j<n; j++){
		cout << i << " " << j << " " << a[i][j] << endl;
	}	  
}

void ps(int aa)
{
P[aa].resize(roz[aa]+1, 0);
P[aa][0]=-1;
int t=-1;
for(int i=1; i<=roz[aa]; i++){
	while(t>=0&&tab[aa][t+1]!=tab[aa][i]) t=P[aa][t];
	t++;
	P[aa][i]=t;
	}
}

int mp(int aa, int bb)
{
int aktmax=0;
int i=0, j=0;
while(i<=roz[aa]){
	while(j<roz[bb]&&tab[bb][j+1]==tab[aa][i+j+1]) {
	j++;
	}
        //if(aa == 1 && bb == 0) cerr << "  " << i << " : " << j << endl;
        if(i+j == roz[aa]) {
          //cerr << "!" << tab[bb]+1 << " : " << (tab[aa]+i+1) << endl;
          for(int jj=0; jj<j; jj++) if(tab[bb][jj+1] != tab[aa][i+jj+1]) return 0;
          return j;
        }
        if(i+j >  roz[aa]) cerr << "!";

	aktmax=max(aktmax, j);
	i+=j-P[aa][j];
	j=max(0,P[aa][j]);
	}
return 0;
}



int main()
{
cin >> n >>m;
for(int i=0; i<n; i++){
	string a;
	cin >> a;
	for(int j=1; j<a.size()+1; j++) tab[i][j]=a[j-1];
	roz[i]=a.size();
	}
	
for(int i=0; i<n; i++) ps(i);

for(int i=0; i<n; i++) 
	for(int j=0; j<n; j++){
		if(i==j) {
			pre[i][j]=roz[j]-P[i][roz[j]];
			}
		else{
			int wynik=mp(i,j);
			pre[i][j]=roz[j]-wynik;
			}
		}
//printM(pre);
getM(m-1);
ll best = 1LL<<60LL;
for(int i=0; i<n; i++) {
  for(int j=0; j<n; j++) {
    ll akt = roz[i] + PM[i][j];
    if(akt <best) best = akt;
  }
}
cout << best << endl;
return 0;
}
