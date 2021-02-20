from random import randint, choice

file = open("in.txt", "w")
s = "asdfghjklqwertyuiopzxcvbnm"
for i in range(1000):
    for i in range(randint(3, 15)):
        file.write(choice(s))

    file.write(" ")

    for i in range(randint(3, 10)):
        file.write(choice(s))

    file.write(" ")

    if randint(0, 1):
        file.write("+")
    for i in range(randint(12, 14)):
        file.write(str(randint(0, 9)))

    file.write(" ")

    for i in range(randint(7, 30)):
        file.write(choice(s + " ,"))

    file.write(". ")

    i = randint(0, 1)

    file.write(str(i) + ' ')


    if i:
        for i in range(randint(3, 10)):
            file.write(choice(s))
        file.write(" ")
        for i in range(randint(3, 15)):
            file.write(choice(s))


    else:
        file.write(str(randint(1900, 2020)) + ' ')

        file.write(str(randint(1, 12)) + ' ')

        file.write(str(randint(1, 28)) + ' ')

    file.write("\n")


file.close()
