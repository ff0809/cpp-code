d={"0":"zero","1":"one","2":"two","3":"three","4":"four","5":"five","6":"six","7":"seven","8":"eight","9":"nine"}
phone=input("请输入电话号码:")
for i in range(len(phone)-1):
    print(d[phone[i]],end="-")
print(d[phone[len(phone)-1]])