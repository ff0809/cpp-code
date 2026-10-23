#ifndef BOARD_H
#define BOARD_H

#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <climits>
#include <unordered_set>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 800;
const int CELL_SIZE = 80;
const int PIECE_RADIUS = 30;
const int OFFSET_X = (WIDTH - 7 * CELL_SIZE) / 2;
const int OFFSET_Y = (HEIGHT - 7 * CELL_SIZE) / 2;

// 菜单选项枚举
enum MenuOption
{
    CLASSIC_MODE,
    CHALLENGE_MODE,
    GAME_RULES,
    EXIT_GAME,
    NONE
};

// 游戏状态枚举
enum GameState
{
    MENU,
    MODE_SELECTION,
    PLAYING,
    SHOWING_RULES,
    GAME_OVER
};

// 游戏模式枚举
enum GameMode
{
    CLASSIC,
    CHALLENGE_1,
    CHALLENGE_2,
    CHALLENGE_3,
    CHALLENGE_4
};

// 存储移动历史的结构
struct MoveRecord
{
    int fromX, fromY;
    int toX, toY;
    int midX, midY;
};

// 存储AI提示的结构
struct AIMoveHint
{
    int fromX = -1, fromY = -1;
    int toX = -1, toY = -1;
};

//Board（棋盘）类
class Board
{
private:
    //经典布局定义
    const int layout[7][7] =
    {
        {0,0,1,1,1,0,0},
        {0,0,1,1,1,0,0},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {0,0,1,1,1,0,0},
        {0,0,1,1,1,0,0}
    };

    int state[7][7] = {};
    int selectedX = -1;
    int selectedY = -1;
    int remainingPieces = 32;
    stack<MoveRecord> history;// 存储移动历史
    AIMoveHint aiHint = {};// AI提示
    std::vector<AIMoveHint> solutionPath; // 存储完整解路径

    std::vector<AIMoveHint> optimalSolutionClassic;
    std::vector<AIMoveHint> optimalSolutionChallenge1;
    std::vector<AIMoveHint> optimalSolutionChallenge2;
    std::vector<AIMoveHint> optimalSolutionChallenge3;
    std::vector<AIMoveHint> optimalSolutionChallenge4;
    std::vector<AIMoveHint>* currentOptimalSolution = nullptr;
    int optimalStep = 0;
    bool followingOptimal = false;

    bool showHint = false;// 是否显示AI提示，用户点击提示按钮后显示，再次点击隐藏
    GameMode currentMode = CLASSIC;

    // 残局布局定义
    const int challenge1[7][7] =
    {
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0},
        {0,0,1,1,1,0,0},
        {0,0,1,1,1,0,0},
        {0,0,0,0,0,0,0}
    };

    const int challenge2[7][7] =
    {
        {0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0},
        {0,0,1,1,1,0,0},
        {0,1,0,0,0,1,0},
        {0,0,1,1,1,0,0},
        {0,0,1,0,1,0,0},
        {0,0,0,0,0,0,0}
    };

    const int challenge3[7][7] =
    {
        {0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0},
        {0,0,1,1,1,0,0},
        {0,1,1,1,1,1,0},
        {1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0}
    };

    const int challenge4[7][7] =
    {
        {0,0,0,1,0,0,0},
        {0,0,1,1,1,0,0},
        {0,1,1,1,1,1,0},
        {0,0,0,1,0,0,0},
        {0,0,0,1,0,0,0},
        {0,0,1,1,1,0,0},
        {0,0,1,1,1,0,0}
    };

public:
    // 获取指定位置状态
    int getState(int x, int y) const;

    // 获取剩余棋子数
    int getRemainingPieces() const;

    // 获取当前游戏模式
    GameMode getCurrentMode() const;

    // 选择或移动棋子
    bool selectOrMove(int mouseX, int mouseY);

    // 悔棋操作
    bool undoMove();

    // 重置棋盘
    void reset(GameMode mode = CLASSIC);

    bool getHint();

    // 局面编码函数
    std::string encodeBoard() const;

    // 切换提示显示状态
    void toggleHint();

    // 绘制棋盘和棋子
    void draw() const;

    // 判断是否胜利
    bool isWin() const;

    // 判断是否失败
    bool isLose() const;

private:
    // 尝试移动棋子
    bool tryMove(int fromX, int fromY, int toX, int toY) const;

    // 检查单步移动是否合法
    bool canMove(int fromX, int fromY, int toX, int toY) const;

    // 优化后的评估函数 - 启发式函数
    int evaluateBoard() const;

    // 获取所有可能的移动
    vector<AIMoveHint> getAllPossibleMoves() const;

    // 模拟移动后的状态
    Board simulateMove(const AIMoveHint& move) const;

    // 使用A*算法寻找最佳移动
    AIMoveHint findBestMoveUsingAStar(int maxDepth = 3) const;

    // A*搜索算法
    int aStarSearch(const Board& board, int depth) const;

    // DFS求解
    bool dfsSolve(Board& board, std::vector<AIMoveHint>& path, int depthLimit = 40, std::unordered_set<std::string>* visited = nullptr);
};

#endif // BOARD_H