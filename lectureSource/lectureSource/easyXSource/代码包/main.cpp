#include <iostream>  
#include <iomanip>     
#include <graphics.h>  
#include <math.h>  
#include <conio.h>  

#include <stdio.h>
#include "clock.h"
#include <windows.h>

using namespace std;

/********************************
函数功能：判断是否需要重新渲染
形参：struct tm t：现在的时间
      struct tm t_copy：上一次的时间
返回值：bool类型 1：不需要渲染
                 0：需要重新渲染
********************************/
bool cmp(struct tm t, struct tm t_copy)
{
    return t.tm_sec == t_copy.tm_sec;
}

int main() {
    // 初始化绘图窗口
    initgraph(WINDOW_X, WINDOW_Y);

    // 开启双缓冲绘图
    BeginBatchDraw();

    // 加载背景图
    IMAGE* background = new IMAGE(WINDOW_X, WINDOW_Y);
    loadimage(background, L"./bk.jpg", WINDOW_X, WINDOW_Y);

    // 创建时钟对象
    // 1.无抗锯齿效果时钟对象
    //无抗锯齿效果
    LineDrawer* lineDrawer_1 = new NoAA_Line();
    CircleDrawer* circleDrawer_1 = new NoAA_Circle();
    ClockRender* clockRender1 = new ClockRender(background, lineDrawer_1, circleDrawer_1, 400, 300, 270);
    // 2.有抗锯齿效果时钟对象
    // SDF
    /****************** RELEASE ******************/
    /*LineDrawer* lineDrawer_2 = new SDF_Line();
    CircleDrawer* circleDrawer_2 = new SDF_Circle()
    ClockRender* clockRender2 = new ClockRender(background, lineDrawer_2, circleDrawer_2, 1200, 300, 270);*/
    /****************** RELEASE END ******************/

    // 绘制时钟表盘
    clockRender1->drawClockFace();
    /****************** ANNOTATION ******************/
    clockRender1->saveFlash();
    /****************** ANNOTATION END ******************/

    /****************** RELEASE ******************/
    /*clockRender2->drawClockFace();
    clockRender2->saveFlash();*/
    /****************** RELEASE END ******************/

    struct tm t, t_copy;
    time_t now;
    time(&now);
    localtime_s(&t, &now);

    while (!_kbhit()) {
        t_copy = t;
        time(&now);
        localtime_s(&t, &now);
        if (cmp(t, t_copy))
            continue;

        // 先绘制背景，防止指针残影
        /****************** ANNOTATION ******************/
        clockRender1->flash();
        /****************** ANNOTATION END ******************/

        /****************** RELEASE ******************/
        //clockRender2->flash();
        /****************** RELEASE END ******************/

        // 绘制两个时钟
        clockRender1->drawClockHand();
        /****************** RELEASE ******************/
        //clockRender2->drawClockHand();
        /****************** RELEASE END ******************/

        // 刷新绘图缓冲区
        FlushBatchDraw();

        Sleep(50);  // 控制帧率
    }

    _getch();
    closegraph();

    // 释放动态分配的内存
    delete background;
    delete clockRender1;
    delete lineDrawer_1;
    delete circleDrawer_1;
    /****************** RELEASE ******************/
    /*delete clockRender2;
    delete lineDrawer_2;
    delete circleDrawer_2;*/
    /****************** RELEASE END ******************/

    return 0;
}