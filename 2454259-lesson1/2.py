import re

def display_length(s):
    chinese_chars = re.findall(r'[\u4e00-\u9fff]', s)  
    return len(s) + len(chinese_chars)  

str_input = input("请输入一个字符串：")
total_width = 48 
str_display_len = display_length(str_input)

space_left = (total_width - str_display_len) // 2
space_right = total_width - str_display_len - space_left

content_line = "*" + " " * space_left + str_input + " " * space_right + "*"

print("*" * 50)
print("*" + " " * 48 + "*")
print("*" + " " * 48 + "*")
print(content_line)
print("*" + " " * 48 + "*")
print("*" + " " * 48 + "*")
print("*" * 50)