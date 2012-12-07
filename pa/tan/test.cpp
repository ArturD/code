#include<set>
#include<queue>
using namespace std;

typedef pair<long long, int> PLI;

int main() {
  int n = 2000000;
  /*
  set<PLI> S;
  for(int i=0; i<n; i++) {
    S.insert( PLI(i,i) );
  }
  for(int i=0; i<n; i++) {
    S.erase( PLI(i,i) );
    S.insert( PLI(i-10,i) );
  }
  */

  priority_queue< PLI > Q;
  
  for(int i=0; i<n; i++) {
    Q.push( PLI(i,i) );
  }
  for(int i=0; i<n; i++) {
    Q.push( PLI(i-10,i) );
    Q.pop();
  }

  return 0;
}
