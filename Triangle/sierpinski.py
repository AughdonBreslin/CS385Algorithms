def draw_sierpinski(length, depth):
  if depth == 0:
    for i in range(3):
      print("/" * length)
      print(" " * (length // 2) + "\\")
  else:
    draw_sierpinski(length // 2, depth - 1)
    print("_" * (length // 2))
    draw_sierpinski(length // 2, depth - 1)
    print("_" * (length // 2))
    draw_sierpinski(length // 2, depth - 1)

# Set the length of the triangle's side
length = 10

# Set the depth of the triangle
depth = 3

# Draw the triangle
draw_sierpinski(length, depth)