#include <cstdio>
#include <cstring>
#include <math.h>
#include <limits>
#include <vector>

using namespace std;


#define INT_MAX 1000000
//#define CLR(a, x) memset( a, x, sizeof( a ) )
#define Inf (INT_MAX/2)
#define BUBL { \
	t = q[i]; q[i] = q[j]; q[j] = t; \
	t = inq[q[i]]; inq[q[i]] = inq[q[j]]; inq[q[j]] = t; }

// Dijkstra's using non-negative edge weights (cost + potential)
#define Pot(u,v) (d[u] + pi[u] - pi[v])

struct MaxFlowMinCost {
	// adjacency matrix (fill this up)
	int** cap;

	// cost per unit of flow matrix (fill this up)
	int** cost;

	// flow network and adjacency list
	int **fnet, **adj, *deg;

	// Dijkstra's predecessor, depth and priority queue
	int *par, *d, *q, *inq, qs;

	// Labelling function
	int *pi;

        int size;

        int * _NewArray(int size) {
          int* ret = new int[size];
          for(int i=0;i<size;i++) ret[i] = 0;
          return ret;
        }
        int ** _NewArray2(int size) {
          int** ret = new int*[size];
          for(int i=0;i<size;i++) ret[i] = _NewArray(size);
          return ret;
        }

        void CLR(int* arr, int v) {
          for(int i=0; i<size; i++) memset(arr, v, sizeof(int) * size);
        }
        void CLR(int** arr, int v) {
          for(int i=0; i<size; i++) CLR(arr[i], v);
        }

        void Delete(int* arr) {
          delete[] arr;
        }
        void Delete(int** arr) {
          for(int i=0;i<size;i++) delete[] arr[i];
          delete[] arr;
        }
    ~MaxFlowMinCost() {
        Delete( cap  ); 
	Delete( cost );
	Delete( fnet );  
        Delete( adj  ); 
        Delete( deg  ); 
	Delete( par  ); 
        Delete( d    ); 
        Delete( q    ); 
        Delete( inq  ); 
	Delete( pi   ); 
    }
    MaxFlowMinCost(int size) {
	cap   = _NewArray2(size);
	cost  = _NewArray2(size);
	fnet  = _NewArray2(size);
        adj   = _NewArray2(size);
        deg   = _NewArray(size);
	par   = _NewArray(size);
        d     = _NewArray(size);
        q     = _NewArray(size);
        inq   = _NewArray(size);
	pi    = _NewArray(size);
        this->size = size;
    }

    void set(int s,int t, int cap, int cost)
    {
      this->cap[s][t] = cap;
      this->cost[s][t] = cost;
    }

	bool dijkstra( int n, int s, int t )
	{
		CLR( d, 0x3F );
		CLR( par, -1 );
		CLR( inq, -1 );
		//for( int i = 0; i < n; i++ ) d[i] = Inf, par[i] = -1;
		d[s] = qs = 0;
		inq[q[qs++] = s] = 0;
		par[s] = n;

		while( qs ) 
		{
			// get the minimum from q and bubble down
			int u = q[0]; inq[u] = -1;
			q[0] = q[--qs];
			if( qs ) inq[q[0]] = 0;
			for( int i = 0, j = 2*i + 1, t; j < qs; i = j, j = 2*i + 1 )
			{
				if( j + 1 < qs && d[q[j + 1]] < d[q[j]] ) j++;
				if( d[q[j]] >= d[q[i]] ) break;
				BUBL;
			}
        
			// relax edge (u,i) or (i,u) for all i;
			for( int k = 0, v = adj[u][k]; k < deg[u]; v = adj[u][++k] )
			{
				// try undoing edge v->u      
				if( fnet[v][u] && d[v] > Pot(u,v) - cost[v][u] ) 
					d[v] = Pot(u,v) - cost[v][par[v] = u];
        
				// try using edge u->v
				if( fnet[u][v] < cap[u][v] && d[v] > Pot(u,v) + cost[u][v] ) 
					d[v] = Pot(u,v) + cost[par[v] = u][v];
                
				if( par[v] == u )
				{
					// bubble up or decrease key
					if( inq[v] < 0 ) { inq[q[qs] = v] = qs; qs++; }
					for( int i = inq[v], j = ( i - 1 )/2, t;
						 d[q[i]] < d[q[j]]; i = j, j = ( i - 1 )/2 )
						 BUBL;
				}
			}
		}
  
		for( int i = 0; i < n; i++ ) if( pi[i] < Inf ) pi[i] += d[i];
  
		return par[t] >= 0;
	}
	#undef Pot

