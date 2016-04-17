# -*- coding: utf-8 -*-
"""
Created on Sun Mar 20 14:28:54 2016

@author: adnen
"""

from pylab import *
from matplotlib.widgets import Slider, Button, RadioButtons    
X0=[0,0]

v1 = 0.64 

v2 = -1.76


theta1 = np.pi + v2
theta2 = v1 -v2 + np.pi
a1 = 5
a2 = 5
a3 = 2
X1=[X0[0]+ np.cos(theta1)*a1,X0[1]+ np.sin(theta1)*a1]
X2=[X1[0]+ np.cos(theta2+theta1)*a2,X1[1]+ np.sin(theta2+theta1)*a2]
 
X=[X0[0],X1[0],X2[0]]
Y=[X0[1],X1[1],X2[1]]

X3 = [X0[0]+ a3 * np.cos(np.pi + v1), X0[1] + a3 * np.sin( np.pi + v1)]
X4 = [X3[0]+ a1 * np.cos(v2 +np.pi), X3[1] + a1 * np.sin(v2 + np.pi)]

ax = subplot(111)
subplots_adjust(left=0.25, bottom=0.25)
t = arange(0.0, 1.0, 0.001)
a0 = 5
f0 = 3
s = a0*sin(2*pi*f0*t)
l, =plot(X,Y,'ro-', linewidth=2)
l2,=plot([X0[0],X3[0],X4[0],X1[0]],[X0[1],X3[1],X4[1],X1[1]], 'bo-', linewidth=2)
#l, = plot(t,s, lw=2, color='red')
axis([-5, 15, -4, 10])
grid()

axcolor = 'lightgoldenrodyellow'
axfreq = axes([0.25, 0.1, 0.65, 0.03], axisbg=axcolor)
axamp  = axes([0.25, 0.15, 0.65, 0.03], axisbg=axcolor)

sfreq = Slider(axfreq, 'V1', -pi/2, pi/2, valinit=v1)
samp = Slider(axamp, 'V2', -pi, 0, valinit=v2)  
def update(val):
    v2 = samp.val
    v1 = sfreq.val
    theta1 = np.pi + v2
    theta2 = v1 -v2 + np.pi
    X1=[X0[0]+ np.cos(theta1)*a1,X0[1]+ np.sin(theta1)*a1]
    X2=[X1[0]+ np.cos(theta2+theta1)*a2,X1[1]+ np.sin(theta2+theta1)*a2]
     
    X=[X0[0],X1[0],X2[0]]
    Y=[X0[1],X1[1],X2[1]]
    
    X3 = [X0[0]+ a3 * np.cos(np.pi + v1), X0[1] + a3 * np.sin( np.pi + v1)]
    X4 = [X3[0]+ a1 * np.cos(v2 +np.pi), X3[1] + a1 * np.sin(v2 + np.pi)]

    l.set_xdata(X)
    l.set_ydata(Y)
    l2.set_xdata([X0[0],X3[0],X4[0],X1[0]])
    l2.set_ydata([X0[1],X3[1],X4[1],X1[1]])
    draw()
sfreq.on_changed(update)
samp.on_changed(update)

resetax = axes([0.8, 0.025, 0.1, 0.04])
button = Button(resetax, 'Reset', color=axcolor, hovercolor='0.975')
def reset(event):
    sfreq.reset()
    samp.reset()
button.on_clicked(reset)

rax = axes([0.025, 0.5, 0.15, 0.15], axisbg=axcolor)
radio = RadioButtons(rax, ('red', 'blue', 'green'), active=0)
def colorfunc(label):
    l.set_color(label)
    draw()
radio.on_clicked(colorfunc)

show()

teta2 = np.arccos((X2[0]**2 + X2[1]**2 - a1**2 - a2**2)/(2* a1 *a2))
teta1 = np.arctan(X2[1]/X2[0]) + np.arccos((a1**2 - a2**2 + X2[0]**2 + X2[1]**2)/( 2 * a1 *np.sqrt(X2[0]**2 + X2[1]**2)))

V2 = teta1 - np.pi
V1 = teta1 - teta2
def get_angles(x,y):
    x = x * 1.0
    y = y* 1.0
    if(x==0):
        tet = np.pi/2
    else:
        tet = np.arctan(y/x)
    
    tet2 = np.arccos((x**2 + y**2 - a1**2 - a2**2)/(2* a1 *a2))
    tet1 = tet + np.arccos((a1**2 - a2**2 + x**2 + y**2)/( 2 * a1 *np.sqrt(x**2 + y**2)))
    if (x>0):    
        v2 = tet1 - np.pi
        v1 = tet1 - tet2
    elif(x<0):
        v2 = tet1
        v1 = tet1 - tet2 + np.pi
    return v1, v2
