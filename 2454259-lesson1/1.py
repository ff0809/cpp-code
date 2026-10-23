try:
    num=int(input("请输入一个小于9的数字n："))
    if num>=9:
        print("数字过大，请输入小于9的数字。")
    else:
        for i in range(1,num+1):
            for j in range (1,i+1):
                print(f"{j}*{i}={j*i}",end=" ")
            print()
except :
    print("无效输入，请输入一个整数。")