	int run(int s, int t, int &fcost )
	{
                int n = size;
		// build the adjacency list
		CLR( deg, 0 );
		for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++ ) 
			if( cap[i][j] || cap[j][i] ) adj[i][deg[i]++] = j;
        
		CLR( fnet, 0 );
		CLR( pi, 0 );
		int flow = fcost = 0;
    
		// repeatedly, find a cheapest path from s to t
		while( dijkstra( n, s, t ) ) 
		{
			// get the bottleneck capacity
			int bot = INT_MAX;
			for( int v = t, u = par[v]; v != s; u = par[v = u] )
				bot = min(bot, fnet[v][u] ? fnet[v][u] : ( cap[u][v] - fnet[u][v] ));

			// update the flow network
			for( int v = t, u = par[v]; v != s; u = par[v = u] )
				if( fnet[v][u] ) { fnet[v][u] -= bot; fcost -= bot * cost[v][u]; }
				else { fnet[u][v] += bot; fcost += bot * cost[u][v]; }
    
			flow += bot;
		}
  
		return flow;
	}
};



const int inf = 1000000000;
const int infflow = 301*301+1;
int main() {
  int n,m;
  scanf("%d%d", &n, &m);
  MaxFlowMinCost flow( 2*n+2+2 );

  for(int i=0; i<m; i++) {
    int a,b,c;
    scanf("%d%d%d", &a, &b, &c);
    a--; b--;
    flow.set(a,b+n,1,c);
  }
  for(int i=0; i<n; i++) {
    flow.set(2*n,     i, infflow, 0); // s   -> i
    flow.set(i+n, 2*n+1, infflow, 0); // i+n -> t
  }
  // inf circualtion
  flow.set(2*n+1, 2*n, infflow, 0);   // t -> s
  flow.set(2*n, 2*n+1, infflow, 0);   // s -> t

  // out lower bounds to t'
  flow.set(2*n  ,2*n+3, n, 0);  // s -> t'
  for(int i=0; i<n; i++) flow.set(i+n, 2*n+3, 1, 0); // i+n -> t'
  // in lower bound from s'
  flow.set(2*n+2,2*n+1, n, 0);  // s' -> t
  for(int i=0; i<n; i++) flow.set(2*n+2, i, 1, 0); // s' -> i

  int res, matched;
  matched = flow.run(2*n+2,2*n+3, res);
  /*
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      fprintf(stderr, " %d", flow.fnet[i][j+n]);
    }
    fprintf(stderr,"\n");
  }
  */
  /*
  for(int i=0; i<4; i++) {
    for(int j=0; j<2*n+4; j++) {
      fprintf(stderr, " %d", flow.fnet[i+2*n][j]);
    }
    fprintf(stderr,"\n");
  }
  fprintf(stderr,"  ---  \n");
  for(int i=0; i<4; i++) {
    for(int j=0; j<2*n+4; j++) {
      fprintf(stderr, " %d", flow.fnet[j][i+2*n]);
    }
    fprintf(stderr,"\n");
  }
  */
  /*
  for(int i=0; i<n*2+4; i++) {
    for(int j=0; j<n*2+4; j++) {
      fprintf(stderr, " %d", flow.fnet[i][j]);
    }
    fprintf(stderr,"\n");
  }
  */
  //fprintf(stderr,"matched %d\n", matched);
  if( matched!=n*2 ) printf("NIE\n");
  else printf("%d\n", res);
}
