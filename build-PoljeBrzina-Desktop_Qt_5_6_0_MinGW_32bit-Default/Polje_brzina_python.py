# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

a=[]
a= np.loadtxt('myout.txt')
print(a)

x, y, z = np.meshgrid(np.arange(-0.8, 1, 0.2),
                      np.arange(-0.8, 1, 0.2),
                      np.arange(-0.8, 1, 0.8))

u = -y/(x*x+y*y)
v = -x/(x*x+y*y)
w = 0.

fig = plt.figure()
ax = fig.gca(projection='3d')

ax.quiver(x, y, z, u, v, w,                 # data
          length=0.15,                      # arrow length
          color='Tomato'                    # arrow colour
          )

ax.set_title('3D Vector Field')             # title
ax.view_init(elev=18, azim=30)              # camera elevation and angle
ax.dist=8                                   # camera distance

plt.show()
