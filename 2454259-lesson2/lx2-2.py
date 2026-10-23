head=int(input("请输入鸡兔的总只数："))
foot=int(input("请输入鸡兔的总脚数："))
x=int(2*head-foot/2)
y=int(foot/2-head)
if foot % 2 == 0 and x > 0 and y>0:
    print(f"鸡有{x}只，兔有{y}只")
elif foot%2==1:
    print("由于鸡有两只脚，兔有四只脚，都是偶数，则总脚数一定是偶数，你的数据有问题哦！")
elif x<=0 or y<=0:
    print("求出来的鸡和兔的只数应该为正数，你的数据有问题哦！")