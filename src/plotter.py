#!/usr/local/bin/python3.6
import matplotlib.pyplot as plt
import matplotlib as mpl

mpl.rcParams['savefig.dpi'] = 300

size = 1000
numbersFile = open("../Prosjekt 1/output/cluster.txt", "r")
values = [int(line) for line in numbersFile.readlines()]
xs = []
ys = []

for node in values:
    x = node % size
    y = node // size
    xs.append(x)
    ys.append(y)

plt.plot(xs, ys, ".", rasterized=True)
plt.xlabel("x")
plt.ylabel("y")
plt.xlim(0, size)
plt.ylim(0, size)
#plt.axis("off")
plt.title("Network")
plt.savefig("./output/activation15.pdf", bbox_inches="tight", pad=0)
plt.show()
