import matplotlib.pyplot as plt

plt.figure(1, figsize=(12, 7))

times = []
r = 0
with open("time_res.txt", "r") as f:
    r = float(f.readline())
    for line in f:
        times.append(float(line) * 1000000)

y = range(len(times))

L = ("ЦДА", "Брезенхем\nдействительный", "Брезенхем\nцелочисленный", "Брезенхем\nсглаживающий", "Ву")

plt.bar(y, times)
plt.xticks(y, L)

plt.ylabel(f"Время в мкс\nДлина отрезка - {r}")
plt.show()