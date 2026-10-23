import random
matrix = []
for _ in range(10):
    row = [random.randint(0, 1) for _ in range(10)]
    matrix.append(row)
print("原始10x10矩阵：")
for row in matrix:
    print(' '.join(map(str, row)))

max_square = 0  # 最大面积
up_position = 0  # 顶行位置
left_position = 0  # 左列位置
height = 0  # 矩形高度
width = 0  # 矩形宽度
for i in range(10):
    for j in range(10):
        if matrix[i][j]==0:
            continue
        for k in range(i,10):
            for l in range(j,10):
                all_one=True
                for m in range(i,k+1):
                    if not all_one:
                        break
                    for n in range(j,l+1):
                        if matrix[m][n]==0:
                            all_one=False
                            break
                if all_one:
                    current_square=(k-i+1)*(l-j+1)
                    if current_square > max_square:
                        max_square = current_square
                        up_position = i
                        left_position = j
                        height = k - i + 1
                        width = l - j + 1
print(f"找到最大全1矩形：面积={max_square}，位置：顶行={up_position}，左列={left_position}，高度={height}，宽度={width}")
for i in range(up_position,up_position+height):
    for j in range(left_position,left_position+width):
        matrix[i][j]='*'
print("替换后的矩阵：")
for row in matrix:
    print(' '.join(map(str, row)))