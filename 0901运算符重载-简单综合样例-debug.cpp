#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <stdexcept>

class StudentScore {
private:
    int studentId;
    float* scores;  // 存储多个科目的成绩
    int subjectCount;
    char name[50];

public:
    // 构造函数
    StudentScore(int id, const char* studentName, int count)
        : studentId(id), subjectCount(count) {

        // 分配内存存储成绩
        scores = new float[subjectCount];
        for (int i = 0; i < subjectCount; i++) {
            scores[i] = 0.0f;  // 初始化为0分
        }

        // 复制学生姓名
        strcpy(name, studentName);
    }

    // 析构函数 
    ~StudentScore() {
        delete[] scores;
    }

    // 拷贝构造函数 
    StudentScore(const StudentScore& other) {
        studentId = other.studentId;
        subjectCount = other.subjectCount;
        strcpy(name, other.name);

        scores = new float[subjectCount];
        for (int i = 0; i < subjectCount; i++) {
            scores[i] = other.scores[i];
        }
    }

    // 1. 重载赋值运算符 = 
    StudentScore& operator=(const StudentScore& other) {
        if (this != &other) {  // 防止自赋值
            // 删除原有内存
            delete[] scores;

            // 复制基本数据
            studentId = other.studentId;
            subjectCount = other.subjectCount;
            strcpy(name, other.name);

            // 分配新内存并复制成绩
            scores = new float[subjectCount];
            for (int i = 0; i < subjectCount; i++) {
                scores[i] = other.scores[i];
            }
        }
        return *this;  // 支持链式赋值
    }

    // 2. 重载下标运算符 [] 
    float& operator[](int index) {
        if (index < 0 || index >= subjectCount) {
            throw std::out_of_range("科目索引超出范围");
        }
        return scores[index];
    }

    // 3. 重载函数调用运算符 ()
    // 可以用于计算平均分、总成绩等
    float operator()(const char* operation) const {
        if (strcmp(operation, "average") == 0) {
            // 计算平均分
            float sum = 0;
            for (int i = 0; i < subjectCount; i++) {
                sum += scores[i];
            }
            return (subjectCount > 0) ? sum / subjectCount : 0.0f;
        }
        else if (strcmp(operation, "total") == 0) {
            // 计算总成绩
            float sum = 0;
            for (int i = 0; i < subjectCount; i++) {
                sum += scores[i];
            }
            return sum;
        }
        else if (strcmp(operation, "max") == 0) {
            // 找最高分
            if (subjectCount == 0) return 0.0f;
            float maxScore = scores[0];
            for (int i = 1; i < subjectCount; i++) {
                if (scores[i] > maxScore) {
                    maxScore = scores[i];
                }
            }
            return maxScore;
        }
        else {
            throw std::invalid_argument("未知的操作类型");
        }
    }

    // 4. 重载成员访问运算符 ->
    // 返回一个可以访问学生信息的指针
    StudentScore* operator->() {
        return this;  // 返回当前对象的指针
    }

    // 一些辅助函数
    void display() const {
        std::cout << "学生ID: " << studentId << std::endl;
        std::cout << "姓名: " << name << std::endl;
        std::cout << "各科成绩: ";
        for (int i = 0; i < subjectCount; i++) {
            std::cout << scores[i] << " ";
        }
        std::cout << std::endl;
    }

    int getId() const { return studentId; }
    const char* getName() const { return name; }

    // 设置所有成绩
    void setAllScores(float* newScores) {
        for (int i = 0; i < subjectCount; i++) {
            scores[i] = newScores[i];
        }
    }
};

// 一个简单的学生管理器类
class StudentManager {
private:
    StudentScore** students;
    int capacity;
    int count;

public:
    StudentManager(int maxStudents) : capacity(maxStudents), count(0) {
        students = new StudentScore * [capacity];
        for (int i = 0; i < capacity; i++) {
            students[i] = nullptr;
        }
    }

    ~StudentManager() {
        for (int i = 0; i < count; i++) {
            delete students[i];
        }
        delete[] students;
    }

    void addStudent(const StudentScore& student) {
        if (count < capacity) {
            students[count] = new StudentScore(student);
            count++;
        }
    }

    StudentScore* getStudent(int index) {
        if (index >= 0 && index < count) {
            return students[index];
        }
        return nullptr;
    }
};

