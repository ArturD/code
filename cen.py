import sys

from Queue import PriorityQueue

n,m,k,a,b = [int(x) for x in sys.stdin.readline().split()]
nast = []
visited = []
distance = []

def dijkstra(start):
  pq = PriorityQueue()
  pq.put([0,start])
  while not pq.empty():
    cost,akt = pq.get()
    if visited[akt]:
      continue
    distance[akt] = cost
    visited[akt] = True
    nn = []
    for nxt in nast[akt]:
      nn += nast[nxt]
    nn = set(nn).difference(nast[akt])
    for nxt in nn:
      pq.put([cost+b, nxt])
    for nxt in nast[akt]:
      pq.put([cost+a, nxt])
      
      

for x in xrange(0,n+1):
  nast.append([])
  visited.append(False)
  distance.append(0)

for x in xrange(0,m):
  x,y = [int(x) for x in sys.stdin.readline().split()]
  nast[x].append(y)
  nast[y].append(x)

dijkstra(k)
for i in xrange(1,n+1):
  print distance[i]
