# -*- coding: utf-8 -*-
from math import*
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import matplotlib
import matplotlib.mlab as mlab
import matplotlib.cm as cm
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.widgets import Slider
import fnmatch
import os

#class field:
#    def __init__(self, path = ''):
#        
#        txt_file = np.loadtxt(path)
#        size = len(txt_file)
#        self.t_all =txt_file[:,0]           #ukupno vrijeme
#        self.x_tocka_all = txt_file[:,1]    #x-kordinate tocke
#        self.y_tocka_all = txt_file[:,2]    #y-koordinate tocke
#        
#        inc = 0                            #pocetna pozicija slidera
#        self.fig, self.ax = plt.subplots()
#        plt.axis([-2, 2, -2, 2])
#        self.sliderax = self.fig.add_axes([0.2, 0.02, 0.6, 0.03],
#                                          axisbg='yellow')
#        
#        self.t_trenutni = self.t_all[inc]   #vijeme na pocetnoj poziciji slidera
#        self.pos_x, self.pos_y, self.u, self.v, self.u_n, self.v_n, self.velocity = self.field_def(self.t_trenutni)
#        
#        self.t = self.t_all[0:inc]    
#        self.x_tocka = self.x_tocka_all[0:inc]
#        self.y_tocka = self.y_tocka_all[0:inc]
#
#        self.ax.quiver(self.pos_x, self.pos_y, self.u_n, self.v_n,  # data
#                       self.velocity,  # colour the arrows based on this array
#                       cmap=cm.Accent,  # colour map
#                       headlength=7)  # length of the arrows
#
##        self.ax.colorbar()  # adds the colour bar
#
#        self.slider = Slider(self.sliderax, 'Value', 0, size , valinit=inc)
#        self.slider.on_changed(self.update)
#        self.slider.drawon = False
#
#        self.ax.plot(self.x_tocka, self.y_tocka,'ro') #crtanje tocke do poetnbog vremena na slideru
#
#
#    def field_def(self,t):
#        pos_y, pos_x = np.mgrid[-3:3:30j, -3:3:30j]
#        vx = -pos_y/(pos_x**2+pos_y**2 )+ 0.2*sin(t)
#        vy = pos_x/(pos_x**2+pos_y**2) + 0.2*cos(t)
#        speed = np.sqrt(vx ** 2 + vy ** 2)
#        u_n = vx / speed
#        v_n = vy / speed
#
#        return pos_x, pos_y, vx, vy, u_n, v_n, speed
#        
#    def update(self, value):
#        val = int (value)
#        self.t_trenutni = self.t_all[val-1]
#        self.t = self.t_all[0:val]
#        self.x_tocka = self.x_tocka_all[0:val-1]
#        self.y_tocka = self.y_tocka_all[0:val-1]
#        self.slider.valtext.set_text(val)
#        self.ax.quiver(self.pos_x, self.pos_y, self.u_n, self.v_n,  # data
#                       self.velocity,  # colour the arrows based on this array
#                       cmap=cm.Accent,  # colour map
#                       headlength=7)  # length of the arrows
#        self.ax.plot(self.x_tocka, self.y_tocka,'ro')
#        self.fig.canvas.draw_idle()
##        print(self.t)
#
#
#class field_const:
#    def __init__(self, path = ''):
#        self.pos_x, self.pos_y, self.u, self.v, self.u_n, self.v_n, self.velocity = self.field_def()      
#        
#        txt_file = np.loadtxt(path)
#        size = len(txt_file)
#        self.t_all =txt_file[:,0]
#        self.x_tocka_all = txt_file[:,1]
#        self.y_tocka_all = txt_file[:,2]        
#        
    


def read_file (path):
    t_all = []
    x_tocka_all = []
    y_tocka_all = []
    t_const_all = []
    x_tocka_const_all = []
    y_tocka_const_all = []       
    for file in os.listdir(path):
        if (len(file) < 18):
            txt_file = np.loadtxt(path +'/'+ file)
            size = len(txt_file)
            t_all.append(txt_file[:,0])           #ukupno vrijeme
            x_tocka_all.append(txt_file[:,1])    #x-kordinate tocke
            y_tocka_all.append(txt_file[:,2])
        else:
            txt_file = np.loadtxt(path +'/'+ file)
            size_const = len(txt_file)
            t_const_all.append(txt_file[:,0])           #ukupno vrijeme
            x_tocka_const_all.append(txt_file[:,1])    #x-kordinate tocke
            y_tocka_const_all.append(txt_file[:,2])
    return t_all[0], x_tocka_all, y_tocka_all,t_const_all[0], x_tocka_const_all, y_tocka_const_all

def field_def():
    pos_y, pos_x = np.mgrid[-3:3:30j, -3:3:30j]
    vx = -pos_y/(pos_x**2+pos_y**2)
    vy = pos_x/(pos_x**2+pos_y**2)
    speed = np.sqrt(vx ** 2 + vy ** 2)
    u_n = vx / speed
    v_n = vy / speed
        
    return pos_x, pos_y, vx, vy, u_n, v_n, speed

def plot_graf ( t = [], x = [], y = [], pos_x = [], pos_y = [], u_n = [], v_n = [], velocity = []):
        size = len(x[0])        
        inc = 10
        fig, ax = plt.subplots()
        plt.axis([-2, 2, -2, 2])
        sliderax = fig.add_axes([0.2, 0.02, 0.6, 0.03],
                                          axisbg='yellow')

        ax.quiver(pos_x, pos_y, u_n, v_n,  # data
                       velocity,  # colour the arrows based on this array
                       cmap=cm.Accent,  # colour map
                       headlength=7)  # length of the arrows
                       
        slider = Slider(sliderax, 'Value', 0, size , valinit=inc)
        for i in range (0, len(x)):
            ax.plot(x [i] [0:inc], y [i] [0:inc],'ro')
        return fig, ax, sliderax, slider

def update(value):
    val = int (value)
    t_slider = t [0:val]
    slider1.valtext.set_text(val)
    for i in range (0, len(x_tocka)):
        ax.plot(x_tocka[i] [0:val], y_tocka[i] [0:val],'ro')
        fig1.canvas.draw_idle()

if __name__ == '__main__' :
    t, x_tocka, y_tocka, t_const, x_tocka_const, y_tocka_const = read_file('../results')
    # citanje svih txt dokumenta u folderu i stvaranje vektora vremena (t),
    # x-korrdinate(x_tocka), y-korrdinate(y_tocka) za nestacionarno i stacionarno vektorsko polje

    x_field, y_field, u, v, u_n, v_n, velocity = field_def()
    # stvaranje vektora x-koordinate(x_field), y-koordinate(y_field),
    # brzine u smjeru osi x(u), brzine u smjeru osi y(v), intenzitet brzine (velocity)
    # jedinicna brzina u smjeru osi x (u_n), jedinicna brzina u smjeru osi x (v_n)

    
    fig1, ax, sliderax, slider1 = plot_graf(t, x_tocka, y_tocka, x_field, y_field, u_n, v_n, velocity)
    fig1.show()
    slider1.on_changed(update)
#    slider.drawon = False

    
    

