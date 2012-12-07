import sys

n,k = [int(x) for x in sys.stdin.readline().split(' ')]
st = sys.stdin.readline().strip()
if len(st) != n:
  print "!",len(st), n
  print "st[0]=%s"% st[0]
  print "st[len(st)]=%s"% st[len(st)-1]
  sys.exit(1)

kk = n / (k+1)
lins = []
was = []
tos = []
for i in xrange(0,kk):
  line = sys.stdin.readline().strip()
  while line == '':
    line = sys.stdin.readline()
  lin2 = [x.strip() for x in line.split(' ') if len(x.strip()) > 0]
  lin = [int(x) for x in lin2]
  lins.append(lin)
  was.append(False)
  if len(lin) != k+1:
    print "line %s %s" % (len(line), line) 
    print "lin %s %s" % (len(lin), k+1) 
    sys.exit(1)
  for j in xrange(0,len(lin)):
    tos.append([lin[j], i])
  c = 0
  b = 0
  for i in lin:
    if st[i-1] == 'c':
      c+=1
    if st[i-1] == 'b':
      b+=1
  if c != 1 or b != k:
    print " k=%s    c=%s b=%s" % (k,c,b)
    sys.exit(1) 
    break
tos = sorted(tos, cmp=lambda a,b: a[0]<b[0])

stack = []

for i,ilin in tos:
  #print i,ilin
  if len(stack) != 0 and stack[len(stack)-1] == ilin:
    #print "pop", 
    stack.pop()
  else:
    if not was[ilin]:
      was[ilin] = True
      for i in xrange(0,k): 
        stack.append(ilin)
    else:
      print "was %s expected %s" % (ilin, stack[len(stack)-1])
      print "  %s %s" % (lins[ilin], lins[stack[len(stack)-1]])
      sys.exit(1)

