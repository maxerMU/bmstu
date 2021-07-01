import matplotlib.pyplot as plt

plt.figure(1, figsize=(16, 12))
plt.subplot(211)

circle_times = []
with open("circle_time_res.txt", "r") as f:
    rmin = int(f.readline().replace(",", "."))
    rmax = int(f.readline().replace(",", "."))
    rstep = int(f.readline().replace(",", "."))

    for line in f:
        circle_times.append(float(line.replace(",", ".")) * 1000000)

x = range(rmin, rmax, rstep)
n = (rmax - rmin) // rstep

plt.plot(x, circle_times[0:n], label="Каноническое")
plt.plot(x, circle_times[n:2*n], label="Параметрическое")
plt.plot(x, circle_times[2*n:3*n], label="Брезенхем")
plt.plot(x, circle_times[3*n:4*n], label="Средняя точка")

plt.title("Окружности")

plt.xlabel("Радиус окружности")
plt.ylabel("Время в мкс * 10000")

plt.grid(True)
plt.legend(loc=0)

plt.subplot(212)
#plt.figure(2, figsize=(12, 7))

ellipse_times = []
with open("ellipse_time_res.txt", "r") as f:
    rx = int(f.readline().replace(",", "."))
    ry = int(f.readline().replace(",", "."))
    step = int(f.readline().replace(",", "."))
    n = int(f.readline().replace(",", "."))

    for line in f:
        ellipse_times.append(float(line.replace(",", ".")) * 1000000)

plt.title("Эллипсы")

x = range(rx, rx + step * n, step)
plt.plot(x, ellipse_times[0:n], label="Каноническое")
plt.plot(x, ellipse_times[n:2*n], label="Параметрическое")
plt.plot(x, ellipse_times[2*n:3*n], label="Брезенхем")
plt.plot(x, ellipse_times[3*n:4*n], label="Средняя точка")

plt.xlabel("x полуось")
plt.ylabel(f"Время в мкс * 10000\nначальное значение y полуоси - {ry}")
plt.grid(True)
plt.legend(loc=0)

plt.show()
