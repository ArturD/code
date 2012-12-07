#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int,int> PII;
vector<PII> values;
typedef vector<int> VI;
typedef VI::iterator VIi;


template<class T>
struct Node {
  T b,e;
  int bit;
  Node *b0, *b1;
  vector<int> v;

  Node(T begin, T end, int b) {
    this->b=begin;
    this->e=end;
    bit = b;
    sort_v();
    burst();
  }
  
  void sort_v() {
    for(T i = b; i!=e ;i++) {
      v.push_back(i->second);
    }
    sort(v.begin(), v.end());
  }

  void burst() {
    if(bit > 0) {
      int bias = 0;
      if(e!=b) bias = b->first;
      bias >>= bit;
      bias <<= bit;
      T piv = lower_bound(b,e, PII(bias+(1<<(bit-1)),0));
      b0 = new Node(b, piv, bit-1);
      b1 = new Node(piv, e, bit-1);
    } else b0 = b1 = 0;
  }

  bool has(int a, int b) {
    VIi u,l;
    l = lower_bound(v.begin(), v.end(), a);
    u = upper_bound(v.begin(), v.end(), b);
    // if(l!=u) { for(VIi i=l; i!=u; i++) cerr<<*i<<" "; cerr <<endl; }
    return l != u;
  }

  int search(int a, int b, int x) {
    //cerr << " search " << a <<" " << b << " " << x <<endl;
    //cerr << "    " << this->b->first << " : " << (e-1)->first << endl;
    if (bit == 0) return 0;
    int bv = 1, ov = 0;
    Node* better = b1;
    Node* other  = b0;
    if(x & (1<< (bit-1))) {
      swap(better,other);
      swap(bv, ov);
    }
    if(better->has(a,b)) {
      //cerr << "+++" << (bv << (bit-1)) << endl;
      return better->search(a,b,x) | (bv << (bit-1));
    } else {
      if(!other->has(a,b)) cerr << "zonk" << endl;
      //cerr << "---" << (ov << (bit-1)) << endl;
      return other->search(a,b,x) | (ov << (bit-1));
    }
  }

  ~Node() {
    if(b0 != 0) delete b0;
    if(b1 != 0) delete b1;
  }
};

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    values.clear();
    int n,q;
    scanf("%d%d", &n, &q);
    for(int i=0; i<n ;i++) {
      int x;
      scanf("%d", &x);
      values.push_back(PII(x,i+1));
    }
    sort(values.begin(), values.end());
    Node<vector<PII>::iterator> N(values.begin(), values.end(), 16);
    for(int i=0; i<q; i++) {
      int a,p,qi;
      scanf("%d%d%d", &a,&p,&qi);
      int r = N.search(p,qi,a); 
      printf("%d\n", r^a);
    }
  }
  return 0;
}
