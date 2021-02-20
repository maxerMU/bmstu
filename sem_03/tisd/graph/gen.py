from random import *

f = open("input.txt", "w")
nodes = 20
for i in range(nodes):
    edges = randint(0, nodes / 5)
    for j in range(edges):
        f.write(f"{randint(0,1)} {i} {randint(0,nodes - 1)} {randint(1, nodes * 10)}\n")
f.write("-1\n")
f.close()
