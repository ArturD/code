import sys
from random import *

d = randint(2,10)
m = randint(1,d)
n = randint(3, 4)

print "%d %d %d"%(d,m,n)
for i in xrange(0,n):
  sys.stdout.write("%d " % randint(1,max(d/10,4)))

print ""

