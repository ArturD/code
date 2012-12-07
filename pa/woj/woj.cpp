#include<cstdio>
#include<queue>

using namespace std;
int main() {
  int n;
  deque<int> a,b;
  scanf("%d", &n);
  a.push_back(-1);
  b.push_back( 1);
  for(int i=0; i<n-1; i++) {
    int aa = a.back(); a.pop_back();
    int bb = b.back(); b.pop_back();
    b.push_front(aa);
    b.push_front(aa);
    a.push_front(bb);
    a.push_front(bb);
  }
  for(int i=0; i<n; i++) {
    int x; 
    scanf("%d", &x);
    x *= a.front(); a.pop_front();
    a.push_back(x);
  }
  for(int i=0; i<n; i++) {
    int x; 
    scanf("%d", &x);
    x *= b.front(); b.pop_front();
    b.push_back(x);
  }
  while(a.size() > 1) {
    int x,y;
    x = a.front(); a.pop_front();
    y = a.front(); a.pop_front();
    b.push_back(min(x,y));
    //fprintf(stderr,"b %d %d\n",x,y);
    
    x = b.front(); b.pop_front();
    y = b.front(); b.pop_front();
    a.push_back(max(x,y));
    //fprintf(stderr,"b %d %d\n",x,y);
  }
  printf("%d\n", -(a.front()+b.front()));
  return 0;
}
