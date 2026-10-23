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

COLORREF mix_color(COLORREF bg, COLORREF color, double alpha)//背景色 前景色 alpha=0.5-d 返回RGB( , , )
{
    COLORREF result;
    result = RGB(GetRValue(bg) * (1 - alpha) + GetRValue(color) * alpha, GetGValue(bg) * (1 - alpha) + GetGValue(color) * alpha, GetBValue(bg) * (1 - alpha) + GetBValue(color) * alpha);
    return result;
}

// SDF 直线
void SDF_Line::draw(int x1, int y1, int x2, int y2, COLORREF color, int thickness)
{
    int sdf_degree = 2;
    SetWorkingImage(buffer);
    for (int x = min(x1, x2) - SDF_WIDTH_LINE; x < max(x1, x2) + SDF_WIDTH_LINE; x++) {
        for (int y = min(y1, y2) - SDF_WIDTH_LINE; y < max(y1, y2) + SDF_WIDTH_LINE; y++) {
            double d;
            bool b1 = ((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) >= 0;
            bool b2 = ((x - x2) * (x1 - x2) + (y - y2) * (y1 - y2)) >= 0;
            if (b1 && b2)
                d = fabs(((x2 - x1) * (y - y1) - (y2 - y1) * (x - x1)) / sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))) - thickness / 2;
            else if (!b1)
                d = sqrt(pow(x - x1, 2) + pow(y - y1, 2)) - thickness / 2;
            else
                d = sqrt(pow(x - x2, 2) + pow(y - y2, 2)) - thickness / 2;
            double alpha = 0.5 - d / sdf_degree;
            if (alpha >= 0 && alpha <= 1) {
                COLORREF bg = getpixel(x, y);
                COLORREF result = mix_color(bg, color, alpha);
                putpixel(x, y, result);
            }
        }
    }
    setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, thickness);
    setlinecolor(color);
    line(x1, y1, x2, y2);
}

// SDF圆
void SDF_Circle::draw(int center_x, int center_y, COLORREF color, int radius) 
{
    SetWorkingImage(buffer);
    for (int x = center_x - radius - SDF_WIDTH_CIRCLE; x <= center_x + radius + SDF_WIDTH_CIRCLE; x++)
    {
        for (int y = center_y - radius - SDF_WIDTH_CIRCLE; y <= center_y + radius + SDF_WIDTH_CIRCLE; y++)
        {
            // 计算点到圆边的距离
            int dx = x - center_x;
            int dy = y - center_y;
            double d = sqrt(dx * dx + dy * dy) - radius;

            // 只处理接近圆边的点
            if (d > 0.5)
                continue;

            if (d < -0.5)
            {
                putpixel(x, y, color);
            }
            else
            {
                double alpha = 0.5 - d;
                if (alpha >= 0 && alpha <= 1)
                {
                    COLORREF bg = getpixel(x, y);
                    COLORREF result = mix_color(bg, color, alpha);
                    putpixel(x, y, result);
                }
            }
        }
    }
}

void SSAA_Line::draw(int x1, int y1, int x2, int y2, COLORREF color, int thickness) 
{
    const int scale = 2;  // 超采样倍率
    int sx1 = x1 * scale, sy1 = y1 * scale;
    int sx2 = x2 * scale, sy2 = y2 * scale;

    // 计算超采样区域的范围
    int min_x = min(sx1, sx2) - thickness * scale;
    int max_x = max(sx1, sx2) + thickness * scale;
    int min_y = min(sy1, sy2) - thickness * scale;
    int max_y = max(sy1, sy2) + thickness * scale;
    int width = max_x - min_x, height = max_y - min_y;

    IMAGE superBuffer(width, height);
    SetWorkingImage(&superBuffer);

    // 复制原图背景到超采样缓冲区
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int orig_x = min_x / scale + x / scale;
            int orig_y = min_y / scale + y / scale;
            SetWorkingImage(buffer);
            COLORREF bgColor = getpixel(orig_x, orig_y);
            SetWorkingImage(&superBuffer);
            putpixel(x, y, bgColor);
        }
    }

    // 设置超采样线条绘制参数
    setlinecolor(color);
    setlinestyle(PS_SOLID, thickness * scale);

    // 在超采样缓冲区中绘制高分辨率的线
    line(sx1 - min_x, sy1 - min_y, sx2 - min_x, sy2 - min_y);

    // 进行 2×2 采样后绘制回原图
    for (int x = 0; x < width / scale; x++) {
        for (int y = 0; y < height / scale; y++) {
            int r = 0, g = 0, b = 0;
            SetWorkingImage(&superBuffer);
            // 计算 2x2 采样区域的平均颜色
            for (int i = 0; i < scale; i++) {
                for (int j = 0; j < scale; j++) {
                    int px = x * scale + i;
                    int py = y * scale + j;
                    COLORREF c = getpixel(px, py);
                    r += GetRValue(c);
                    g += GetGValue(c);
                    b += GetBValue(c);
                }
            }
            r /= (scale * scale);
            g /= (scale * scale);
            b /= (scale * scale);

            // 计算正确的目标位置
            SetWorkingImage(buffer);
            int target_x = (min_x / scale) + x;
            int target_y = (min_y / scale) + y;
            putpixel(target_x, target_y, RGB(r, g, b));
        }
    }
}

// SSAA 圆绘制（局部超采样）
void SSAA_Circle::draw(int center_x, int center_y, COLORREF color, int radius) 
{

    const int scale = 2;  // 超采样倍率
    int scaled_radius = radius * scale;
    int sx = center_x * scale;
    int sy = center_y * scale;

    // 计算超采样区域的范围
    int thickness = 2;
    int min_x = sx - scaled_radius - thickness * scale;
    int max_x = sx + scaled_radius + thickness * scale;
    int min_y = sy - scaled_radius - thickness * scale;
    int max_y = sy + scaled_radius + thickness * scale;
    int width = max_x - min_x, height = max_y - min_y;

    IMAGE superBuffer(width, height);
    SetWorkingImage(&superBuffer);

    // 复制原图背景到超采样缓冲区
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int orig_x = (min_x / scale) + (x / scale);
            int orig_y = (min_y / scale) + (y / scale);
            SetWorkingImage(buffer);
            COLORREF bgColor = getpixel(orig_x, orig_y);
            SetWorkingImage(&superBuffer);
            putpixel(x, y, bgColor);
        }
    }

    // 在超采样缓冲区中绘制高分辨率的圆形
    setfillcolor(color);
    solidcircle(sx - min_x, sy - min_y, scaled_radius);

    // 进行 2×2 采样后绘制回原图
    for (int x = 0; x < width / scale; x++) {
        for (int y = 0; y < height / scale; y++) {
            int r = 0, g = 0, b = 0;
            SetWorkingImage(&superBuffer);
            // 计算 2x2 采样区域的平均颜色
            for (int i = 0; i < scale; i++) {
                for (int j = 0; j < scale; j++) {
                    int px = x * scale + i;
                    int py = y * scale + j;
                    COLORREF c = getpixel(px, py);
                    r += GetRValue(c);
                    g += GetGValue(c);
                    b += GetBValue(c);
                }
            }
            r /= (scale * scale);
            g /= (scale * scale);
            b /= (scale * scale);

            // 计算正确的目标位置
            SetWorkingImage(buffer);
            int target_x = (min_x / scale) + x;
            int target_y = (min_y / scale) + y;
            putpixel(target_x, target_y, RGB(r, g, b));
        }
    }
}