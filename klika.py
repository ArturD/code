n = 440+1
a, b = 1, 10

k = 1
m = n*(n+1)/2+1

print "%s %s %s %s %s" % (n,m,k,a,b)

print "1 2"
for i in xrange(2,n+1):
  for j in xrange(2,n+1):
    print "%s %s" % (i, j)
  
  
