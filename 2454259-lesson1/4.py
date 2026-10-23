num = int(input("输入4位数字："))

while num != 6174:
    s = f"{num:04d}" 
    sorted_jiang = ''.join(sorted(s, reverse=True))  
    sorted_sheng = ''.join(sorted(s))
    num = int(sorted_jiang) - int(sorted_sheng)
    print(f"{sorted_jiang}-{sorted_sheng}={num:04d}")