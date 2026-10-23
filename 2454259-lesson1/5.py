import turtle
import random

screen = turtle.Screen()
screen.title("随机射线星图")
screen.bgcolor("black")  

pen = turtle.Turtle()
pen.speed(0)  
pen.hideturtle()  

colors = ["red", "orange", "yellow", "green", "blue", "purple", "pink", 
          "white", "cyan", "magenta", "gold", "silver"]

def draw_random_star():

    pen.color(random.choice(colors))  
    pen.pensize(random.randint(1, 10))  

    x = random.randint(-screen.window_width()//2, screen.window_width()//2)
    y = random.randint(-screen.window_height()//2, screen.window_height()//2)
    pen.penup()
    pen.goto(x, y)
    pen.pendown()
    
    sides = random.randint(8, 15) 
    size = random.randint(20, 100)  
    
    for i in range(sides):
        line_length = random.randint(size//2, size)
        pen.forward(line_length)
        pen.backward(line_length)
        pen.right(360 / sides)

while True:
    draw_random_star()

turtle.done()