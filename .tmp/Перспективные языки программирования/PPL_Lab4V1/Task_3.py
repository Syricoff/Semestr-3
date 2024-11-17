import matplotlib.pyplot as plt
import numpy as np


x = np.arange(0, 5)
y1 = 2 * x + 1
y2 = -2 * x + 5
fig, ax = plt.subplots()

ax.plot(x, y1, color='blue', label='y = 2x + 1', lw=3)
ax.plot(x, y2, color='red', label='y = 5 - 2x', lw=3)
ax.fill_between(x, y2, 9 + y2 + y1, color='yellow')
ax.fill_between(x, y2, 0 - y1 - y2, color='yellow')
ax.fill_between(x, y1, y2, color='green')
ax.legend(loc='upper left')
plt.show()
