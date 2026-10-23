line=int(input("请输入三角形的行数（1-26）："))
n=65
for i in range(line):
    print(" " * (line-i-1),end="")
    for j in range(2 * i + 1):
        print(chr(n), end="")
        n += 1
        if n == 91:
            n = 65
    print()