#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "PicReader.h"
#include "FastPrinter.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
#include <limits>
using namespace std;

template <typename T>
T clamp(T value, T minValue, T maxValue) {
    return std::max(minValue, std::min(value, maxValue));
}

const char asciiStrength[] = {
  '@', '8', 'M', 'B', 'W', 'O', '&', '%', 'H', '9'
};
const int ASCII_LEVELS = sizeof(asciiStrength) / sizeof(asciiStrength[0]);

void getExactConsoleSize(int& maxCols, int& maxRows) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        maxCols = 120;
        maxRows = 60;
        return;
    }

    maxCols = csbi.srWindow.Right - csbi.srWindow.Left - 5;
    maxRows = csbi.srWindow.Bottom - csbi.srWindow.Top - 3;

    maxCols = max(maxCols, 80);
    maxRows = max(maxRows, 40);
}

int calculateExactScale(int originalWidth, int originalHeight, int maxConsoleCols, int maxConsoleRows) {
    float scaleW = static_cast<float>(originalWidth * 2) / maxConsoleCols;
    float scaleH = static_cast<float>(originalHeight) / maxConsoleRows;
    float maxScale = max(scaleW, scaleH);
    int d = static_cast<int>(ceil(maxScale));
    d = max(d, 1);
    return d;
}

// RGB转灰度
unsigned char rgbToGrayOptimized(unsigned char r, unsigned char g, unsigned char b) {
    return static_cast<unsigned char>((r * 299 + g * 587 + b * 114 + 500) / 1000);
}

// 灰度转ASCII
char grayToAscii(unsigned char gray) {
    int asciiIndex = gray * (ASCII_LEVELS - 1) / 255;
    asciiIndex = clamp(asciiIndex, 0, ASCII_LEVELS - 1);
    return asciiStrength[asciiIndex];
}

// 灰度转ASCII（带边缘调整）
char grayToAsciiAdjusted(unsigned char gray, double edgeNorm, double edgeFactor = 0.6) {
    double grayNorm = static_cast<double>(gray) / 255.0;
    double lumIndex = grayNorm * (ASCII_LEVELS - 1);
    double edgeBias = edgeNorm * (ASCII_LEVELS - 1) * edgeFactor;
    int idx = static_cast<int>(std::round(lumIndex - edgeBias));
    idx = clamp(idx, 0, ASCII_LEVELS - 1);
    return asciiStrength[idx];
}

// 图像压缩
vector<unsigned char> compressImageWithArray(const Array& imgData,
    int originalWidth, int originalHeight,
    int outputWidth, int outputHeight) {

    vector<unsigned char> result(outputWidth * outputHeight * 3);
    float scaleX = static_cast<float>(originalWidth) / outputWidth;
    float scaleY = static_cast<float>(originalHeight) / outputHeight;

    for (int y = 0; y < outputHeight; y++) {
        for (int x = 0; x < outputWidth; x++) {
            int startX = static_cast<int>(x * scaleX);
            int startY = static_cast<int>(y * scaleY);
            int endX = static_cast<int>((x + 1) * scaleX);
            int endY = static_cast<int>((y + 1) * scaleY);
            endX = min(endX, originalWidth);
            endY = min(endY, originalHeight);

            long totalR = 0, totalG = 0, totalB = 0;
            int pixelCount = 0;

            for (int sy = startY; sy < endY; sy++) {
                for (int sx = startX; sx < endX; sx++) {
                    totalR += imgData.at(sx, sy, 0);
                    totalG += imgData.at(sx, sy, 1);
                    totalB += imgData.at(sx, sy, 2);
                    pixelCount++;
                }
            }

            int resultIdx = (y * outputWidth + x) * 3;
            if (pixelCount > 0) {
                result[resultIdx] = static_cast<unsigned char>(totalR / pixelCount);
                result[resultIdx + 1] = static_cast<unsigned char>(totalG / pixelCount);
                result[resultIdx + 2] = static_cast<unsigned char>(totalB / pixelCount);
            }
            else {
                result[resultIdx] = result[resultIdx + 1] = result[resultIdx + 2] = 0;
            }
        }
    }
    return result;
}

