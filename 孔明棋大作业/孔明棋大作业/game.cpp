#include "game.h"

// 初始化游戏
void Game::init()
{
    initgraph(WIDTH, HEIGHT);
    setbkcolor(WHITE);
    loadimage(&backgroundImg, _T("jidi.jpg")); // 加载背景图片
}

// 运行游戏主循环
void Game::run()
{
    BeginBatchDraw();//设置双缓冲绘图模式，减少闪烁

    while (true)
    {
        cleardevice();
        drawBackground();//在游戏开始前绘制背景

        switch (currentState)
        {
        case MENU:
            showMainMenu();
            break;
        case MODE_SELECTION:
            showModeSelection();
            break;
        case PLAYING:
            playGame();
            break;
        case SHOWING_RULES:
            showRules();
            break;
        case GAME_OVER:
            showGameOver();
            break;
        }

        FlushBatchDraw();// 刷新屏幕
        handleMouseInput();
        Sleep(1);// 减少CPU占用
    }

    EndBatchDraw();// 结束双缓冲
}

// 处理鼠标输入
void Game::handleMouseInput()
{
    if (MouseHit())
    {
        MOUSEMSG msg = GetMouseMsg();// 获取鼠标消息

        if (msg.uMsg == WM_MOUSEMOVE)// 鼠标移动事件
        {
            hoveredOption = NONE;

            if (currentState == MENU)
            {
                if (PtInRect(&startButton, msg.x, msg.y)) hoveredOption = CLASSIC_MODE;//PtInRect函数检查鼠标位置是否在矩形内
                else if (PtInRect(&rulesButton, msg.x, msg.y)) hoveredOption = GAME_RULES;
                else if (PtInRect(&exitButton, msg.x, msg.y)) hoveredOption = EXIT_GAME;
            }
            else if (currentState == MODE_SELECTION)
            {
                if (PtInRect(&classicButton, msg.x, msg.y)) hoveredOption = CLASSIC_MODE;
                else if (PtInRect(&challengeButton, msg.x, msg.y)) hoveredOption = CHALLENGE_MODE;
                else if (PtInRect(&backButton, msg.x, msg.y)) hoveredOption = EXIT_GAME;
            }
        }

        if (msg.uMsg == WM_LBUTTONDOWN) // 鼠标左键按下事件
        {
            switch (currentState)
            {
            case MENU:
                if (PtInRect(&startButton, msg.x, msg.y))
                {
                    currentState = MODE_SELECTION;
                }
                else if (PtInRect(&rulesButton, msg.x, msg.y))
                {
                    currentState = SHOWING_RULES;
                }
                else if (PtInRect(&exitButton, msg.x, msg.y))
                {
                    closegraph();
                    exit(0);
                }
                break;

            case MODE_SELECTION:
                if (PtInRect(&classicButton, msg.x, msg.y))
                {
                    board.reset(CLASSIC);
                    currentState = PLAYING;
                }
                else if (PtInRect(&challengeButton, msg.x, msg.y))
                {
                    showChallengeSelection();
                }
                else if (PtInRect(&backButton, msg.x, msg.y))
                {
                    currentState = MENU;
                }
                break;

            case PLAYING:
                if (PtInRect(&restartButtonInGame, msg.x, msg.y))
                {
                    board.reset(board.getCurrentMode());
                }
                else if (PtInRect(&undoButtonInGame, msg.x, msg.y))
                {
                    board.undoMove();
                }
                else if (PtInRect(&hintButtonInGame, msg.x, msg.y))
                {
                    board.toggleHint();
                }
                else if (PtInRect(&backButtonInGame, msg.x, msg.y))
                {
                    currentState = MENU;
                }
                else
                {
                    board.selectOrMove(msg.x, msg.y);

                    if (board.isWin() || board.isLose())
                    {
                        currentState = GAME_OVER;
                    }
                }
                break;

            case SHOWING_RULES:
                currentState = MENU;
                break;

            case GAME_OVER:
                if (PtInRect(&restartButton, msg.x, msg.y))
                {
                    board.reset(board.getCurrentMode());
                    currentState = PLAYING;
                }
                else if (PtInRect(&menuButton, msg.x, msg.y))
                {
                    currentState = MENU;
                }
                break;
            }
        }
    }
}

