#pragma once
#pragma once
#include "anti_aliasing.h"

#define PI 3.1415926
//画图窗口大小
#define WINDOW_X 1600
#define WINDOW_Y 600
//圆心坐标
#define CENTER_X WINDOW_X / 2
#define CENTER_Y WINDOW_Y / 2
//两个圆的半径
#define RADIUS_1 int(min(WINDOW_X,WINDOW_Y)/2*0.9)
#define RADIUS_2 int(min(WINDOW_X,WINDOW_Y)/2*0.55)
// 抗锯齿
#define SDF_WIDTH_CIRCLE 30//抗锯齿处理像素宽度 circle
#define SDF_WIDTH_LINE 10//抗锯齿处理像素宽度 line
//各种color
#define MY_PURPLE RGB(150,142,185)
#define MY_WHITE RGB(248, 241, 248)
#define MY_LIGHT_RED RGB(255, 186, 201)
#define MY_PINK RGB(249,218,228)
#define MY_WHITE_2 RGB(249, 236, 243)
#define MY_BLUE RGB(239,239,246)

class ClockHand {
private:
    double hour_hand_angle;
    double minite_hand_angle;
    double second_hand_angle;
    int centerX;
    int centerY;
    int radius;
    int hour;
    int minite;
    int second;
    LineDrawer* lineDrawer;
    CircleDrawer* circleDrawer;

    void draw_hms(double len, double angle);

public:
    ClockHand(int h, int m, int s, LineDrawer* line, CircleDrawer* circle, int x, int y, int r);
    void draw();
};


class ClockFace {
private:
    LineDrawer* lineDrawer;
    CircleDrawer* circleDrawer;

public:
    ClockFace(LineDrawer* line, CircleDrawer* circle);
    void draw(int centerX, int centerY, int radius);
};

class ClockRender {
private:
    LineDrawer* lineDrawer;
    CircleDrawer* circleDrawer;
    IMAGE* buffer;
    IMAGE* flashBuffer;
    int c_x;
    int c_y;
    int r;
public:
    ClockRender(IMAGE* buffer, LineDrawer* line, CircleDrawer* circle, int c_x, int c_y, int r);
    void drawClockFace();
    void drawClockHand();
    void saveFlash();
    void flash();
};