// 计算Sobel边缘检测（归一化）
vector<double> computeNormalizedSobel(const vector<unsigned char>& gray, int w, int h) {
    vector<double> grad(w * h, 0.0);
    auto at = [&](int x, int y)->int { return y * w + x; };
    double maxG = 1e-6;

    for (int y = 1; y < h - 1; ++y) {
        for (int x = 1; x < w - 1; ++x) {
            int gx = -(int)gray[at(x - 1, y - 1)] - 2 * (int)gray[at(x - 1, y)] - (int)gray[at(x - 1, y + 1)]
                + (int)gray[at(x + 1, y - 1)] + 2 * (int)gray[at(x + 1, y)] + (int)gray[at(x + 1, y + 1)];
            int gy = -(int)gray[at(x - 1, y - 1)] - 2 * (int)gray[at(x, y - 1)] - (int)gray[at(x + 1, y - 1)]
                + (int)gray[at(x - 1, y + 1)] + 2 * (int)gray[at(x, y + 1)] + (int)gray[at(x + 1, y + 1)];
            double g = std::sqrt(static_cast<double>(gx * gx + gy * gy));
            grad[at(x, y)] = g;
            if (g > maxG) maxG = g;
        }
    }

    // 归一化
    for (size_t i = 0; i < grad.size(); ++i) {
        grad[i] = grad[i] / maxG;
        if (grad[i] < 0.0) grad[i] = 0.0;
        if (grad[i] > 1.0) grad[i] = 1.0;
    }
    return grad;
}

// 从RGB生成增强的灰度图
vector<unsigned char> makeEnhancedGrayFromRGB(const vector<unsigned char>& rgb, int w, int h,
    double gamma = 1.05, double edgeStrength = 0.9) {
    vector<unsigned char> gray(w * h);

    for (int i = 0; i < w * h; ++i) {
        int idx = i * 3;
        unsigned char r = rgb[idx], g = rgb[idx + 1], b = rgb[idx + 2];
        double L = (r * 299 + g * 587 + b * 114 + 500) / 1000.0;
        double n = std::pow(clamp(L / 255.0, 0.0, 1.0), 1.0 / gamma);
        gray[i] = static_cast<unsigned char>(std::round(n * 255.0));
    }
    auto gradNorm = computeNormalizedSobel(gray, w, h);

    // 增强灰度图（增加边缘对比度）
    vector<unsigned char> outGray(w * h);
    for (int i = 0; i < w * h; ++i) {
        double boosted = static_cast<double>(gray[i]) + edgeStrength * 255.0 * gradNorm[i];
        if (boosted < 0.0) boosted = 0.0;
        if (boosted > 255.0) boosted = 255.0;
        outGray[i] = static_cast<unsigned char>(std::round(boosted));
    }
    return outGray;
}

