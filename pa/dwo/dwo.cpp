#include<iostream>
#include<bitset>
using namespace std;

typedef long long ll;

ll CACHE[100] = {319973637ll,639946773ll,959985937ll,1279959047ll,1599998211ll,1919971349ll,2239944979ll,2559983617ll,2879957249ll,3199995923ll,3519969537ll,3839942657ll,4159981829ll,4480020759ll,4800059415ll,5120033045ll,5440006161ll,5760045329ll,6080018455ll,6400057607ll,6720030737ll,7040004355ll,7360043025ll,7680016647ll,8000055297ll,8320028949ll,8639936513ll,8959975445ll,9279949063ll,9599987729ll,9919961363ll,10240000017ll,10559973655ll,10879946757ll,11199985939ll,11519959041ll,11839998231ll,12159971331ll,12479944967ll,12799983621ll,13120022533ll,13440061701ll,13760034819ll,14080008469ll,14400047123ll,14720020759ll,15040059395ll,15360033047ll,15680006161ll,16000045313ll,16320018439ll,16640057605ll,16960030743ll,17279938819ll,17599977733ll,17919950869ll,18239990021ll,18559963139ll,18879936773ll,19199975447ll,19519949073ll,19839987715ll,20159961345ll,20480000023ll,20799973653ll,21119946759ll,21439985921ll,21760024577ll,22080063511ll,22400037125ll,22720010245ll,23040049427ll,23360022535ll,23680061703ll,24000034817ll,24320008465ll,24640047123ll,24960020739ll,25280059415ll,25600033047ll,25919940627ll,26239979525ll,26559953159ll,26879991809ll,27199965447ll,27519938565ll,27839977731ll,28159950865ll,28479990019ll,28799963155ll,29119936787ll,29439975445ll,29759949077ll,30080053269ll,30400026903ll,30720065793ll,31040038933ll,31360012549ll,31680051221ll,32000024835ll};
int MAP[32];
void pre() {
  MAP[0]=0;
  MAP[1]=1;
  MAP[2]=3;
  MAP[3]=0;
  MAP[4]=4;
  MAP[5]=1;
  MAP[6]=7;
  MAP[7]=0;
  MAP[8]=8;
  MAP[9]=1;
  MAP[10]=11;
  MAP[11]=0;
  MAP[12]=12;
  MAP[13]=1;
  MAP[14]=15;
  MAP[15]=0;
  MAP[16]=16;
  MAP[17]=1;
  MAP[18]=19;
  MAP[19]=0;
  MAP[20]=20;
  MAP[21]=1;
  MAP[22]=23;
  MAP[23]=0;
  MAP[24]=24;
  MAP[25]=1;
  MAP[26]=27;
  MAP[27]=0;
  MAP[28]=28;
  MAP[29]=1;
  MAP[30]=31;
  MAP[31]=0;
}
ll get(ll no) {
  pre();
  if( no==1 ) return 1;
  ll a = no/2;
  int xr = 1;
  int cur = 0;
  ll i=2;
  int div = 5000000;
  if( a/div ) {
    i = CACHE[a/div-1]/2 + 1;
    if( a%div==0 ) i--;
    cur += a/div*div;
    xr = 0;
  }
  for(; ; i++) {
    int count = 1;
    ll ii = i;
    while( ii%2==0 ) {
      ii/=2;
      count++;
    }
    xr ^= MAP[count-1] ^ MAP[count];
    if( xr==0 ) cur++;
    //if( xr==0 && (i*2+no%2)%1000==127 ) cerr << cur*2 << " : " << (i*2+no%2) << endl;
    if( a==cur ) return i*2 + no%2;
  }
}

int main() {
  ll a = 1000000005;
  cin >> a;
  cout << get(a) << endl;
  return 0;
}

