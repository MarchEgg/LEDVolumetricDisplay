import math as m

points = [[2.8, 2.8, 5.6],
  [-2.8, 2.8, 5.6],
  [2.8, -2.8, 5.6],
  [-2.8, -2.8, 5.6],
  [2.8, 2.8, 0],
  [-2.8, 2.8, 0],
  [2.8, -2.8, 0],
  [-2.8, -2.8, 0]]

polar = []

for point in points:
    r = m.sqrt(point[0]**2 + point[1]**2)
    theta = m.atan2(point[1], point[0])
    polar.append([r, theta, point[2]])

print("Polar coordinates:")
for p in polar:
    print(f"r: {p[0]:.2f}, θ: {p[1]:.2f}, z: {p[2]}")