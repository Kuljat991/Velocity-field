# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib
import matplotlib.mlab as mlab
import matplotlib.cm as cm
import matplotlib.pyplot as plt
import numpy as np

a=[]
a= np.loadtxt('../results/myout.txt')
#print(a)

x, y, z = np.meshgrid(np.arange(-0.8, 1, 0.2),
                      np.arange(-0.8, 1, 0.2),
                      np.arange(0, 0.1, 0.1))

u = -y/(x*x+y*y)
v = x/(x*x+y*y)
w = np.sqrt(u**2+v**2)
print(w)

fig = plt.figure()
ax = fig.gca(projection='3d')
#ax.quiver(x, y, z, u, v, w,                 # data
#          length=0.15,                      # arrow length
#         )
ax.plot_surface(x[:,:,0],y[:,:,0],w[:,:,0])
ax.set_title('3D Vector Field')             # title
ax.view_init(elev=18, azim=30)              # camera elevation and angle
ax.dist=8                                   # camera distance



plt.show()
