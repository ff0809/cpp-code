//#include <iostream>
//#include <cmath>
//using namespace std;
//
//class Shape {
//public:
//    // 纯虚函数 - 抽象基类
//    virtual double area() const = 0;
//    virtual double perimeter() const = 0;
//    virtual void printInfo() const {
//        cout << "图形信息：" << endl;
//    }
//    virtual ~Shape() = default;
//};
//
//class Circle : public Shape {
//private:
//    double radius;
//public:
//    Circle(double r) : radius(r) {}
//
//    double area() const override {
//        return 3.14159 * radius * radius;
//    }
//
//    double perimeter() const override {
//        return 2 * 3.14159 * radius;
//    }
//
//    void printInfo() const override {
//        cout << "圆形 - 半径: " << radius
//            << ", 面积: " << area()
//            << ", 周长: " << perimeter() << endl;
//    }
//};
//
//class Rectangle : public Shape {
//private:
//    double width, height;
//public:
//    Rectangle(double w, double h) : width(w), height(h) {}
//
//    double area() const override {
//        return width * height;
//    }
//
//    double perimeter() const override {
//        return 2 * (width + height);
//    }
//
//    void printInfo() const override {
//        cout << "矩形 - 宽: " << width << ", 高: " << height
//            << ", 面积: " << area()
//            << ", 周长: " << perimeter() << endl;
//    }
//};
//
//// 处理各种图形的通用函数
//void processShapes(const Shape* shapes[], int count) {
//    double totalArea = 0;
//    double totalPerimeter = 0;
//
//    for (int i = 0; i < count; i++) {
//        shapes[i]->printInfo();  // 多态调用
//        totalArea += shapes[i]->area();
//        totalPerimeter += shapes[i]->perimeter();
//    }
//
//    cout << "\n总面积: " << totalArea << endl;
//    cout << "总周长: " << totalPerimeter << endl;
//}
//
//int main() {
//    Circle circle(5.0);
//    Rectangle rectangle(4.0, 6.0);
//
//    const Shape* shapes[] = { &circle, &rectangle };
//
//    processShapes(shapes, 2);
//
//    return 0;
//}