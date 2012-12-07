/* Enter your code here. Read input from STDIN. Print output to STDOUT */
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <cstdlib>
using namespace std;

const int maxn=105;

int dad[maxn];
int pot[maxn];
int odw[maxn];

stack <int> S;
vector<int> nast[maxn];
queue<int> q;

void dfs(int a){
dad[a]=0;
S.push(a);
while(!S.empty()){
        a=S.top();
        S.pop();
        if(a > 0) {
          S.push(-a);
          odw[a]=1;
          for(int i=0; i<nast[a].size(); i++){
                if(!odw[nast[a][i]]){
                        S.push(nast[a][i]);
                        dad[nast[a][i]]=a;
                        }
                
           }
        } else {
          a = - a;
          int p = 1;
          for(int i=0; i<nast[a].size(); i++){
            if(nast[a][i] == dad[a]) continue;
            p += pot[nast[a][i]];
          }
          pot[a] = p;
          
        }
      }
}

int main(){
        int n,m;
        cin >> n >> m;
        for(int i=0; i<m; i++){
                int a,b;
                cin >> a >> b;
                nast[a].push_back(b);
                nast[b].push_back(a);
                }       
        for(int i=1; i<=n; i++) pot[i]=1;
        dfs(1);
        int wynik=0;
        for(int i=2; i<=n; i++){
                if(pot[i]%2==0){
                        wynik ++;
                }
}
cout << wynik << endl;
return 0;
}
