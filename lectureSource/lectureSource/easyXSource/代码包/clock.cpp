#define _CRT_SECURE_NO_WARNINGS
#include "clock.h"
#include <graphics.h>
#include <math.h>
#include <time.h> 

// 构造函数：接受抗锯齿对象
ClockHand::ClockHand(int h, int m, int s, LineDrawer* line, CircleDrawer* circle, int x, int y, int r)
    : hour(h), minite(m), second(s), lineDrawer(line), circleDrawer(circle), centerX(x), centerY(y), radius(r) {
    hour_hand_angle = -PI / 2 + h * 2 * PI / 12 + m * 2 * PI / 12 / 60 + s * 2 * PI / 12 / 60 / 60;
    minite_hand_angle = -PI / 2 + m * 2 * PI / 60 + s * 2 * PI / 60 / 60;
    second_hand_angle = -PI / 2 + s * 2 * PI / 60;
}

// 画指针
void ClockHand::draw_hms(double len, double angle) {
    int x1 = int(centerX + len * 0.85 * cos(angle));
    int y1 = int(centerY + len * 0.85 * sin(angle));
    int x2 = int(centerX - len * 0.15 * cos(angle));
    int y2 = int(centerY - len * 0.15 * sin(angle));

    lineDrawer->draw(x1, y1, x2, y2, MY_PINK, 5);
    circleDrawer->draw(x2, y2, MY_PINK, 5);
    circleDrawer->draw(centerX, centerY, MY_LIGHT_RED, 15);
    circleDrawer->draw(centerX, centerY, MY_WHITE_2, 5);
    circleDrawer->draw(x1, y1, MY_LIGHT_RED, 10);
    circleDrawer->draw(x1, y1, MY_WHITE_2, 4);
}

void ClockHand::draw() {
    draw_hms(radius * 1.00, second_hand_angle);
    draw_hms(radius * 0.75, minite_hand_angle);
    draw_hms(radius * 0.40, hour_hand_angle);
}
// 构造函数
ClockFace::ClockFace(LineDrawer* line, CircleDrawer* circle)
    :lineDrawer(line), circleDrawer(circle) {
}

/********************************
函数功能：文字输出抗锯齿以及设计格式
形参：int x：文字输出横坐标
      int y：文字输出纵坐标
      TCHAR s[]：字符串
      COLORREF color：颜色
      int Height：文字高度，宽度自适应
返回值：无
********************************/
void text(int x, int y, TCHAR s[], COLORREF color, int Height, bool aa = true)
{
    // 设置输出效果为抗锯齿
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = Height;						// 设置字体高度
    setbkmode(TRANSPARENT);//背景透明字体
    settextcolor(color);
    _tcscpy_s(f.lfFaceName, _T("黑体"));	// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
    if (aa) {
        f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    }
    else {
        f.lfQuality = NONANTIALIASED_QUALITY;		// 设置输出效果为非抗锯齿  
    }
    settextstyle(&f);// 设置字体样式
    outtextxy(x, y, s);
}

// 画表盘
void ClockFace::draw(int centerX, int centerY, int radius) {

    int radius1 = radius;
    int radius2 = int(radius1 * 0.6);
    // 画圆环
    //circleDrawer->draw(centerX, centerY, MY_PURPLE, radius1, 60);
    //circleDrawer->draw(centerX, centerY, MY_BLUE, radius2, 150);
    circleDrawer->draw(centerX, centerY, MY_PURPLE, radius1);
    circleDrawer->draw(centerX, centerY, MY_BLUE, radius2);

    // 画刻度线和数字
    for (int i = 1; i <= 60; i++) {
        double sita = 2 * PI / 60 * i - PI / 2;
        int x1 = int(centerX + radius1 * 0.95 * cos(sita));  // 线的起点
        int y1 = int(centerY + radius1 * 0.95 * sin(sita));
        int x2;  // 线的终点
        int y2;
        int x3;  // 外圈数字位置
        int y3;
        int x4;  // 内圈数字位置
        int y4;

        if (i % 5) {  // **短刻度**
            x2 = int(centerX + radius1 * 0.9 * cos(sita));
            y2 = int(centerY + radius1 * 0.9 * sin(sita));
        }
        else {  // **长刻度 + 数字**
            x2 = int(centerX + radius1 * 0.85 * cos(sita));
            y2 = int(centerY + radius1 * 0.85 * sin(sita));
            x3 = int(centerX + radius1 * 0.75 * cos(sita) - 13);
            y3 = int(centerY + radius1 * 0.75 * sin(sita) - 13);
            x4 = int(centerX + radius2 * 0.75 * cos(sita) - 13);
            y4 = int(centerY + radius2 * 0.75 * sin(sita) - 17);

            // **绘制外圈数字**
            TCHAR s[5];
            _stprintf(s, _T("%d"), i);
            text(x3, y3, s, WHITE, 35);

            // **绘制内圈数字**
            _stprintf(s, _T("%d"), i / 5);
            text(x4, y4, s, MY_PURPLE, 40);
        }

        // **绘制刻度线**
        lineDrawer->draw(x1, y1, x2, y2, WHITE, (i % 5 == 0) ? 4 : 2);
    }
}
ClockRender::ClockRender(IMAGE* buffer, LineDrawer* line, CircleDrawer* circle, int c_x, int c_y, int r) :
    buffer(buffer), lineDrawer(line), circleDrawer(circle), c_x(c_x), c_y(c_y), r(r)
{
    flashBuffer = new IMAGE(WINDOW_X, WINDOW_Y);
}

void ClockRender::drawClockFace()
{
    // 画表盘
    lineDrawer->setBuffer(buffer);
    circleDrawer->setBuffer(buffer);
    ClockFace clockFace(lineDrawer, circleDrawer);
    clockFace.draw(c_x, c_y, r);
}

void ClockRender::drawClockHand()
{
    struct tm t;
    time_t now;
    time(&now);
    localtime_s(&t, &now);
    //if (cmp(t, t_copy)) continue;

    // 离屏渲染
    IMAGE* particle = new IMAGE(WINDOW_X, WINDOW_Y);
    SetWorkingImage(particle);
    lineDrawer->setBuffer(particle);
    circleDrawer->setBuffer(particle);
    putimage(0, 0, buffer);

    // 画指针
    ClockHand h(t.tm_hour, t.tm_min, t.tm_sec, lineDrawer, circleDrawer, c_x, c_y, r);
    h.draw();

    // 更新屏幕
    SetWorkingImage(buffer);
    putimage(0, 0, particle);
    SetWorkingImage(NULL);
    putimage(0, 0, particle);

    //delete particle;
}

void ClockRender::saveFlash()
{
    SetWorkingImage(flashBuffer);
    putimage(0, 0, buffer);
}

void ClockRender::flash()
{
    SetWorkingImage(buffer);
    putimage(0, 0, flashBuffer);
}

