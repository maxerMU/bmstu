import matplotlib.pyplot as plt

plt.figure(1)

r = 0
angle_step = 0

with open("stairs_res.txt", "r") as f:
    r = float(f.readline().replace(",", "."))
    angle_step = float(f.readline().replace(",", "."))
    angle_step = int(angle_step)

    stairs = []
    for line in f:
        stairs.append(float(line.replace(",", ".")))

plt.title("Анализ ступенчатости")
plt.xlabel("Угол наклона прямой")
plt.ylabel(f"Число ступеней\nДлина отрезка - {r}")
plt.grid(True)

angles = range(0, 365, angle_step)

plt.plot(angles, stairs)
plt.show()