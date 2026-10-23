#ifndef GAME_H
#define GAME_H

#include "board.h"

//Game（游戏）类
class Game
{
private:
    Board board;
    GameState currentState = MENU;
    MenuOption hoveredOption = NONE;
    GameMode selectedMode = CLASSIC;
    IMAGE backgroundImg; // 导入背景图片对象

    // 主菜单按钮（开始游戏、规则、退出）
    RECT startButton = { WIDTH / 2 - 100, 250, WIDTH / 2 + 100, 300 };
    RECT rulesButton = { WIDTH / 2 - 100, 320, WIDTH / 2 + 100, 370 };
    RECT exitButton = { WIDTH / 2 - 100, 390, WIDTH / 2 + 100, 440 };

    // 模式选择（经典或残局）按钮
    RECT classicButton = { WIDTH / 2 - 100, 250, WIDTH / 2 + 100, 300 };
    RECT challengeButton = { WIDTH / 2 - 100, 320, WIDTH / 2 + 100, 370 };
    RECT backButton = { WIDTH / 2 - 100, 390, WIDTH / 2 + 100, 440 };

    // 残局选择按钮
    RECT challenge1Button = { WIDTH / 2 - 220, 250, WIDTH / 2 - 20, 300 };
    RECT challenge2Button = { WIDTH / 2 + 20, 250, WIDTH / 2 + 220, 300 };
    RECT challenge3Button = { WIDTH / 2 - 220, 350, WIDTH / 2 - 20, 400 };
    RECT challenge4Button = { WIDTH / 2 + 20, 350, WIDTH / 2 + 220, 400 };
    RECT backToModeButton = { WIDTH / 2 - 100, 450, WIDTH / 2 + 100, 500 };

    // 游戏结束按钮（重新开始、返回菜单）
    RECT restartButton = { WIDTH / 2 - 150, 350, WIDTH / 2 - 30, 400 };
    RECT menuButton = { WIDTH / 2 + 30, 350, WIDTH / 2 + 150, 400 };

    // 游戏界面按钮（重启、返回菜单、悔棋、提示）
    RECT restartButtonInGame = { WIDTH - 370, HEIGHT - 40, WIDTH - 270, HEIGHT - 10 };
    RECT backButtonInGame = { WIDTH - 260, HEIGHT - 40, WIDTH - 160, HEIGHT - 10 };
    RECT undoButtonInGame = { WIDTH - 150, HEIGHT - 40, WIDTH - 50, HEIGHT - 10 };
    RECT hintButtonInGame = { WIDTH - 480, HEIGHT - 40, WIDTH - 380, HEIGHT - 10 };

public:
    void init();
    void run();
    void close();

private:
    void handleMouseInput();
    void showChallengeSelection();
    void showMainMenu();
    void showModeSelection();
    void showRules();
    void showGameOver();
    void playGame();
    void drawBackground() const;
    bool PtInRect(const RECT* rect, int x, int y);
};

#endif // GAME_H