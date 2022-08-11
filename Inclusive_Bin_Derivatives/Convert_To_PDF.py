import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

w = 10
h = 10

fig = plt.figure(figsize=(8, 8),dpi=94)
columns = 4
rows = 5
for i in range(1, columns*rows +1):
    img = np.random.randint(10, size=(h,w))
    fig.add_subplot(rows, columns, i)
    plt.imshow(img,  interpolation="spline36",)
plt.savefig("./test.png")
