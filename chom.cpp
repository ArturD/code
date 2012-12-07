#include <iostream>

#include <string>

#include <list>

using namespace std;



const int maxn=205;

const int maxs=100005;

int n,m;

char tab[maxn][maxs];

int P[maxn][maxs];

int roz[maxn];

int pre[maxn][maxn];



void ps(int aa)

{

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

	aktmax=max(aktmax, j);

	i+=j-P[aa][j];

	j=max(0,P[aa][j]);

	}

return aktmax;

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

for(int i=0; i<n; i++) 

	for(int j=0; j<n; j++){

		cout << i << " " << j << " " << pre[i][j] << endl;

	}	

		

return 0;

}
