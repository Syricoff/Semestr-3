import math
import matplotlib.pyplot as plt
import numpy as np 

# этап 1 считываем точку

px,py = map( float, input('Введите координаты точки: ' ).split() )
x,y = px,py
in_graph = ( 0 <= y <= math.sqrt(x) ) ^  ( x**2 + y**2 - 4*x <= 0 )

point_color = 'g' if in_graph else 'r'

if in_graph:
	print("Входит")
else: 
	print("Не входит")


# этап 2
# рисуем чёрные полоски

def xy(r,phi):
  return r*np.cos(phi)+2, r*np.sin(phi)

fig = plt.figure()
ax = fig.add_subplot(111,aspect='equal')  

phis=np.arange(0,6.28,0.01)
r =2.
ax.plot( *xy(r,phis), c='k',ls='-' )


Nx = 1000
x = np.linspace(0,50,Nx)
y = np.sqrt(x)

max_x = 10

plt.plot(np.linspace(0, max_x, Nx),
    np.sqrt(np.linspace(0, max_x, Nx)),
    color='k'
    )

plt.plot( np.linspace(0, max_x, Nx),
    np.linspace(0, 0, Nx),
    color= 'k'
    )

plt.plot( 

    np.linspace(max_x, max_x, Nx),
        np.linspace(0, math.sqrt(max_x), Nx),
    color= 'k'
    )


# этап 3
# заливаю синим
x = np.arange(0,max_x, max_x / Nx )

c1 = 2 * np.cos ( np.arcsin( x / 2 - 1 ) )
s = np.sqrt( x )

c2 = -2 * np.cos ( np.arcsin( x / 2 - 1 ) )
l = x * 0

ax.fill_between( x, c1, s , color='b')
ax.fill_between( x, c2, l , color='b')


x = np.arange(4,max_x, max_x / Nx )
s = np.sqrt( x )
l = x * 0

ax.fill_between( x, l, s , color='b')


# этап 4 рисую точку
plt.plot( px ,py, color=point_color, marker = 'o', markersize = 10 )



plt.show()
