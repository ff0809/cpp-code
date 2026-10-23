//#include <iostream>
//using namespace std;
//
//class Employee {
//protected:
//    string name;
//    double baseSalary;
//public:
//    Employee(const string& n, double salary)
//        : name(n), baseSalary(salary) {
//    }
//
//    // 虚函数 - 计算总薪资
//    virtual double calculatePay() const {
//        return baseSalary;  // 基础员工只有基本工资
//    }
//
//    virtual void displayInfo() const {
//        cout << "员工: " << name
//            << ", 薪资: " << calculatePay() << endl;
//    }
//
//    virtual ~Employee() = default;
//};
//
//class Manager : public Employee {
//private:
//    double bonus;
//public:
//    Manager(const string& n, double salary, double b)
//        : Employee(n, salary), bonus(b) {
//    }
//
//    // 重写计算薪资方法
//    double calculatePay() const override {
//        return baseSalary + bonus;  // 经理有基本工资+奖金
//    }
//
//    void displayInfo() const override {
//        cout << "经理: " << name
//            << ", 基本工资: " << baseSalary
//            << ", 奖金: " << bonus
//            << ", 总薪资: " << calculatePay() << endl;
//    }
//};
//
//class SalesPerson : public Employee {
//private:
//    double sales;
//    double commissionRate;
//public:
//    SalesPerson(const string& n, double salary, double s, double rate)
//        : Employee(n, salary), sales(s), commissionRate(rate) {
//    }
//
//    // 重写计算薪资方法
//    double calculatePay() const override {
//        return baseSalary + (sales * commissionRate);  // 销售有基本工资+提成
//    }
//
//    void displayInfo() const override {
//        cout << "销售: " << name
//            << ", 基本工资: " << baseSalary
//            << ", 销售额: " << sales
//            << ", 总薪资: " << calculatePay() << endl;
//    }
//};
//
//int main() {
//    Employee emp("张三", 5000);
//    Manager mgr("李四", 8000, 3000);
//    SalesPerson sales("王五", 4000, 100000, 0.1);
//
//    // 通过基类指针调用，体现多态
//    Employee* employees[] = { &emp, &mgr, &sales };
//
//    cout << "员工薪资信息：" << endl;
//    for (int i = 0; i < 3; i++) {
//        employees[i]->displayInfo();
//        // 同一接口，不同计算方式
//    }
//
//    return 0;
//}