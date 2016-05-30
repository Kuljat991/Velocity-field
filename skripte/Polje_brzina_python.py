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

class field:
    def __init__(self, path = ''):
        
        txt_file = np.loadtxt(path)
        size = len(txt_file)
        self.t_all =txt_file[:,0]           #ukupno vrijeme
        self.x_tocka_all = txt_file[:,1]    #x-kordinate tocke
        self.y_tocka_all = txt_file[:,2]    #y-koordinate tocke
        
        inc = 10                            #pocetna pozicija slidera
        self.fig, self.ax = plt.subplots()
        plt.axis([-2, 2, -2, 2])
        self.sliderax = self.fig.add_axes([0.2, 0.02, 0.6, 0.03],
                                          axisbg='yellow')
        
        self.t_trenutni = self.t_all[inc]   #vijeme na pocetnoj poziciji slidera
        self.pos_x, self.pos_y, self.u, self.v, self.u_n, self.v_n, self.velocity = self.field_def(self.t_trenutni)
        
        self.t = self.t_all[0:inc]    
        self.x_tocka = self.x_tocka_all[0:inc]
        self.y_tocka = self.y_tocka_all[0:inc]

        self.ax.quiver(self.pos_x, self.pos_y, self.u_n, self.v_n,  # data
                       self.velocity,  # colour the arrows based on this array
                       cmap=cm.Accent,  # colour map
                       headlength=7)  # length of the arrows

#        self.ax.colorbar()  # adds the colour bar

        self.slider = Slider(self.sliderax, 'Value', 0, size , valinit=inc)
        self.slider.on_changed(self.update)
        self.slider.drawon = False

        self.ax.plot(self.x_tocka, self.y_tocka,'ro') #crtanje tocke do poetnbog vremena na slideru


    def field_def(self,t):
        pos_y, pos_x = np.mgrid[-3:3:30j, -3:3:30j]
        vx = -pos_y/(pos_x**2+pos_y**2 )+ 0.2*sin(t)
        vy = pos_x/(pos_x**2+pos_y**2) + 0.2*cos(t)
        speed = np.sqrt(vx ** 2 + vy ** 2)
        u_n = vx / speed
        v_n = vy / speed

        return pos_x, pos_y, vx, vy, u_n, v_n, speed
        
    def update(self, value):
        val = int (value)
        self.t_trenutni = self.t_all[val-1]
        self.t = self.t_all[0:val]
        self.x_tocka = self.x_tocka_all[0:val-1]
        self.y_tocka = self.y_tocka_all[0:val-1]
        self.slider.valtext.set_text(val)
        self.ax.quiver(self.pos_x, self.pos_y, self.u_n, self.v_n,  # data
                       self.velocity,  # colour the arrows based on this array
                       cmap=cm.Accent,  # colour map
                       headlength=7)  # length of the arrows
        self.ax.plot(self.x_tocka, self.y_tocka,'ro')
        self.fig.canvas.draw_idle()
#        print(self.t)
        
    def show(self):
        plt.show()


class field_const:
    def __init__(self, path = ''):
        self.pos_x, self.pos_y, self.u, self.v, self.u_n, self.v_n, self.velocity = self.field_def()      
        
        txt_file = np.loadtxt(path)
        size = len(txt_file)
        self.t_all =txt_file[:,0]
        self.x_tocka_all = txt_file[:,1]
        self.y_tocka_all = txt_file[:,2]        
        
        inc = 10
        self.fig, self.ax = plt.subplots()
        plt.axis([-2, 2, -2, 2])
        self.sliderax = self.fig.add_axes([0.2, 0.02, 0.6, 0.03],
                                          axisbg='yellow')
        
        self.t = self.t_all[0:inc]    
        self.x_tocka = self.x_tocka_all[0:inc]
        self.y_tocka = self.y_tocka_all[0:inc]

        self.ax.quiver(self.pos_x, self.pos_y, self.u_n, self.v_n,  # data
                       self.velocity,  # colour the arrows based on this array
                       cmap=cm.Accent,  # colour map
                       headlength=7)  # length of the arrows

#        self.ax.colorbar()  # adds the colour bar

        self.slider = Slider(self.sliderax, 'Value', 0, size , valinit=inc)
        self.slider.on_changed(self.update)
        self.slider.drawon = False

        self.ax.plot(self.x_tocka, self.y_tocka,'ro')


    def field_def(self):
        pos_y, pos_x = np.mgrid[-3:3:30j, -3:3:30j]
        vx = -pos_y/(pos_x**2+pos_y**2)
        vy = pos_x/(pos_x**2+pos_y**2)
        speed = np.sqrt(vx ** 2 + vy ** 2)
        u_n = vx / speed
        v_n = vy / speed

        return pos_x, pos_y, vx, vy, u_n, v_n, speed
        
    def update(self, value):
        val = int (value)
        self.t = self.t_all[0:val]
        self.x_tocka = self.x_tocka_all[0:val]
        self.y_tocka = self.y_tocka_all[0:val]
        self.slider.valtext.set_text(val)
        self.ax.plot(self.x_tocka, self.y_tocka,'ro')
        self.fig.canvas.draw_idle()
#        print(self.t)
        
    def show(self):
        plt.show()

if __name__ == '__main__' :
    p = field_const(path = '../results/VectorField_const.txt')
    p1 = field(path = '../results/VectorField.txt')

