import matplotlib.pyplot as plt
import numpy as np
x = []
y=[]
point = [1, 0]
delta = [5,0]
t1 = [0, 1]
t2 = [0,-1]
langkah = 5
for i in range(langkah+1):
    s = i / langkah;  ##  // scale s to go from 0 to 1
    h1 =  2*s**3 - 3*s**2 + 1##          // calculate basis function 1
    h2 = -2*s**3 + 3*s**2      ##        // calculate basis function 2
    h3 =   s**3 - 2*s**2 + s   ##      // calculate basis function 3
    h4 =   s**3 -  s**2
    px = h1*point[0]+h2*(point[0]+delta[0])+h3*t1[0]+h4*t2[0]
    py = h1*point[1]+h2*(point[1]+delta[1])+h3*t1[1]+h4*t2[1]
    x.append(px)
    y.append(py)

plt.plot(x,y)
plt.show()
