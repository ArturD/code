#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n;
const int maxn = 1000005;

vector<vector<int> > next;
vector<bool> was;
vector<bool> was2;

bool adj(int a, int b){
  for(int i=0; i<next[a].size(); i++) {
    if(next[a][i] == b) return true;
  }
  return false;
}

bool cango(int f, int to) {
  if(f == to) return false;
  if(adj(f,to)) return true;
  for(int i=0; i<next[f].size(); i++) {
    if(adj(next[f][i], to)) return true;
  }
  return false;
}

bool wash[maxn];

bool hamilton(int cur) {
  if(cur == n) {
    bool finish = true;
    for(int i=1; i<n; i++){
      if(!wash[i]) { finish = false; break; }
    }
    return finish;
  }
  wash[cur] = true;
  bool wyn = false;
  for(int i=1; i<=n; i++){
    if(!wash[i] && cango(cur, i)) {
      if(hamilton(i)) {
        wyn = true;
        break;
      }
    }
  }
  wash[cur] = false;
  return wyn;
}

int main() {
  cin >> n;
  next.resize(n+1);
  was .resize(n+1);
  was2.resize(n+1);
  for(int i=0; i<n-1; i++) {
    int a,b;
    cin >> a >> b;

    next[a].push_back(b);
    next[b].push_back(a);
  }

  string line1;
  cin >> line1;
  if(line1 == "1") {
    was2[1] = true;
    if(n<16 && !hamilton(1)) {
      cerr << " !!!!!! " << endl;
      return 1;
    }
  } else if(line1 == "BRAK") {
    cerr << " * BRAK * " << endl;
    if(hamilton(1)) {
      cerr << " !!!!!! " << endl;
      return 1;
    }
    else return 0;
  }

  int current = 1;
  for(int i=1; i<n; i++) {
    int a;
    cin >> a;
    if(i==n-1 && a!=n) { cerr << "line "<<n << endl; return 1; }
    else {
      if(!cango(current, a)) { cerr << "cannot go " << current << "->" << a << endl; return 1; }
      current = a;
    }
    if(was2[current]) { cerr << "was "<< current << endl; return 1; } 
    was2[current] = true;
  }
  for(int i=0; i<n; i++) {
    if(was2[i+1] == false) cerr << "was not " << i+1 << endl;
  } 
  return 0;
}
