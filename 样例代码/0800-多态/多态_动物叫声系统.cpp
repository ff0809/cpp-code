//#include <iostream>
//#include <string>
//using namespace std;
//
//// 基类
//class Animal {
//public:
//    // 虚函数 - 允许在派生类中被重写
//    virtual void makeSound() const {
//        cout << "动物发出声音" << endl;
//    }
//
//    virtual ~Animal() = default;  // 虚析构函数
//};
//
//// 派生类
//class Dog : public Animal {
//public:
//    // 重写基类的虚函数
//    void makeSound() const override {
//        cout << "汪汪汪！" << endl;
//    }
//};
//
//class Cat : public Animal {
//public:
//    void makeSound() const override {
//        cout << "喵喵喵！" << endl;
//    }
//};
//
//class Cow : public Animal {
//public:
//    void makeSound() const override {
//        cout << "哞哞哞！" << endl;
//    }
//};
//
//// 测试函数
//void animalConcert(Animal* animals[], int count) {
//    for (int i = 0; i < count; i++) {
//        animals[i]->makeSound();  // 同一调用，不同行为
//    }
//}
//
//int main() {
//    Dog dog;
//    Cat cat;
//    Cow cow;
//
//    Animal* animals[] = { &dog, &cat, &cow };
//
//    cout << "直接调用：" << endl;
//    dog.makeSound();  // 输出：汪汪汪！
//    cat.makeSound();  // 输出：喵喵喵！
//    cow.makeSound();  // 输出：哞哞哞！
//
//    cout << "\n通过基类指针调用（多态）：" << endl;
//    animalConcert(animals, 3);
//    // 输出：
//    // 汪汪汪！
//    // 喵喵喵！
//    // 哞哞哞！
//
//    return 0;
//}