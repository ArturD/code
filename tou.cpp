#include<cstdio>
#include<vector>
#include<stack>
#include<iostream>
using namespace std;

const int maxn=1000005;

int n,m,k;

int pozycja[maxn];
vector<int>DFS;
vector<int>ZB;

vector<int>nast[maxn];
vector<int> wynik1;
vector<int> wynik2;
vector<int>stos;
int prev[maxn];
bool odw[maxn];

void dfs(int a)
{
if (odw[a]) return;
stos.push_back(a);

DFS.push_back(a);
if(a <= k) ZB.push_back(a);
pozycja[a] = 0;

while(!stos.empty())
{
  a=stos[stos.size()-1];
  stos.pop_back();
  if(a<0) {
    a = -a;
    
    //cerr << "back " << a << endl;
    // backward
    DFS.pop_back();
    if(a<=k) ZB.pop_back();

  }
  if(a>0) {
    if(odw[a]) continue;
    odw[a]=true;
    stos.push_back(-a);
    //cerr << "go " << a << endl;

    // forward
    
    DFS.push_back(a);
    pozycja[a]=DFS.size()-1;
    if(a<=k) ZB.push_back(pozycja[a]);

    for(int i=0; i<nast[a].size(); i++)
    {
      if(!odw[nast[a][i]]) {
        stos.push_back(nast[a][i]);
        prev[nast[a][i]] = a;
        //cerr << "prev" << nast[a][i]  << " : " << a << endl;
      } else {
        int b = nast[a][i];
        int zb;
        if (ZB.size() > 0) zb = ZB[ZB.size()-1];
        else zb = -1;
        int wst = pozycja[b];
        if(prev[a] == b) continue;
          //cerr << "edge " << a << " : " << b << endl;
          //cerr << "edge2 " << zb << " : " << wst << endl;
        if(zb>=wst) {
          wynik1.push_back(a);  
          wynik2.push_back(b);  
        }
      }
    }
  }
}
}

int main() {
scanf("%d%d%d",&n, &m, &k);
for(int i=0; i<m; i++)
{
  int a,b;
  scanf("%d%d", &a, &b);
    nast[a].push_back(b);
    nast[b].push_back(a);
}
for(int i=1; i<=n; i++) dfs(i);


printf("%d\n", (int)wynik1.size());
for(int i=0;i<wynik1.size(); i++) {
  printf("%d %d\n", wynik1[i],wynik2[i]);
}
return 0;
}
