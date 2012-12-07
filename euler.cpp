#include<iostream>
#include<vector>
#include<list>
#include<stack>
#include<map>
#include<cstdio>
using namespace std;
int n,m, w;
const int maxn = 100005;
const int maxm = 200005;

struct Edge {
  int next;
  Edge* wym;
  bool wymuszona;

  Edge() {
    wym = NULL;
    next = -1;
    wymuszona = false;
  }
};

list<Edge*> edges[maxn];
map<pair<int,int>, Edge*> edgesMap;
stack<int> s1,s2;

bool go() {
  scanf("%d%d", &n, &m);
  for(int i=0;i<m;i++) {
    int a,b;
    scanf("%d%d", &a, &b);
    Edge* ea = new Edge();
    ea->next = b;
    edges[a].push_front(ea);
    edgesMap[pair<int,int>(a,b)] = ea;
  }

  //cin >> w;
  scanf("%d", &w);
  for(int i=0; i<w;i++) {
    int k;
    //cin >> k;
    scanf("%d", &k);
    int a,b;
    //cin >> a >> b;
    scanf("%d%d", &a,&b);
    if(k == 2) {
      map<pair<int,int>, Edge*>::iterator iter = edgesMap.find(pair<int,int>(a,b));
      if(iter == edgesMap.end()) return false;
    }
    for(int i=2; i<k; i++) {
      int c;
      //cin >> c;
      scanf("%d", &c);
      
      map<pair<int,int>, Edge*>::iterator iter = edgesMap.find(pair<int,int>(a,b));
      if(iter == edgesMap.end()) return false;

      Edge* ab = iter->second; 
      if (ab->wym != NULL && ab->wym->next != c) {
        return false;
      }
      if (ab->wym == NULL) {
        iter = edgesMap.find(pair<int,int>(b,c));
        if(iter == edgesMap.end()) return false;
        ab->wym = iter->second;
        ab->wym->wymuszona = true;
      }

      a=b;
      b=c;
    }
  }

  stack<bool> s1w;
  s1.push(1);
  s1w.push(false);
  while(!s1.empty()) {
    int akt = s1.top();
    if(!edges[akt].empty()) {
      list<Edge*>::iterator i1 = edges[akt].begin();
      if((*i1)->wymuszona) {
        edges[akt].erase(i1);
        continue;
      }
      s1.push((*i1)->next);
      s1w.push(false);
      edges[akt].erase(i1);
      Edge* e = (*i1)->wym;
      if(e != NULL) {
        do {
          s1.push(e->next);
          s1w.push(true);
          e = e->wym;
        } while(e != NULL);
      }
    } else {
      while (true){
        int akt = s1.top();
        s1.pop();
        if(s2.empty()) if(akt!= 1) return false;
        s2.push(akt);
        bool wym = s1w.top();
        s1w.pop();
        if(!wym)break;
      }
    }
  }

  if(s2.size() != m+1) return false;
  if(s2.top() != 1) return false;
  return true;
}

int main() {
  if(go()) {
    printf("TAK\n");
    while(!s2.empty()) {
      printf("%d\n", s2.top());
      s2.pop();
    }
  } else {
    printf("NIE\n");
  }
  return 0;
}
