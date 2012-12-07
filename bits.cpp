#include<cstdio>
#include<set>

using namespace std;
int n, q;
const int maxn = 100005;
char A[maxn], B[maxn];
set<int> SUMS[3];

char TMP[maxn];

void set_a(int idx, int x) {
  SUMS[A[idx]+B[idx]].erase(idx);
  A[idx] = x;
  SUMS[A[idx]+B[idx]].insert(idx);
}
void set_b(int idx, int x) {
  SUMS[A[idx]+B[idx]].erase(idx);
  B[idx] = x;
  SUMS[A[idx]+B[idx]].insert(idx);
}

int get_bit_pos(set<int>& S, int position) {
  set<int>::iterator iter = S.lower_bound(position);
  if(iter == S.begin()) return -1;
  iter --;
  return *iter;
}

int get_c(int idx) {
  int b2 = get_bit_pos(SUMS[2], idx);
  int b0 = get_bit_pos(SUMS[0], idx);
  int carry = 0;
  if(b2 > b0) carry = 1;
  return (A[idx] + B[idx] + carry) % 2;
}

int main() {
  scanf("%d%d", &n, &q);

  scanf("%s", TMP);
  for(int i=0; i<n ;i++) set_a(n - i - 1, TMP[i] == '0' ? 0 : 1);
  scanf("%s", TMP);
  for(int i=0; i<n ;i++) set_b(n - i - 1, TMP[i] == '0' ? 0 : 1); 

  for(int i=0; i<q ;i++) {
    char op[6];
    int idx, x;
    scanf("%s", op);
    //printf("%s\n", op);
    if(op[0] == 's') {
      scanf("%d%d", &idx, &x);
      if(op[4] == 'a') set_a(idx,x);
      if(op[4] == 'b') set_b(idx,x);
    } else {
      scanf("%d", &idx);
      int b = get_c(idx);
      printf("%d", b);
    }
  }
  return 0;
}
