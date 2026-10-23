#include "anti_aliasing.h"
#include "clock.h"
#include <graphics.h>
#include <math.h>

void LineDrawer::setBuffer(IMAGE* buffer)
{
    this->buffer = buffer;
}

void CircleDrawer::setBuffer(IMAGE* buffer)
{
    this->buffer = buffer;
}

// 无抗锯齿直线
void NoAA_Line::draw(int x1, int y1, int x2, int y2, COLORREF color, int thickness)
{
    SetWorkingImage(buffer);
    setlinestyle(PS_SOLID, thickness);
    setlinecolor(color);
    line(x1, y1, x2, y2);
}

// 无抗锯齿圆
void NoAA_Circle::draw(int center_x, int center_y, COLORREF color, int radius)
{
    SetWorkingImage(buffer);
    setfillcolor(color);
    solidcircle(center_x, center_y, radius);
}

// SDF 直线
class SDF_Line {
public:
    void draw(int x1, int y1, int x2, int y2, COLORREF color, int thickness);
};

void SDF_Line::draw(int x1, int y1, int x2, int y2, COLORREF color, int thickness) {
    for (int y = 0; y < BUFFER_HEIGHT; ++y) {
        for (int x = 0; x < BUFFER_WIDTH; ++x) {
            // 计算点 (x, y) 到直线的有符号距离
            double dx = x2 - x1;
            double dy = y2 - y1;
            double length = std::sqrt(dx * dx + dy * dy);
            double t = ((x - x1) * dx + (y - y1) * dy) / (length * length);
            t = std::max(0.0, std::min(1.0, t));
            double closestX = x1 + t * dx;
            double closestY = y1 + t * dy;
            double distance = std::sqrt((x - closestX) * (x - closestX) + (y - closestY) * (y - closestY));

            // 如果距离小于等于厚度的一半，则绘制该像素
            if (distance <= thickness / 2.0) {
                putpixel(x, y, color);
            }
        }
    }
}

// SDF 圆
void SDF_Circle::draw(int center_x, int center_y, COLORREF color, int radius)
{
    SetWorkingImage(buffer);
    int radiusSquared = radius * radius; // 预计算半径的平方
    for (int y = center_y - radius; y <= center_y + radius; ++y) {
        for (int x = center_x - radius; x <= center_x + radius; ++x) {
            if (x >= 0 && x < BUFFER_WIDTH && y >= 0 && y < BUFFER_HEIGHT) {
                int dx = x - center_x;
                int dy = y - center_y;
                if (dx * dx + dy * dy <= radiusSquared) { // 使用平方避免开方运算
                    putpixel(x, y, color);
                }
            }
        }
    }
}

// SSAA 直线
void SSAA_Line::draw(int x1, int y1, int x2, int y2, COLORREF color, int thickness)
{
    const int SSAA_FACTOR = 4; // 超采样因子
    int superWidth = BUFFER_WIDTH * SSAA_FACTOR;
    int superHeight = BUFFER_HEIGHT * SSAA_FACTOR;

    // 在超采样缓冲区绘制直线
    for (int y = 0; y < superHeight; ++y) {
        for (int x = 0; x < superWidth; ++x) {
            double dx = (x2 - x1) * SSAA_FACTOR;
            double dy = (y2 - y1) * SSAA_FACTOR;
            double length = std::sqrt(dx * dx + dy * dy);
            double t = ((x - x1 * SSAA_FACTOR) * dx + (y - y1 * SSAA_FACTOR) * dy) / (length * length);
            t = std::max(0.0, std::min(1.0, t));
            double closestX = x1 * SSAA_FACTOR + t * dx;
            double closestY = y1 * SSAA_FACTOR + t * dy;
            double distance = std::sqrt((x - closestX) * (x - closestX) + (y - closestY) * (y - closestY));

            if (distance <= (thickness * SSAA_FACTOR) / 2.0) {
                int pixelX = x / SSAA_FACTOR;
                int pixelY = y / SSAA_FACTOR;
                if (pixelX >= 0 && pixelX < BUFFER_WIDTH && pixelY >= 0 && pixelY < BUFFER_HEIGHT) {
                    putpixel(pixelX, pixelY, color);
                }
            }
        }
    }
}

// SSAA 圆
void SSAA_Circle::draw(int center_x, int center_y, COLORREF color, int radius)
{
    const int SSAA_FACTOR = 4; // 超采样因子
    int superRadius = radius * SSAA_FACTOR;
    int superCenterX = center_x * SSAA_FACTOR;
    int superCenterY = center_y * SSAA_FACTOR;

    // 在超采样缓冲区绘制圆
    for (int y = superCenterY - superRadius; y <= superCenterY + superRadius; ++y) {
        for (int x = superCenterX - superRadius; x <= superCenterX + superRadius; ++x) {
            double distance = std::sqrt((x - superCenterX) * (x - superCenterX) +
                (y - superCenterY) * (y - superCenterY));
            if (distance <= superRadius) {
                int pixelX = x / SSAA_FACTOR;
                int pixelY = y / SSAA_FACTOR;
                if (pixelX >= 0 && pixelX < BUFFER_WIDTH && pixelY >= 0 && pixelY < BUFFER_HEIGHT) {
                    putpixel(pixelX, pixelY, color);
                }
            }
        }
    }
}
