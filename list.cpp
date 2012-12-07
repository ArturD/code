#include<iostream>
#include<list>

using namespace std;

struct Edge;
list<Edge*> next[100000];

struct Edge {
  int next;
  list<Edge*>::iterator rev;
};

void remove(Edge* edge) {
  cerr << "erase " << edge->next;
  cerr << " <- "  << (*(edge->rev))->next << endl;
  Edge *edge2 = *(edge->rev);
  next[edge->next].erase(edge->rev);
  next[edge2->next].erase(edge2->rev);
}

int n,m;

void wypisz() {
  for(int i=0;i<n;i++) {
    cout << i << " :";
    for(list<Edge*>::iterator j = next[i].begin(); j!=next[i].end(); j++) {
      cout << (*j)->next << " ";
    }
    cout << endl;
  }
}

int main() {
  cin >>n >> m;
  for(int i=0; i<m; i++){
    int a,b;
    cin >> a >> b;
    Edge* e_a = new Edge();
    Edge* e_b = new Edge();
    e_a->next = b;
    e_b->next = a;

    e_b->rev = next[a].insert(next[a].end(), e_a);
    e_a->rev = next[b].insert(next[b].end() ,e_b); 
  }

  wypisz();

  cout << "co mam usunac?" << endl;
  int x;
  cin >> x;
  for(list<Edge*>::iterator ie=next[x].begin(); ie!=next[x].end();) {
    list<Edge*>::iterator tmp = ie;
    ie++;
    remove(*tmp);
  }

  wypisz();
}
