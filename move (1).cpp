#include <vector>
#include <chrono>
#include <iostream>

int main() {
    // 大对象
    std::vector<int> large_vec(1000000, 42);

    auto start1 = std::chrono::high_resolution_clock::now();
    std::vector<int> copy_vec = large_vec;  // 拷贝
    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    std::vector<int> move_vec = std::move(large_vec);  // 移动
    auto end2 = std::chrono::high_resolution_clock::now();

    auto copy_time = std::chrono::duration<double>(end1 - start1).count();
    auto move_time = std::chrono::duration<double>(end2 - start2).count();

    std::cout << "拷贝耗时: " << copy_time << " 秒\n";
    std::cout << "移动耗时: " << move_time << " 秒\n";

    return 0;
}
// 输出示例：
// 拷贝耗时: 0.002345 秒  (需要复制100万个元素)
// 移动耗时: 0.000001 秒  (只是复制几个指针)