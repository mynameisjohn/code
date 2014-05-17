import math
import numpy as np

def f(x,y):
   C=6.6
   E=0.5
   mu=1.
   nu=4.

   mu = -math.log(2.)/(mu*mu)
   nu = -math.log(2.)/(nu*nu)
   
   return C*math.exp((x**2+y**2)*mu)-E*math.exp((x**2+y**2)*nu)

size=11
dog=np.eye(size,size)
#np.array([[0.,0.,0.],[0.,0.,0.],[0.,0.,0.]])

for i in range (-(size/2),size/2+1):
   for j in range (-(size/2),size/2+1):
      idx_X=j+size/2
      idx_Y=i+size/2
      dog[idx_X,idx_Y]=f(j,i)

#print dog
sum=0
for i in range (0,size):
   sum = sum + np.sum(dog[i])
#np.sum(dog[0])+np.sum(dog[1])+np.sum(dog[2])
print sum           
#print "("+str(idx_X)+", "+str(idx_Y)+")"

#for i in range (-(size/2),size/2+1):
#   print (i+size/2)

#str(f(i))+", "+str(i)
