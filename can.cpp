#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;


vector<int> candies;
vector<int> scores;
int n;

void pass() {
  for(int i=1; i<n; i++) {
    if(scores[i] > scores[i-1]) candies[i] = max(candies[i], candies[i-1] + 1);
  }
}

int main() {
  scanf("%d", &n);
  for(int i=0; i<n ;i++) {
    int score;
    scanf("%d", &score);
    scores.push_back(score);
    candies.push_back(1);
  }
  pass();
  reverse(candies.begin(), candies.end());
  reverse(scores.begin(),  scores.end());
  pass();
/*
  reverse(candies.begin(), candies.end());
  reverse(scores.begin(),  scores.end());
  for(int i=0; i<n ;i++) printf("  -  %d\n", candies[i]);
*/
  int result = 0;
  for(int i=0; i<n ;i++) result += candies[i];
  printf("%d\n", result);
  
  return 0;
}
