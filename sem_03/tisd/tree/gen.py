from random import randint, choice

file = open("test.txt", "w")

for i in range(500):
    file.write(str(randint(1, 10000)) + " ")


file.close()

