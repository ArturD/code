#include <iostream>
#include <vector>
#include <map>
#include<stack>
using namespace std;
typedef pair<int,int> PII;
const int maxn=100005;
vector<int>nast[maxn];

stack<int>S;
stack<int>S2;
int ile;
int drog[maxn];
int drog1[maxn];

PII dfs(int a)
{
while(!S.empty())S.pop();
S.push(a);
//int prev;
PII ret = PII(-1,-1);
if(drog1[a]) return ret;
drog1[a] = 1000005;
while(!S.empty())
                 {
                 a=S.top();
                 S.pop();
                 cerr << a << " ";
                 // if(drog1[a] == 0) cerr << " BLAD !! " << a <<endl;
                 for(int i=0; i<nast[a].size(); i++)
                         {
                          //cerr << "    nast = " << nast[a][i] << endl;
                         if(drog1[nast[a][i]]&&nast[a][i]!=drog1[a] && ret.first == -1)
                                                       {
                                                       //cerr <<"<<<<" << a << " nast="<<nast[a][i] <<" drog1[a]" << drog1[a] <<endl;
                                                       //cerr <<" <<<" << drog1[nast[a][i]] <<endl;
                                                       if(nast[a][i]>a) ret= PII(a,nast[a][i]) ;

                                                       else ret = PII(nast[a][i],a);                      
                                                       }
                         if(!drog1[nast[a][i]]&&nast[a][i]!=drog1[a]) {
                           drog1[nast[a][i]] = a;
                           S.push(nast[a][i]);
                         }
                         }
                 //if(S.top()==a) S.pop();
                 }
                 //cerr << endl;
                 //cerr << ret.first << " : " << ret.second << endl;
  return ret;
}

void dfs2(int a, int b)
{
int _a = a;
int _b = b;
while(!S2.empty())S2.pop();
S2.push(a);
ile++;
drog[a] = b;
a=b;
//int prev;
while(!S2.empty())
                  {
                  a=S2.top();
                  S2.pop();
                  //cerr << " akt " << a  << endl;
                  for(int i=0; i<nast[a].size(); i++)
                          {
                          //cerr << "     nast [a][i] " << nast[a][i] << endl; 
                          if(a == _a && nast[a][i] == _b) continue;
                          if(!drog[nast[a][i]]&&nast[a][i]!=drog[a]){ 
                                                                  //if (a == 128) cerr << " i " << nast[a][i] << " : " << a  << " !!!!!!!!!!!! "<< endl;
                                                                  //cout << nast[a][i] << endl;
                                                                  ile++;
                                                                  drog[nast[a][i]] = a;
                                                                  S2.push(nast[a][i]);
                                                                  }
                          }
                  //cout << "S2.top() " << S2.top() << endl;
                  //if(S2.top()==a) S2.pop();
                  } cerr << endl;
           
}


int main()
{
ios_base::sync_with_stdio(false);
int n,m;
cin >> n >> m;

for(int i=1;i<m+1; i++)
{
        int a,b;
        cin >> a >> b; 
      
        nast[a].push_back(b);    
        nast[b].push_back(a);   
}

if(n>m)
       {
       cout << "NIE" << endl; 
       return 0;
       }  
for(int i=1;i<n+1; i++)
{ 
if(!drog[i])
            {
            PII akt=dfs(i);
            if(akt.first == -1) continue;
            if(drog[akt.first]) cerr << "już jest !! " << akt.first<< " : " << drog[akt.first]<< endl;
            if(drog[akt.first]) cerr << "           " << akt.second<< endl;
            //drog[akt.first]=akt.second;
            //ile++;
            //cerr  << " -- " << i <<  endl;
            //if(akt.first == 128)cerr << " i2 " << akt.first << " : " << akt.second << endl;
            dfs2(akt.first, akt.second);
            }
}

cerr << "ile"  << ile<< endl;
if(ile<n) {cout << "NIE" << endl; return 0;}
cout << "TAK" << endl;
for(int i=1; i<n+1; i++)
        {
        bool ok = false;
        for(int j=0; j<nast[drog[i]].size(); j++)
          if(nast[drog[i]][j] == i) ok = true;
        if(!ok) cerr << "nie ma!! " << i << "<-"<<drog[i] << endl;
        if(drog[drog[i]] == i) cerr << "cykl!!!" << i << " : " << drog[i] << endl;
        cout << drog[i] << endl;
        } 

return 0;    
}
