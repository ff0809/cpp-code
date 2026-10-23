//#include <iostream>
//#include <vector>
//#include <string>
//#include <opencv2/opencv.hpp>
//#include <Windows.h>
//using namespace std;
//using namespace cv;
//
//// 清屏
//void Clear() {
//    // Windows 下可以改成 system("cls");
//    cout << "\x1B[2J\x1B[H";
//}
//
//// 暂停等待
//void waitForEnter() {
//    cout << "\n按任意键返回...\n";
//    system("pause");
//}
//
//class ColorDetector {
//public:
//    ColorDetector() {
//        cap.open(0);
//        if (!cap.isOpened()) {
//            cerr << "无法打开摄像头" << endl;
//            exit(-1);
//        }
//    }
//
//    // 添加颜色菜单
//    void addmenu() {
//        Clear();
//        cout << "===== 颜色列表 =====\n";
//        for (int i = 0; i < availableColors.size(); i++)
//            cout << i + 1 << ". " << availableColors[i] << "\n";
//        cout << availableColors.size() + 1 << ". 添加全部颜色\n";
//        cout << "====================\n";
//
//        int choice;
//        cin >> choice;
//        if (choice == availableColors.size() + 1) {
//            for (auto& name : availableColors)
//                addSingleColor(name);
//        }
//        else if (choice >= 1 && choice <= availableColors.size()) {
//            addSingleColor(availableColors[choice - 1]);
//        }
//        else {
//            cout << "无效选项！\n";
//        }
//        waitForEnter();
//    }
//
//    // 删除颜色菜单
//    void delmenu() {
//        Clear();
//        if (colors.empty()) {
//            cout << "当前没有选定任何颜色。\n";
//            waitForEnter();
//            return;
//        }
//        cout << "===== 删除颜色 =====\n";
//        for (int i = 0; i < colors.size(); i++)
//            cout << i + 1 << ". " << colors[i].name << "\n";
//        cout << colors.size() + 1 << ". 删除全部颜色\n";
//        cout << "====================\n";
//
//        int choice;
//        cin >> choice;
//        if (choice == colors.size() + 1) {
//            colors.clear();
//            cout << "已删除全部颜色。\n";
//        }
//        else if (choice >= 1 && choice <= colors.size()) {
//            cout << "已删除颜色: " << colors[choice - 1].name << "\n";
//            colors.erase(colors.begin() + (choice - 1));
//        }
//        else {
//            cout << "无效选项！\n";
//        }
//        waitForEnter();
//    }
//
//    // 列出已选颜色
//    void listColors() {
//        Clear();
//        if (colors.empty()) {
//            cout << "当前没有选定任何颜色。\n";
//        }
//        else {
//            cout << "== 已选颜色 ==\n";
//            for (auto& c : colors) cout << "- " << c.name << "\n";
//            cout << "==============\n";
//        }
//        waitForEnter();
//    }
//
//    // 摄像头检测
//    void runCamera() {
//        cout << "开始摄像头检测 (按 'q' 退出)...\n";
//        while (true) {
//            Mat frame;
//            if (!cap.read(frame)) break;
//            detectOnImage(frame);
//            imshow("Camera Detection", frame);
//            if (waitKey(1) == 'q') break;
//        }
//        destroyWindow("Camera Detection");
//    }
//
//    // 静态图片检测
//    void runImage(const string& path) {
//        Mat img = imread(path);
//        if (img.empty()) {
//            cerr << "无法读取图片！\n";
//            Sleep(1000);
//            return;
//        }
//        Mat display = img.clone();
//        detectOnImage(display);
//        imshow("Image Detection", display);
//        cout << "按任意键关闭窗口...\n";
//        waitKey(0);
//        destroyWindow("Image Detection");
//    }
//
//private:
//    struct Color {
//        string name;
//        Scalar lower, upper, bgr;
//    };
//
//    VideoCapture cap;
//    vector<Color> colors;
//    vector<string> availableColors = {
//        "red","green","blue","yellow","orange","purple","black","white","gray"
//    };
//
//    // 添加单个颜色（去重）
//    void addSingleColor(const string& name) {
//        for (auto& c : colors)
//            if (c.name == name) {
//                cout << "颜色 " << name << " 已存在！\n";
//                return;
//            }
//        Color c;
//        c.name = name;
//        getLimits(name, c.lower, c.upper);
//        c.bgr = getBGR(name);
//        colors.push_back(c);
//        cout << "已添加颜色: " << name << "\n";
//    }
//
//    // 颜色检测核心逻辑
//    void detectOnImage(Mat& frame) {
//        Mat hsv;
//        cvtColor(frame, hsv, COLOR_BGR2HSV);
//        for (auto& c : colors) {
//            Mat mask;
//            inRange(hsv, c.lower, c.upper, mask);
//            morphologyEx(mask, mask, MORPH_CLOSE,
//                getStructuringElement(MORPH_RECT, Size(5, 5)));
//            vector<vector<Point>> contours;
//            findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//            for (auto& cnt : contours) {
//                Rect r = boundingRect(cnt);
//                if (r.area() > 1000) {
//                    rectangle(frame, r, c.bgr, 2);
//                    putText(frame, c.name, r.tl(),
//                        FONT_ITALIC, 1, c.bgr, 1);
//                }
//            }
//        }
//    }
//
//    // 预设 HSV 范围
//    void getLimits(const string& name, Scalar& lo, Scalar& hi) {
//        if (name == "red") { lo = { 158,106,108 }; hi = { 179,255,255 }; }
//        else if (name == "green") { lo = { 28,52,66 };    hi = { 65,255,255 }; }
//        else if (name == "blue") { lo = { 80,47,59 };    hi = { 125,255,255 }; }
//        else if (name == "yellow") { lo = { 24,88,135 };  hi = { 34,255,255 }; }
//        else if (name == "orange") { lo = { 6,118,97 };   hi = { 19,255,253 }; }
//        else if (name == "purple") { lo = { 124,66,71 };  hi = { 164,255,255 }; }
//        else if (name == "black") { lo = { 0,0,0 };       hi = { 179,255,64 }; }
//        else if (name == "white") { lo = { 0,0,158 };     hi = { 179,24,255 }; }
//        else if (name == "gray") { lo = { 0,0,45 };      hi = { 179,31,219 }; }
//        else { lo = { 0,0,0 };       hi = { 0,0,0 }; }
//    }
//
//    // BGR 框线颜色
//    Scalar getBGR(const string& name) {
//        if (name == "red")    return { 0,0,255 };
//        if (name == "green")  return { 0,255,0 };
//        if (name == "blue")   return { 255,0,0 };
//        if (name == "yellow") return { 0,255,255 };
//        if (name == "orange") return { 0,165,255 };
//        if (name == "purple") return { 255,0,255 };
//        if (name == "black")  return { 0,0,0 };
//        if (name == "white")  return { 255,255,255 };
//        if (name == "gray")   return { 128,128,128 };
//        return { 0,0,0 };
//    }
//};
//
//void showMenu() {
//    Clear();
//    cout << "======= 菜单 =======\n";
//    cout << "1. 添加颜色\n";
//    cout << "2. 删除颜色\n";
//    cout << "3. 显示颜色列表\n";
//    cout << "4. 开始摄像头检测\n";
//    cout << "5. 图片检测\n";
//    cout << "6. 退出程序\n";
//    cout << "====================\n";
//}
//
//int main() {
//    ColorDetector detector;
//    while (true) {
//        showMenu();
//        int choice;
//        cin >> choice;
//        switch (choice) {
//        case 1: detector.addmenu();    break;
//        case 2: detector.delmenu();    break;
//        case 3: detector.listColors(); break;
//        case 4: detector.runCamera();  break;
//        case 5: {
//            cout << "请输入图片路径：";
//            string path; cin >> path;
//            detector.runImage(path);
//            break;
//        }
//        case 6:
//            cout << "退出程序。\n";
//            return 0;
//        default:
//            cout << "无效选项，请重新输入。\n";
//            Sleep(500);
//        }
//    }
//    return 0;
//}
