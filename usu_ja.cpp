#include <cstdio>
#include <vector>
#include <algorithm>

#include <iostream>
using namespace std;

const int maxn = 1000005;
int n,k;
char str[maxn];
char x;
int main() {
  scanf("%d%d", &n, &k);
  scanf("%s", str);

  vector<int> stack;
  int pos = 0;
  int black = 0;
  int white = 0;
  while(stack.size()!=0 || pos<n) {
    while(black+white < k+1) {
      stack.push_back(pos);
      char c = str[pos++];
      if(c == 'b') white++;
      else if(c == 'c') black++;
      else cerr << "!" << c << endl;
    }
    if(black == 1 && white == k) {
      for(int i=0; i<k+1; i++) {
        printf("%d ",  stack[stack.size()-k-1+i]+1);
      }
      for(int i=0; i<k+1; i++) {
        stack.pop_back();
      }
      white = black = 0;
      printf("\n"); 
      while(black+white < min(k+1,(int)stack.size())) {
        char c = str[stack[stack.size()-black-white-1]];
        if(c == 'b') white++;
        else if(c == 'c') black++;
        else cerr << "!" << c << endl;
      }
    } else {
      char c = str[stack[stack.size()-k-1]];
      if(c == 'b') white--;
      else if(c == 'c') black--;
      else cerr << "!" << c << endl;
    }
  }
  return 0;
}
