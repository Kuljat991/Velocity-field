# -*- coding: utf-8 -*-
from math import*
import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
import numpy as np
import os
import glob
from PIL import Image, ImageSequence

def read_file (path):
    file_number = len(os.listdir(path))
    t_all= []
    x_all= []
    y_all= []
    for file in range (0, file_number-1):
        txt_file = np.loadtxt(path +'/'+ str(file) + '.txt')
        t_all.append(txt_file[:,0])           #ukupno vrijeme
        x_all.append(txt_file[:,1])    #x-kordinate tocke
        y_all.append(txt_file[:,2])
    return t_all[0], x_all, y_all, file_number

def field_def():
    pos_y, pos_x = np.mgrid[-3:3:30j, -3:3:30j]
    vx = -pos_y/(pos_x**2+pos_y**2)
    vy = pos_x/(pos_x**2+pos_y**2)
    speed = np.sqrt(vx ** 2 + vy ** 2)
    u_n = vx / speed
    v_n = vy / speed
        
    return pos_x, pos_y, vx, vy, u_n, v_n, speed
    
def plot_vector_field (t ,x = [], y = [], pos_x = [], pos_y = [], u_n = [], v_n = [], velocity = []):
    fig, ax = plt.subplots()
    plt.axis([-3, 3, -3, 3])
    ax.quiver(pos_x, pos_y, u_n, v_n,  # data
                velocity,  # colour the arrows based on this array
                cmap=cm.Accent,  # colour map
                headlength=7)  # length of the arrows
    ax.plot(x , y, 'ro')
    plt.title(str(t))
    return fig, ax


if __name__ == '__main__' :
    path = os.listdir('../results')
    path_for_save_fig = []
    for folder in path:
        path_for_save_fig.append('../results/' + folder + '/' + 'fig')
    #provjera ako ima filova
    if len (path_for_save_fig) == 0 :
        print 'no files'
    else:
    #stvaranje foldera za spremanje slika ako ne postoji, a ako postoji onda se brise sve u njemu
        for folder in path_for_save_fig:             
            if not os.path.exists(folder):
                os.mkdir(folder)
            else:
                files = glob.glob(folder + '/*')
                for f in files:
                    os.remove(f)

    for folder in path: 
    # citanje svih txt dokumenta u folderu i stvaranje vektora vremena (t),
    # x-korrdinate(x_tocka), y-korrdinate(y_tocka) za nestacionarno i stacionarno vektorsko polje
        t_all, x_all, y_all, file_len = read_file('../results/' + folder)

    # stvaranje vektora x-koordinate(x_field), y-koordinate(y_field),
    # brzine u smjeru osi x(u), brzine u smjeru osi y(v), intenzitet brzine (velocity)
    # jedinicna brzina u smjeru osi x (u_n), jedinicna brzina u smjeru osi x (v_n)
        x_field, y_field, u, v, u_n, v_n, velocity = field_def()    
    
        for i in range ( 0, len(t_all)):
            x_plot = []
            y_plot = []

            for j in range (0, file_len-1):
                x_plot.append(x_all [j] [i])
                y_plot.append(y_all [j] [i])

            fig1, ax = plot_vector_field(t_all [i], x_plot, y_plot, x_field, y_field, u_n, v_n, velocity)
            fig1.savefig('../results/' + folder + '/' + 'fig' + '/'+str (i))
            plt.close(fig1)
