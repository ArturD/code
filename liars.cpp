/* Sample program illustrating input and output */

#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 105;
int A[maxn], B[maxn], C[maxn];
int MIN[maxn][maxn], MAX[maxn][maxn];
int HAS_MIN[maxn][maxn], HAS_MAX[maxn][maxn];
typedef pair<int,int> PII;

int N, M;

int get_min(int a, int b, int iter);

int get_max(int a, int b, int iter) {
  if(HAS_MAX[a][b] == iter) return MAX[a][b];
  int m = MAX[a][b];
  for(int i=a; i<b; i++) {
    int tmp = (get_max(a,i,iter)+get_max(i+1,b,iter));
    if(tmp < m) m = tmp;
  }
  for(int i=a; i<b; i++) {
    int ma1 = get_max(a,i,iter);
    int ma2 = get_max(i+1,b,iter);
    int mi1 = get_min(a,i,iter);
    int mi2 = get_min(i+1,b,iter);
    if(ma1 + mi2 > m) MAX[a][i]   = m-mi2;
    if(mi1 + ma2 > m) MAX[i+1][b] = m-mi1;
  }
  MAX[a][b] = m;
  HAS_MAX[a][b] = iter;
  //cerr << " max " << a << " : " << b << " = " << m << endl;
  return MAX[a][b];
}

int get_min(int a, int b, int iter) {
  if(HAS_MIN[a][b] == iter) return MIN[a][b];
  int m = MIN[a][b];
  for(int i=a; i<b; i++) {
    int tmp = (get_min(a,i,iter)+get_min(i+1,b,iter));
    if(tmp > m) m = tmp;
  }
  for(int i=a; i<b; i++) {
    int ma1 = get_max(a,i,iter);
    int ma2 = get_max(i+1,b,iter);
    int mi1 = get_min(a,i,iter);
    int mi2 = get_min(i+1,b,iter);
    if(ma1 + mi2 < m) MIN[i+1][b] = m-ma1;
    if(mi1 + ma2 < m) MIN[a][i]   = m-ma2;
  }
  MIN[a][b] = m;
  HAS_MIN[a][b] = iter;
  //cerr << " min " << a << " : " << b << " = " << MIN[a][b] << endl;
  return MIN[a][b];
}

int count_bits(int a) {
  int result = 0;
  //cerr << "bits " << a; 
  for(; a ; a &= a-1) result ++;
  //cerr << " : "  << result << endl; 
  return result;
}

PII brut() {
  int rmin = N+1;
  int rmax = 0;
  for(int mask=0; mask<(1<<N); mask++) {
    bool ok = true;
    for(int i=0; i<M ;i++) {
      int mm = 0;
      for(int j=A[i]; j<=B[i]; j++) {
        mm |= 1 << (j-1);
      }
      if(C[i] != count_bits(mm&mask)) { ok = false; break; }
    }
    //cerr << hex << mask << endl;
    if(ok) {
      int used = count_bits(mask);
      rmin = min(rmin, used);
      rmax = max(rmax, used);
    }
  }
  if(rmin > rmax) return PII(-1,-1);
  return PII(rmin, rmax);
}

int main(){
        cin >> N >> M;
        for(int i=1; i<=N ;i++)
          for(int j=i; j<=N ;j++) {
            MAX[i][j] = j-i+1;
          }
        for(int i = 0; i < M; i++){
                cin >> A[i] >> B[i] >> C[i];
                int diff = B[i] - A[i] + 1;
                for(int x = A[i]; x<=B[i] ;x++)
                  for(int y = x ; y<=B[i] ;y++) {
                    MAX[x][y] = min(MAX[x][y], C[i]);
                    MIN[x][y] = max(MIN[x][y], max(0, (y-x+1) - diff + C[i]));
                  }
        }
        
        int rmin, rmax;

        for(int i=1; i<4; i++) {
          rmin = get_min(1, N,i);
          rmax = get_max(1, N,i);
        }
        cout << rmin << " " << rmax << "\n";
         
        /*
        PII b = brut();
        if( b.first != -1 && (b.first != rmin || b.second != rmax) ) {
          cerr << b.first << " " << b.second << endl;
          while(true) {}
        }
        */
        
        return 0;
}
