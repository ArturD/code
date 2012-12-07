import sys

from Queue import PriorityQueue
from random import *

n,m,k,a,b = (10**4*9,10**5, 1,10,7)

print "%d %d %d %d %d" % (n,m,k,a,b)
for x in xrange(1,n):
  print "%d %d" % (x,x+1)

for x in xrange(0,m-n+1):
  a = randint(1,n)
  b = randint(min(a+1,n-1),min(n,a+10))
  if b>=a:
    a = b-1
  if a<1:
    b+=1
    a+=1
  if b>=a:
    a = b-1
  if a<1:
    break
  print "%d %d" % (a,b)

