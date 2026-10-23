sentence=input("请输入一个英文句子:")
new_sentence=""
for i in sentence:
    if 97 <= ord(i) <= 122:
        new_sentence+=chr(ord(i)-32)
    else:
        new_sentence+=i

chars=list(set(new_sentence))
chars.sort()
freq={}
for i in chars:
    if 65<=ord(i)<=90:
        num = new_sentence.count(i)
        freq[i] = num
print(freq)