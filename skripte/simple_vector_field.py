from mpl_toolkits.mplot3d import Axes3D
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from matplotlib.pyplot import cm
import matplotlib.pyplot as plt
import numpy as np

"""
Kopirao `primjer`_.
.. _primjer: https://www.getdatajoy.com/examples/python-plots/vector-fields
"""


def field_def():
    """
    iz `dokumentacije <http://docs.scipy.org/doc/numpy/reference/generated/numpy.mgrid.html>`

    if the step length is a **complex number** (e.g. 5j),
    then the integer part of its magnitude is interpreted
    as specifying the number of points to create between
    the start and stop values, where the stop value **is inclusive**.
    """
    pos_y, pos_x = np.mgrid[-3:3:30j, -3:3:30j]
    vx = -pos_y/(pos_x**2+pos_y**2)
    vy = pos_x/(pos_x**2+pos_y**2)
    speed = np.sqrt(vx ** 2 + vy ** 2)
    u_n = vx / speed
    v_n = vy / speed

    return pos_x, pos_y, vx, vy, u_n, v_n, speed


def quiver_dyn_colors(px, py, un, vn, value):
    plot1 = plt.figure()
    plt.quiver(px, py, un, vn,  # data
               value,  # colour the arrows based on this array
               cmap=cm.Accent,  # colour map
               headlength=7)  # length of the arrows
    plt.colorbar()  # adds the colour bar

    plt.title('Quive Plot, Dynamic Colours')
    return plot1


def quiver_single_color(px, py, un, vn):
    plot2 = plt.figure()
    plt.quiver(px, py, un, vn,
               color='Teal',
               headlength=7)

    plt.title('Quiver Plot, Single Colour')
    return plot2


def stream_dyn_color(px, py, vx, vy, vel):
    plot3 = plt.figure()
    plt.streamplot(px, py, vx, vy,  # data
                   color=vel,  # array that determines the colour
                   # cmap=cm.cool,  # colour map
                   cmap=cm.seismic,  # colour map
                   linewidth=2,  # line thickness
                   arrowstyle='->',  # arrow style
                   arrowsize=1.5)  # arrow size

    plt.colorbar()  # add colour bar on the right

    plt.title('Stream Plot, Dynamic Colour')
    return plot3


def stream_dyn_line_width(px, py, vx, vy, vel):
    plot4 = plt.figure()
    lw = 5 * vel / vel.max()  # line width proportional to speed

    plt.streamplot(px, py, vx, vy,  # data
                   density=[0.5, 1],
                   color='DarkRed',
                   linewidth=lw)

    plt.title('Stream Plot, Dynamic Line Width')
    return plot4


def surface_3d(px, py, vel):
    """
    iz `primjera <https://www.getdatajoy.com/examples/python-plots/surface-plot-and-wireframe>`
    """
    plot5 = plt.figure()
    ax = plot5.gca(projection='3d')  # 3d axes instance
    surf = ax.plot_surface(px, py, vel,  # data values (2D Arrays)
                           rstride=2,  # row step size
                           cstride=2,  # column step size
                           cmap=cm.gnuplot2,  # colour map
                           linewidth=1,  # wireframe line width
                           antialiased=True)

    #ax.zaxis.set_major_locator(LinearLocator(6))
    #ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))
    ax.set_title('Brzine')  # title
    plot5.colorbar(surf, shrink=0.5, aspect=5)  # colour bar
    #ax.view_init(elev=30, azim=70)  # elevation & angle
    #ax.dist = 8  # distance from the plot

    return plot5

if __name__ == '__main__':
    print("greska s dijeljenjem kada su x && y == 0")
    x, y, u, v, u_n, v_n, velocity = field_def()
    plots = []
    plots.append(quiver_dyn_colors(x, y, u_n, v_n, velocity))
    plots.append(quiver_single_color(x, y, u_n, v_n))
    plots.append(stream_dyn_color(x, y, u, v, velocity))
    plots.append(stream_dyn_line_width(x, y, u, v, velocity))
    plots.append(surface_3d(x, y, velocity))
    for p in plots:
        plt.show(p)