int main() {
    std::cout << "======= 学生成绩管理系统 =======" << std::endl;

    // 创建几个学生
    StudentScore student1(1001, "张三", 3);  // 3个科目
    StudentScore student2(1002, "李四", 3);

    // 1. 使用下标运算符[]设置和获取成绩
    std::cout << "\n1. 使用下标运算符[]设置和获取成绩:" << std::endl;

    // 设置成绩
    student1[0] = 85.5f;  // 语文
    student1[1] = 92.0f;  // 数学
    student1[2] = 78.5f;  // 英语

    // 获取成绩
    std::cout << student1.getName() << "的成绩:" << std::endl;
    std::cout << "语文: " << student1[0] << std::endl;
    std::cout << "数学: " << student1[1] << std::endl;
    std::cout << "英语: " << student1[2] << std::endl;

    // 2. 使用函数调用运算符()进行统计计算
    std::cout << "\n2. 使用函数调用运算符()进行统计计算:" << std::endl;

    std::cout << student1.getName() << "的统计信息:" << std::endl;
    std::cout << "平均分: " << student1("average") << std::endl;
    std::cout << "总分: " << student1("total") << std::endl;
    std::cout << "最高分: " << student1("max") << std::endl;

    // 3. 使用赋值运算符=复制学生信息
    std::cout << "\n3. 使用赋值运算符=复制学生信息:" << std::endl;

    StudentScore student3 = student1;  // 使用拷贝构造函数
    student3.display();

    // 修改student2的成绩
    float scores[3] = { 90.0f, 88.5f, 95.0f };
    student2.setAllScores(scores);

    // 使用赋值运算符
    student3 = student2;  // student3现在有和student2一样的数据
    std::cout << "\n赋值后student3的信息:" << std::endl;
    student3.display();

    // 4. 使用成员访问运算符->访问成员函数
    std::cout << "\n4. 使用成员访问运算符->访问成员函数:" << std::endl;

    // 创建学生管理器
    StudentManager manager(10);
    manager.addStudent(student1);
    manager.addStudent(student2);

    // 获取第一个学生并使用->访问成员
    StudentScore* firstStudent = manager.getStudent(0);
    if (firstStudent) {
        // 使用->运算符访问成员函数
        std::cout << "第一个学生的信息:" << std::endl;
        std::cout << "ID: " << firstStudent->getId() << std::endl;
        std::cout << "姓名: " << firstStudent->getName() << std::endl;
        std::cout << "平均分: " << firstStudent->operator()("average") << std::endl;

        // 或者更自然地使用
        std::cout << "\n另一种使用方式:" << std::endl;
        std::cout << "数学成绩: " << (*firstStudent)[1] << std::endl;
    }

    // 5. 综合使用所有运算符
    std::cout << "\n5. 综合使用所有运算符的例子:" << std::endl;

    // 创建一个新学生 - 错误5: 尝试创建StudentScore数组，但构造函数参数不正确
    StudentScore student4[3] = {
        StudentScore(1003, "王五", 3),
        StudentScore(1004, "赵六", 3),
        StudentScore(1005, "孙七", 3)
    };

    // 使用[]设置成绩
    student4[0][0] = 75.0f;
    student4[0][1] = 82.0f;
    student4[0][2] = 91.5f;

    // 使用()计算统计信息
    float avg = student4[0]("average");
    float total = student4[0]("total");

    std::cout << student4[0].getName() << "的成绩统计:" << std::endl;
    std::cout << "平均分: " << avg << std::endl;
    std::cout << "总分: " << total << std::endl;

    // 创建副本并修改
    StudentScore student5 = student4[0];  // 使用拷贝构造函数
    student5[0] = 88.0f;  // 修改语文成绩

    std::cout << "\n修改后学生5的语文成绩: " << student5[0] << std::endl;
    std::cout << "学生4[0]的语文成绩保持不变: " << student4[0][0] << std::endl;

    // 使用->访问成员
    StudentScore* ptr = &student5;
    std::cout << "\n通过指针访问学生5的姓名: " << ptr->getName() << std::endl;

    // 链式赋值示例
    StudentScore student6(1006, "周八", 3);
    student6 = student5 = student4[0];  // 链式赋值

    std::cout << "\n链式赋值后学生6的数学成绩: " << student6[1] << std::endl;

    return 0;
}