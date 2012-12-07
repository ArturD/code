#include <iostream>
#include <algorithm>
using namespace std;

const int maxn=500005;

long long tak[maxn];

bool cmp( int a, int b ) {
   return a > b;
 }

int main()
{
long long m,d;
int n;
cin >> m >> d >> n;
for(int i=0; i<n; i++){
	cin >> tak[i];
	}
sort(tak, tak+n, cmp);

long long przejechane=0;
int akti=-1;
int zoz=-1;
long long kroki=0;
while(true){
	akti++;
	if(tak[akti]>=m-d){
		if(tak[akti+1]<m-d){
			zoz=akti;
			break;
			}
		przejechane+=tak[akti]-(d-przejechane);
		kroki++;
		if(przejechane>=m) break;
		}
	}

while(tak[zoz]<((m-d)+2*(d-przejechane))){
	akti++;
	if(tak[akti]>d-przejechane) {
		przejechane+=tak[akti]-(d-przejechane);
		kroki++;
		}
	else break;	
	}

if(przejechane>=m) cout << kroki << endl;
else{
	if(przejechane<d){
		if(tak[zoz]>=(m-d)+2*(d-przejechane)){
			kroki++;
			cout << kroki << endl;
			}
		else cout << "0" << endl;
		}
	else{
		kroki++;
		cout << kroki << endl;
		}
	}
return 0;	
}

