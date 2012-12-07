import sys
import random

x = int(sys.argv[1])
k = int(sys.argv[2])

n1 = x/(k+1)
n = n1*(k+1)
print "%s %s" % (n,k)

lstr = []
for i in xrange(0,n1):
  lstr.append('c')
for i in xrange(0,n1*k):
  lstr.append('b')

#random.shuffle(lstr)
ostr = ''.join(lstr)

print ostr

print ""
