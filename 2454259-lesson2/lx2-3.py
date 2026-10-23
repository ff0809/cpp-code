import math
a=float(input("请输入一元二次方程ax²+bx+c=0的二次项系数a："))
b=float(input("请输入一元二次方程ax²+bx+c=0的一次项系数b："))
c=float(input("请输入一元二次方程ax²+bx+c=0的常数项c："))
if b*b-4*a*c<0:
    print("无实根")
else:
    x1=(-b-math.sqrt(b*b-4*a*c))/(2*a)
    x2=(-b+math.sqrt(b*b-4*a*c))/(2*a)
    if x1==x2:
        print(f"该方程有两个相等的实根：{x1}")
    else:
        print(f"该方程有两个不相等的实根：{x1}，{x2}")