// 显示残局选择界面
void Game::showChallengeSelection()
{
    cleardevice();
    drawBackground();//在选择残局时也绘制导入图片背景

    // 绘制标题
    settextstyle(36, 0, _T("宋体"), 0, 0, FW_BOLD, false, false, false);
    settextcolor(RGB(70, 130, 180));
    outtextxy(WIDTH / 2 - 100, 150, _T("选择残局"));

    // 绘制残局选项
    settextstyle(28, 0, _T("宋体"));

    // 残局1按钮
    setfillcolor(RGB(180, 230, 100));
    fillrectangle(challenge1Button.left, challenge1Button.top, challenge1Button.right, challenge1Button.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(challenge1Button.left + 30, challenge1Button.top + 20, _T("残局1"));

    // 残局2按钮
    setfillcolor(RGB(100, 180, 255));
    fillrectangle(challenge2Button.left, challenge2Button.top, challenge2Button.right, challenge2Button.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(challenge2Button.left + 30, challenge2Button.top + 20, _T("残局2"));

    // 残局3按钮
    setfillcolor(RGB(255, 200, 100));
    fillrectangle(challenge3Button.left, challenge3Button.top, challenge3Button.right, challenge3Button.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(challenge3Button.left + 30, challenge3Button.top + 20, _T("残局3"));

    // 残局4按钮
    setfillcolor(RGB(255, 150, 200));
    fillrectangle(challenge4Button.left, challenge4Button.top, challenge4Button.right, challenge4Button.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(challenge4Button.left + 30, challenge4Button.top + 20, _T("残局4"));

    // 返回按钮
    setfillcolor(RGB(200, 200, 200));
    fillrectangle(backToModeButton.left, backToModeButton.top, backToModeButton.right, backToModeButton.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(backToModeButton.left + 30, backToModeButton.top + 20, _T("返回"));

    FlushBatchDraw();// 刷新屏幕

    // 处理残局选择
    while (true)
    {
        if (MouseHit())
        {
            MOUSEMSG msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                if (PtInRect(&challenge1Button, msg.x, msg.y))
                {
                    board.reset(CHALLENGE_1);
                    currentState = PLAYING;
                    return;
                }
                else if (PtInRect(&challenge2Button, msg.x, msg.y))
                {
                    board.reset(CHALLENGE_2);
                    currentState = PLAYING;
                    return;
                }
                else if (PtInRect(&challenge3Button, msg.x, msg.y))
                {
                    board.reset(CHALLENGE_3);
                    currentState = PLAYING;
                    return;
                }
                else if (PtInRect(&challenge4Button, msg.x, msg.y))
                {
                    board.reset(CHALLENGE_4);
                    currentState = PLAYING;
                    return;
                }
                else if (PtInRect(&backToModeButton, msg.x, msg.y))
                {
                    currentState = MODE_SELECTION;
                    return;
                }
            }
        }
        Sleep(1);// 减少CPU占用
    }
}

// 关闭游戏
void Game::close()
{
    closegraph();
}

// 显示主菜单
void Game::showMainMenu()
{
    // 绘制标题
    settextstyle(48, 0, _T("宋体"), 0, 0, FW_BOLD, false, false, false);
    settextcolor(RGB(70, 130, 180));
    outtextxy(WIDTH / 2 - 75, 100, _T("孔明棋"));

    //绘制副标题
    settextstyle(24, 0, _T("宋体"));
    settextcolor(RGB(100, 100, 150));
    outtextxy(WIDTH / 2 - 85, 180, _T("Peg Solitaire"));

    // 绘制菜单选项
    settextstyle(36, 0, _T("宋体"));

    // 开始游戏按钮
    setfillcolor(hoveredOption == CLASSIC_MODE ? RGB(100, 200, 100) : RGB(180, 230, 100));
    fillrectangle(startButton.left, startButton.top, startButton.right, startButton.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(WIDTH / 2 - 80, 260, _T("开始游戏"));

    // 游戏规则按钮
    setfillcolor(hoveredOption == GAME_RULES ? RGB(100, 180, 255) : RGB(180, 200, 255));
    fillrectangle(rulesButton.left, rulesButton.top, rulesButton.right, rulesButton.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(WIDTH / 2 - 80, 330, _T("游戏规则"));

    // 退出游戏按钮
    setfillcolor(hoveredOption == EXIT_GAME ? RGB(255, 150, 150) : RGB(255, 180, 180));
    fillrectangle(exitButton.left, exitButton.top, exitButton.right, exitButton.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(WIDTH / 2 - 80, 400, _T("退出游戏"));
}

// 显示模式选择界面
void Game::showModeSelection()
{
    // 绘制标题
    settextstyle(36, 0, _T("宋体"), 0, 0, FW_BOLD, false, false, false);
    settextcolor(RGB(70, 130, 180));
    outtextxy(WIDTH / 2 - 100, 150, _T("选择游戏模式"));

    // 绘制模式选项
    settextstyle(36, 0, _T("宋体"));

    // 经典模式按钮
    setfillcolor(hoveredOption == CLASSIC_MODE ? RGB(100, 200, 100) : RGB(180, 230, 100));
    fillrectangle(classicButton.left, classicButton.top, classicButton.right, classicButton.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(WIDTH / 2 - 80, 260, _T("经典模式"));

    // 残局模式按钮
    setfillcolor(hoveredOption == CHALLENGE_MODE ? RGB(100, 180, 255) : RGB(180, 200, 255));
    fillrectangle(challengeButton.left, challengeButton.top, challengeButton.right, challengeButton.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(WIDTH / 2 - 80, 330, _T("残局模式"));

    // 返回按钮
    setfillcolor(hoveredOption == EXIT_GAME ? RGB(255, 150, 150) : RGB(255, 180, 180));
    fillrectangle(backButton.left, backButton.top, backButton.right, backButton.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(WIDTH / 2 - 80, 400, _T("返回"));
}

// 显示游戏规则
void Game::showRules()
{
    settextstyle(36, 0, _T("宋体"), 0, 0, FW_BOLD, false, false, false);
    settextcolor(RGB(70, 130, 180));
    outtextxy(WIDTH / 2 - 150, 100, _T("游戏规则"));

    settextstyle(24, 0, _T("宋体"));
    settextcolor(RGB(80, 60, 30));

    int y = 180;
    outtextxy(100, y, _T("1. 棋子只能沿水平或垂直方向移动"));
    y += 40;
    outtextxy(100, y, _T("2. 每次移动必须跳过相邻的一个棋子"));
    y += 40;
    outtextxy(100, y, _T("3. 被跳过的棋子会被移除"));
    y += 40;
    outtextxy(100, y, _T("4. 目标位置必须为空"));
    y += 40;
    outtextxy(100, y, _T("5. 游戏目标：移除所有棋子，只剩一个"));
    y += 40;
    outtextxy(100, y, _T("6. 若剩下超过一个棋子且均不可移动则游戏结束"));
    y += 40;
    outtextxy(100, y, _T("7. 点击悔棋按钮可以撤销上一步操作"));
    y += 40;
    outtextxy(100, y, _T("8. 点击提示按钮可以显示可能的移动"));

    settextstyle(20, 0, _T("宋体"));
    settextcolor(RGB(100, 100, 150));
    outtextxy(WIDTH / 2 - 100, HEIGHT - 60, _T("点击任意位置返回菜单"));
}

// 显示游戏结束界面
void Game::showGameOver()
{
    settextstyle(48, 0, _T("宋体"), 0, 0, FW_BOLD, false, false, false);

    if (board.isWin())
    {
        settextcolor(RGB(40, 180, 40));
        outtextxy(WIDTH / 2 - 150, 100, _T("You win！"));
    }
    else
    {
        settextcolor(RGB(220, 40, 40));
        outtextxy(WIDTH / 2 - 150, 100, _T("You lose!"));
    }

    settextstyle(32, 0, _T("宋体"));
    settextcolor(RGB(80, 60, 30));
    TCHAR result[64];
    _stprintf_s(result, _T("剩余棋子: %d"), board.getRemainingPieces());
    outtextxy(WIDTH / 2 - 100, 180, result);

    setfillcolor(RGB(255, 200, 100));
    fillrectangle(restartButton.left, restartButton.top, restartButton.right, restartButton.bottom);
    settextcolor(RGB(0, 0, 0));
    settextstyle(24, 0, _T("宋体"));
    outtextxy(restartButton.left + 10, restartButton.top + 10, _T("重新开始"));

    setfillcolor(RGB(180, 230, 100));
    fillrectangle(menuButton.left, menuButton.top, menuButton.right, menuButton.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(menuButton.left + 10, menuButton.top + 10, _T("返回菜单"));
}

// 显示游戏界面
void Game::playGame()
{
    board.draw();

    settextstyle(20, 0, _T("宋体"));

    setfillcolor(RGB(255, 200, 100));
    fillrectangle(restartButtonInGame.left, restartButtonInGame.top, restartButtonInGame.right, restartButtonInGame.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(restartButtonInGame.left + 10, restartButtonInGame.top + 5, _T("重新开始"));

    setfillcolor(RGB(180, 230, 100));
    fillrectangle(backButtonInGame.left, backButtonInGame.top, backButtonInGame.right, backButtonInGame.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(backButtonInGame.left + 10, backButtonInGame.top + 5, _T("返回菜单"));

    setfillcolor(RGB(100, 180, 255));
    fillrectangle(undoButtonInGame.left, undoButtonInGame.top, undoButtonInGame.right, undoButtonInGame.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(undoButtonInGame.left + 10, undoButtonInGame.top + 5, _T("悔棋"));

    setfillcolor(RGB(255, 165, 0));
    fillrectangle(hintButtonInGame.left, hintButtonInGame.top, hintButtonInGame.right, hintButtonInGame.bottom);
    settextcolor(RGB(0, 0, 0));
    outtextxy(hintButtonInGame.left + 10, hintButtonInGame.top + 5, _T("提示"));
}

// 绘制背景图片
void Game::drawBackground() const
{
    putimage(0, 0, &backgroundImg);
}

// 检查点是否在矩形内
bool Game::PtInRect(const RECT* rect, int x, int y)
{
    return (x >= rect->left && x <= rect->right && y >= rect->top && y <= rect->bottom);
}