import matplotlib.pyplot as plt

plt.figure(1, figsize=(12, 7))

times = []
r = 0
with open("ellipse_time_res.txt", "r") as f:
    rx = float(f.readline().replace(",", "."))
    ry = float(f.readline().replace(",", "."))

    for line in f:
        times.append(float(line.replace(",", ".")) * 1000000)

y = range(len(times))

L = ("Каноническое", "Параметрическое", "Брезенхем", "Средняя точка")

plt.title("Эллипсы")
plt.bar(y, times)
plt.xticks(y, L)

plt.ylabel(f"Время в мкс\nрадиус по х - {rx}, радиус по y - {ry}")
plt.show()
