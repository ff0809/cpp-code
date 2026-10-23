#include "game.h"

int main()
{
    Game game; // 创建游戏对象
    game.init(); // 初始化游戏
    game.run(); // 运行游戏主循环
    game.close(); // 关闭图形窗口
    return 0;
}