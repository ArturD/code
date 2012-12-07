#include <iostream>
#include <algorithm>
using namespace std;

int n,k;
const int maxn=605;
const int maxk=55;
int x[maxn][maxn];
int S[maxn][maxn];
int T[maxn][maxk];
int Ti[maxn][maxk];
int wyn[maxk];
int main()
{
cin >> n >>k;
for(int i=1; i<n; i++)
	for(int j=i+1; j<=n; j++)
		cin >> x[i][j];

for(int j=2; j<=n; j++) S[0][j]=0;
for(int i=1; i<n; i++) S[i][0]=0;	

for(int i=1; i<n; i++)
	for(int j=2; j<=n; j++)
		S[i][j]=x[i][j]+S[i-1][j]+S[i][j-1]-S[i-1][j-1];

int ost=-1;

for(int l=n-1; l>0; l--){
		int prev=l;
		for(int h=0; h<=k; h++){
		if(h==0) T[l][h]=0;
		else{
			if(n-l<h) T[l][h]=0;
			else{
				int max=-1;
				int maxi=-1;
				for(int i=l; i<=n-h; i++){
					int suma=T[i+1][h-1]+S[i][n]-S[l-1][n]-S[i][i]+S[l-1][i];
					//cerr << l << " : " << i << " : " << h << " = " << suma << endl;
					if(suma>max){
						max=suma;
						maxi=i;
						ost=i;
					}
				}
				T[l][h]=max;
				Ti[l][h]=maxi;
			}
		//cerr << l << ":" << h << endl;
		//cout << T[l][h] << endl;	 
		}
		}
	}
/*
for(int i=0; i<=n; i++) {
  for(int j=0; j<=k; j++) {
    cerr.precision(3);
    cerr << T[i][j] << ' ';
  }
  cerr << endl;
}
cerr << endl;
for(int i=0; i<=n; i++) {
  for(int j=0; j<=k; j++) {
    cerr.precision(3);
    cerr << Ti[i][j] << ' ';
  }
  cerr << endl;
}
cerr << endl;
*/
for(int i=k-1; i>=0; i--){
	cout << ost << " ";
	ost=Ti[ost+1][i];
	}
cout << endl;
return 0;
}


