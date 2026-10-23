#pragma once
#include <graphics.h>

// 抽象基类：抗锯齿线条
class LineDrawer {
protected:
    IMAGE* buffer = NULL;
public:
    void setBuffer(IMAGE* buffer);
    virtual void draw(int x1, int y1, int x2, int y2, COLORREF color, int thickness) = 0;
    virtual ~LineDrawer() = default;
};

// 抽象基类：抗锯齿圆形
class CircleDrawer {
protected:
    IMAGE* buffer = NULL;
public:
    void setBuffer(IMAGE* buffer);
    virtual void draw(int center_x, int center_y, COLORREF color, int radius) = 0;
    virtual ~CircleDrawer() = default;
};

// 无抗锯齿实现
class NoAA_Line : public LineDrawer {
public:
    //NoAA_Line(IMAGE* buffer) : AntiAliasedLine(buffer) {}
    void draw(int x1, int y1, int x2, int y2, COLORREF color, int thickness) override;
};

class NoAA_Circle : public CircleDrawer {
public:
    //NoAA_Circle(IMAGE* buffer) : AntiAliasedCircle(buffer) {}
    void draw(int center_x, int center_y, COLORREF color, int radius) override;
};

// SDF 抗锯齿实现
class SDF_Line : public LineDrawer {
public:
    //SDF_Line(IMAGE* buffer) : AntiAliasedLine(buffer) {}
    void draw(int x1, int y1, int x2, int y2, COLORREF color, int thickness) override;
};

class SDF_Circle : public CircleDrawer {
public:
    //SDF_Circle(IMAGE* buffer) : AntiAliasedCircle(buffer) {}
    void draw(int center_x, int center_y, COLORREF color, int radius) override;
};

// SSAA 抗锯齿实现
class SSAA_Line : public LineDrawer {
public:
    //SSAA_Line(IMAGE* buffer) : AntiAliasedLine(buffer) {}
    void draw(int x1, int y1, int x2, int y2, COLORREF color, int thickness) override;
};

class SSAA_Circle : public CircleDrawer {
public:
    //SSAA_Circle(IMAGE* buffer) : AntiAliasedCircle(buffer) {}
    void draw(int center_x, int center_y, COLORREF color, int radius) override;
};