// 主处理函数
void processImageToAscii(const char* imagePath) {
    PicReader reader;

    if (!reader.readPic(imagePath)) {
        cerr << "can't load the picture!" << endl;
        return;
    }

    Array imgData = reader.getData(false);

    int origWidth = imgData.get_width();
    int origHeight = imgData.get_height();

    int maxConsoleCols, maxConsoleRows;
    getExactConsoleSize(maxConsoleCols, maxConsoleRows);

    int d = calculateExactScale(origWidth, origHeight, maxConsoleCols, maxConsoleRows);

    int outputWidth = max(1, origWidth / d);
    int outputHeight = max(1, origHeight / d);

    if (outputWidth % 2 != 0) {
        outputWidth++;
    }

    int displayWidth = outputWidth * 2;
    int displayHeight = outputHeight;

    displayWidth = min(displayWidth, maxConsoleCols);
    displayHeight = min(displayHeight, maxConsoleRows);
    outputWidth = max(1, displayWidth / 2);

    // 压缩图像
    auto compressedData = compressImageWithArray(imgData, origWidth, origHeight, outputWidth, outputHeight);

    // 生成增强的灰度图
    auto enhancedGray = makeEnhancedGrayFromRGB(compressedData, outputWidth, outputHeight, 1.05, 0.9);

    // 计算边缘
    auto gradNorm = computeNormalizedSobel(enhancedGray, outputWidth, outputHeight);

    // 准备ASCII缓冲区
    vector<char> asciiBuffer(outputWidth * outputHeight);
    vector<BYTE> frontColor(outputWidth * outputHeight * 3);
    vector<BYTE> backColor(outputWidth * outputHeight * 3, 0);

    const double edgeFactor = 0.6;

    // 转换为ASCII字符
    for (int y = 0; y < outputHeight; y++) {
        for (int x = 0; x < outputWidth; x++) {
            int idx = (y * outputWidth + x);
            int colorIdx = idx * 3;
            unsigned char r = compressedData[colorIdx];
            unsigned char g = compressedData[colorIdx + 1];
            unsigned char b = compressedData[colorIdx + 2];
            unsigned char gray = enhancedGray[idx];
            double edge = gradNorm[idx];

            asciiBuffer[idx] = grayToAsciiAdjusted(gray, edge, edgeFactor);

            frontColor[colorIdx] = r;
            frontColor[colorIdx + 1] = g;
            frontColor[colorIdx + 2] = b;
        }
    }

    // 扩展ASCII字符（两个字符表示一个像素）
    vector<char> expandedAscii(displayWidth * displayHeight);
    vector<BYTE> expandedFrontColor(displayWidth * displayHeight * 3);
    vector<BYTE> expandedBackColor(displayWidth * displayHeight * 3, 0);

    std::fill(expandedAscii.begin(), expandedAscii.end(), ' ');
    std::fill(expandedFrontColor.begin(), expandedFrontColor.end(), 0);

    for (int y = 0; y < displayHeight; y++) {
        for (int x = 0; x < outputWidth; x++) {
            if (y < outputHeight && x < outputWidth) {
                char c = asciiBuffer[y * outputWidth + x];
                int srcColorIdx = (y * outputWidth + x) * 3;
                int dstIdx1 = y * displayWidth + x * 2;
                int dstIdx2 = y * displayWidth + x * 2 + 1;

                expandedAscii[dstIdx1] = c;
                expandedAscii[dstIdx2] = c;

                for (int k = 0; k < 3; k++) {
                    expandedFrontColor[dstIdx1 * 3 + k] = frontColor[srcColorIdx + k];
                    expandedFrontColor[dstIdx2 * 3 + k] = frontColor[srcColorIdx + k];
                }
            }
        }
    }

    // 创建FastPrinter并显示
    FastPrinter printer(displayWidth, displayHeight, 6);
    printer.cleanSrceen();
    printer.setData(expandedAscii.data(), expandedFrontColor.data(), expandedBackColor.data());
    printer.draw(true);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void showMenu() {
    system("cls");
    cout << "==========================================" << endl;
    cout << "         ASCII Picture" << endl;
    cout << "==========================================" << endl;
    cout << "1. test Picture" << endl;
    cout << "2. your path" << endl;
    cout << "3. exit" << endl;
    cout << "==========================================" << endl;
    cout << "choose: ";
}

int main() {
    SetConsoleOutputCP(65001);

    const string defaultPath = "D:\\C++code\\Z_4_Resources\\Z_4_Resources\\Z_4_Resources\\classic_picture\\lena.jpg";
    string imagePath;

    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        showMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            imagePath = defaultPath;
            cout << "test picture: " << imagePath << endl;
            break;

        case 2:
            cout << "your path: ";
            getline(cin, imagePath);
            if (imagePath.empty()) {
                cout << "Your path is empty! it will show the test picture." << endl;
                imagePath = defaultPath;
            }
            break;

        case 3:
            cout << "bye!" << endl;
            exitProgram = true;
            continue;

        default:
            cout << "invalid choice!" << endl;
            system("pause");
            continue;
        }

        try {
            processImageToAscii(imagePath.c_str());
        }
        catch (const exception& e) {
            cerr << "error: " << e.what() << endl;
            system("pause");
        }

        cout << "\ncontinue？(y/n): ";
        char continueChoice;
        cin >> continueChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (continueChoice != 'y' && continueChoice != 'Y') {
            exitProgram = true;
        }
    }

    return 0;
}