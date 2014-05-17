import sys

size=sys.getsizeof(1)
n=3

G = [[1 for x in xrange(n)] for x in xrange(n)]
X = [[0 for x in xrange((n-1)/size+1)] for x in xrange(n)]

#G.append([1,1,1,1,1,1,0,0,0])
#G.append([1,1,1,1,1,1,0,0,0])
#G.append([1,1,1,1,1,1,0,0,0])
#G.append([1,1,1,1,1,1,1,1,1])
#G.append([1,1,1,1,1,1,1,1,1])
#G.append([1,1,1,1,1,1,1,1,1])
#G.append([0,0,0,1,1,1,1,1,1])
#G.append([0,0,0,1,1,1,1,1,1])
#G.append([0,0,0,1,1,1,1,1,1])

for i in range (0,len(G)):
   for j in range (0,len(G[i])):
      idx=0
      if (j>0 and (j%size==0)):
         idx=idx+1
      X[i][idx]=X[i][idx]<<1
      X[i][idx]=X[i][idx]|G[i][j]

print X

