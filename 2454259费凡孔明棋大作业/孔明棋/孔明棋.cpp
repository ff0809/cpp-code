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
	// 管理孔明棋的棋盘和棋子状态，存储游戏状态和历史记录
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

	//每种模式的最优解流程（后续如果用户按照最优解流程进行游戏，则可以直接跟随，开始就使用AI提示直到最后可以直接成功）
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

//走棋模式及其他特定功能实现
public:
    // 获取指定位置状态
    int getState(int x, int y) const //const表示该函数不会修改类的成员变量
    {
        if (x >= 0 && x < 7 && y >= 0 && y < 7)
        {
            return state[x][y];
        }
        return -1;
    }

    // 获取剩余棋子数
    int getRemainingPieces() const
    {
        return remainingPieces;
    }

    // 获取当前游戏模式
    GameMode getCurrentMode() const
    {
        return currentMode;
    }

    // 选择或移动棋子
    bool selectOrMove(int mouseX, int mouseY)
    {
        int col = (mouseX - OFFSET_X) / CELL_SIZE;
        int row = (mouseY - OFFSET_Y) / CELL_SIZE;

        if (row < 0 || row >= 7 || col < 0 || col >= 7 || layout[row][col] != 1)
        {
            return false;
        }

        if (state[row][col] == 1)
        {
            selectedX = row;
            selectedY = col;
            showHint = false;
            return true;
        }

        if (selectedX != -1 && selectedY != -1 && state[row][col] == 0)
        {
            if (tryMove(selectedX, selectedY, row, col))
            {
                MoveRecord record;
                record.fromX = selectedX;
                record.fromY = selectedY;
                record.toX = row;
                record.toY = col;
                record.midX = (selectedX + row) / 2;
                record.midY = (selectedY + col) / 2;
                history.push(record);

                state[selectedX][selectedY] = 0;
                state[row][col] = 1;
                remainingPieces--;
                state[record.midX][record.midY] = 0;

                // 判断是否还在最优解流程上
                if (followingOptimal && currentOptimalSolution && optimalStep < (int)currentOptimalSolution->size())
                {
                    AIMoveHint move = (*currentOptimalSolution)[optimalStep];
                    if (selectedX == move.fromX && selectedY == move.fromY && row == move.toX && col == move.toY)
                    {
                        optimalStep++;
                    }
					else     // 如果当前移动不符合最优解流程，则不再跟随
                    {
                        followingOptimal = false;
                    }
                }

                selectedX = -1;
                selectedY = -1;
                showHint = false;
                return true;
            }
        }
        return false;
    }

    // 悔棋操作
    bool undoMove()
    {
        if (history.empty())
        {
            return false;
        }

        MoveRecord record = history.top();
        history.pop();

        state[record.fromX][record.fromY] = 1;
        state[record.toX][record.toY] = 0;
        state[record.midX][record.midY] = 1;

        remainingPieces++;

        selectedX = -1;
        selectedY = -1;
        showHint = false;

        // 悔棋时回退optimalStep
        if (followingOptimal && optimalStep > 0)
        {
            optimalStep--;
        }
        // 检查历史和当前最优解流程是否一致
        if (currentOptimalSolution && !history.empty())
        {
            std::stack<MoveRecord> tmpHistory = history;
            int step = (int)tmpHistory.size() - 1;
            bool stillOptimal = true;
            while (!tmpHistory.empty() && step >= 0)
            {
                MoveRecord rec = tmpHistory.top();
                tmpHistory.pop();
                if (step >= (int)currentOptimalSolution->size() ||
                    rec.fromX != (*currentOptimalSolution)[step].fromX ||
                    rec.fromY != (*currentOptimalSolution)[step].fromY ||
                    rec.toX != (*currentOptimalSolution)[step].toX ||
                    rec.toY != (*currentOptimalSolution)[step].toY)
                {
                    stillOptimal = false;
                    break;
                }
                step--;
            }
            followingOptimal = stillOptimal;
            if (stillOptimal)
                optimalStep = (int)history.size();
        }

        return true;
    }

    // 重置棋盘
    void reset(GameMode mode = CLASSIC)
    {
        currentMode = mode;

        switch (mode)
        {
        case CLASSIC:
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 7; j++)
                    state[i][j] = (i == 3 && j == 3) ? 0 : layout[i][j];
            remainingPieces = 32;
            break;
        case CHALLENGE_1:
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 7; j++)
                    state[i][j] = challenge1[i][j];
            remainingPieces = 7;
            break;
        case CHALLENGE_2:
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 7; j++)
                    state[i][j] = challenge2[i][j];
            remainingPieces = 12;
            break;
        case CHALLENGE_3:
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 7; j++)
                    state[i][j] = challenge3[i][j];
            remainingPieces = 16;
            break;
        case CHALLENGE_4:
            for (int i = 0; i < 7; i++)
                for (int j = 0; j < 7; j++)
                    state[i][j] = challenge4[i][j];
            remainingPieces = 17;
            break;
        }

        selectedX = -1;
        selectedY = -1;
        while (!history.empty())
			history.pop();// 清空历史记录
        showHint = false;

        // 生成/切换最优解流程
        switch (mode) 
        {
        case CLASSIC: 
        {
			if (optimalSolutionClassic.empty()) // 如果最优解流程为空，则生成最优解
            {
                Board tmp = *this;
				std::unordered_set<std::string> visited;// 用于记录访问过的局面
				dfsSolve(tmp, optimalSolutionClassic, 60, &visited);// 深度优先搜索（DFS）求解最优解
            }
			currentOptimalSolution = &optimalSolutionClassic;// 切换到经典模式的最优解流程
            break;
        }
        case CHALLENGE_1: 
        {
            if (optimalSolutionChallenge1.empty()) 
            {
                Board tmp = *this;
                std::unordered_set<std::string> visited;
                dfsSolve(tmp, optimalSolutionChallenge1, 30, &visited);
            }
            currentOptimalSolution = &optimalSolutionChallenge1;
            break;
        }
        case CHALLENGE_2: 
        {
            if (optimalSolutionChallenge2.empty()) 
            {
                Board tmp = *this;
                std::unordered_set<std::string> visited;
                dfsSolve(tmp, optimalSolutionChallenge2, 30, &visited);
            }
            currentOptimalSolution = &optimalSolutionChallenge2;
            break;
        }
        case CHALLENGE_3: 
        {
            if (optimalSolutionChallenge3.empty()) 
            {
                Board tmp = *this;
                std::unordered_set<std::string> visited;
                dfsSolve(tmp, optimalSolutionChallenge3, 30, &visited);
            }
            currentOptimalSolution = &optimalSolutionChallenge3;
            break;
        }
        case CHALLENGE_4: 
        {
            if (optimalSolutionChallenge4.empty()) 
            {
                Board tmp = *this;
                std::unordered_set<std::string> visited;
                dfsSolve(tmp, optimalSolutionChallenge4, 30, &visited);
            }
            currentOptimalSolution = &optimalSolutionChallenge4;
            break;
        }
        default:
            currentOptimalSolution = nullptr;
            break;
        }
        optimalStep = 0;
        followingOptimal = (currentOptimalSolution && !currentOptimalSolution->empty());
    }

    // AI提示
    bool getHint()
    {
        // 如果还在最优解流程上，直接提示最优解的下一步
        if (followingOptimal && currentOptimalSolution && optimalStep < (int)currentOptimalSolution->size())
        {
            aiHint = (*currentOptimalSolution)[optimalStep];
            showHint = true;
            return true;
        }
        // 否则降级为A*
        solutionPath.clear();
        Board tmp = *this;
        std::unordered_set<std::string> visited;
        aiHint = findBestMoveUsingAStar(3);
        showHint = (aiHint.fromX != -1 && aiHint.fromY != -1);
        return showHint;
    }

    // 局面编码函数
    std::string encodeBoard() const
    {
        std::string s;
        for (int i = 0; i < 7; ++i)
            for (int j = 0; j < 7; ++j)
                s += (state[i][j] == 1 ? '1' : '0');// 将棋子位置编码为字符串
        return s;
    }

    // 切换提示显示状态
    void toggleHint()
    {
        if (showHint)
        {
            showHint = false;// 隐藏AI提示
        }
        else
        {
            getHint();// 获取AI提示
        }
    }

    // 绘制棋盘和棋子
    void draw() const
    {
        // 显示当前模式
        settextstyle(24, 0, _T("宋体"));
        settextcolor(RGB(80, 60, 30));

        const TCHAR* modeText = _T("经典模式");
        switch (currentMode)
        {
        case CHALLENGE_1: modeText = _T("残局1"); break;
        case CHALLENGE_2: modeText = _T("残局2"); break;
        case CHALLENGE_3: modeText = _T("残局3"); break;
        case CHALLENGE_4: modeText = _T("残局4"); break;
        }
        outtextxy(50, OFFSET_Y - 50, modeText);

        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (layout[i][j] == 1)
                {
                    int x = OFFSET_X + j * CELL_SIZE;
                    int y = OFFSET_Y + i * CELL_SIZE;

                    setfillcolor(RGB(245, 230, 180));// 棋盘格子颜色
                    fillrectangle(x, y, x + CELL_SIZE, y + CELL_SIZE);

                    setlinecolor(RGB(180, 150, 90));// 棋盘格子边框颜色
                    setlinestyle(PS_SOLID, 2);
                    rectangle(x, y, x + CELL_SIZE, y + CELL_SIZE);

                    if (state[i][j] == 1)
                    {
                        if (i == selectedX && j == selectedY)
                        {
                            setfillcolor(RGB(40, 180, 40));//被选中的棋子颜色
                            setlinecolor(RGB(0, 120, 0));
                        }
                        else if (showHint && i == aiHint.fromX && j == aiHint.fromY)
                        {
                            setfillcolor(RGB(255, 165, 0));//AI提示的棋子颜色 
                            setlinecolor(RGB(200, 120, 0));
                        }
                        else
                        {
                            setfillcolor(RGB(220, 40, 40));//未被选中的棋子颜色
                            setlinecolor(RGB(180, 0, 0));
                        }
                        fillcircle(x + CELL_SIZE / 2, y + CELL_SIZE / 2, PIECE_RADIUS);// 绘制棋子
                        circle(x + CELL_SIZE / 2, y + CELL_SIZE / 2, PIECE_RADIUS);
                    }
                    else if (showHint && i == aiHint.toX && j == aiHint.toY)
                    {
                        setfillcolor(RGB(255, 255, 0));// AI提示的目标位置颜色
                        fillcircle(x + CELL_SIZE / 2, y + CELL_SIZE / 2, 20);
                    }
                }
            }
        }

        settextstyle(28, 0, _T("宋体"), 0, 0, FW_BOLD, false, false, false);
        settextcolor(RGB(220, 150, 126));
        TCHAR text[32];
        _stprintf_s(text, _T("剩余棋子：%d"), remainingPieces);
        int textWidth = textwidth(text);
        outtextxy((WIDTH - textWidth) / 2, OFFSET_Y - 50, text);
    }
//管理棋子移动合法性及AI提示逻辑
private:
    // 尝试移动棋子
    bool tryMove(int fromX, int fromY, int toX, int toY) const
    {
        if (state[toX][toY] != 0)
        {
            return false;
        }

        if (fromX == toX) //检查横向是否能移动
        {
            int distance = abs(fromY - toY);
            if (distance != 2)
            {
                return false;
            }

            int midY = (fromY + toY) / 2;
            if (state[fromX][midY] != 1)
            {
                return false;
            }
        }
        else if (fromY == toY)
        {
            int distance = abs(fromX - toX);
            if (distance != 2)
            {
                return false;
            }

            int midX = (fromX + toX) / 2;
            if (state[midX][fromY] != 1)
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        return true;
    }

    // 检查单步移动是否合法
    bool canMove(int fromX, int fromY, int toX, int toY) const
    {
        if (toX < 0 || toX >= 7 || toY < 0 || toY >= 7) return false;
        if (layout[toX][toY] != 1) return false;
        return tryMove(fromX, fromY, toX, toY);//再返回上面检查逻辑进行移动判断
    }

    // 优化后的评估函数 - 启发式函数
    int evaluateBoard() const
    {
        // 剩余棋子越少越好，可移动棋子越多越好，中心权重高
        int score = remainingPieces * 100;

        // 统计可移动棋子数
        int movable = 0;
        for (int i = 0; i < 7; ++i)
            for (int j = 0; j < 7; ++j)
                if (state[i][j] == 1)
                    if (canMove(i, j, i - 2, j) || canMove(i, j, i + 2, j) ||
                        canMove(i, j, i, j - 2) || canMove(i, j, i, j + 2))
                        ++movable;
        score -= movable * 10;

        // 中心权重（鼓励棋子靠近中心）
        static const int centerWeight[7][7] =
        {
            {0,0,1,2,1,0,0},
            {0,1,2,3,2,1,0},
            {1,2,4,5,4,2,1},
            {2,3,5,8,5,3,2},
            {1,2,4,5,4,2,1},
            {0,1,2,3,2,1,0},
            {0,0,1,2,1,0,0}
        };
        int centerScore = 0;
        for (int i = 0; i < 7; ++i)
            for (int j = 0; j < 7; ++j)
                if (state[i][j] == 1)
                    centerScore += centerWeight[i][j];
        score -= centerScore * 2;

        return score;
    }

    // 获取所有可能的移动
    vector<AIMoveHint> getAllPossibleMoves() const
    {
        vector<AIMoveHint> moves;

        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                if (state[i][j] == 1)
                {
                    // 检查四个方向的移动
                    if (canMove(i, j, i - 2, j))
                    {
                        moves.push_back({ i, j, i - 2, j });// 添加移动提示
                    }
                    if (canMove(i, j, i + 2, j))
                    {
                        moves.push_back({ i, j, i + 2, j });
                    }
                    if (canMove(i, j, i, j - 2))
                    {
                        moves.push_back({ i, j, i, j - 2 });
                    }
                    if (canMove(i, j, i, j + 2))
                    {
                        moves.push_back({ i, j, i, j + 2 });
                    }
                }
            }
        }

        return moves;
    }

    // 模拟移动后的状态
    Board simulateMove(const AIMoveHint& move) const
    {
        Board newBoard = *this;

        newBoard.state[move.fromX][move.fromY] = 0;
        newBoard.state[move.toX][move.toY] = 1;
        newBoard.state[(move.fromX + move.toX) / 2][(move.fromY + move.toY) / 2] = 0;
        newBoard.remainingPieces--;

        return newBoard;
    }

    // 使用A*算法寻找最佳移动
    AIMoveHint findBestMoveUsingAStar(int maxDepth = 3) const
    {
        vector<AIMoveHint> allMoves = getAllPossibleMoves();
        if (allMoves.empty()) return AIMoveHint(); // 返回无效提示

        // 评估每个可能的移动
        vector<pair<int, AIMoveHint>> scoredMoves;

        for (const auto& move : allMoves)
        {
            Board newBoard = simulateMove(move);
            int score = aStarSearch(newBoard, maxDepth - 1);
            scoredMoves.emplace_back(score, move);
        }

        if (scoredMoves.empty()) return AIMoveHint();

        // 选择得分最低的移动（分数越低越好）
        auto bestMove = min_element(scoredMoves.begin(), scoredMoves.end(),
            [](const pair<int, AIMoveHint>& a, const pair<int, AIMoveHint>& b)
            {
                return a.first < b.first;
            });

        return bestMove->second;
    }

    // A*搜索算法
    int aStarSearch(const Board& board, int depth) const
    {
        if (depth == 0 || board.isWin() || board.isLose())
        {
            return board.evaluateBoard();
        }

        vector<AIMoveHint> moves = board.getAllPossibleMoves();
        if (moves.empty())
        {
            return board.evaluateBoard();
        }

        int minScore = INT_MAX;

        for (const auto& move : moves)
        {
            Board newBoard = board.simulateMove(move);
            // 剪枝：如果已经胜利，直接返回最优分数
            if (newBoard.isWin()) return newBoard.evaluateBoard();
            int score = aStarSearch(newBoard, depth - 1);
            if (score < minScore)
            {
                minScore = score;
            }
        }

        return minScore;
    }

	// dfsSolve增加visited参数，避免重复访问相同局面
    bool dfsSolve(Board& board, std::vector<AIMoveHint>& path, int depthLimit = 40, std::unordered_set<std::string>* visited = nullptr)
    {
        if (board.isWin()) return true;
        if (board.isLose() || depthLimit <= 0) return false;

		// 判定是否有重复局面
        if (visited)
        {
            std::string code = board.encodeBoard();
            if (visited->count(code)) return false;
            visited->insert(code);
        }
		// 如果当前局面已经在路径中，避免重复访问
        auto moves = board.getAllPossibleMoves();
        for (const auto& move : moves)
        {
            Board next = board.simulateMove(move);
            path.push_back(move);
            if (dfsSolve(next, path, depthLimit - 1, visited)) return true;
            path.pop_back();
        }
        return false;
    }

public:
    // 判断是否胜利
    bool isWin() const
    {
        return remainingPieces == 1;
    }

    // 判断是否失败
    bool isLose() const
    {
        if (remainingPieces <= 1) return false;

        for (int i = 0; i < 7; ++i)
        {
            for (int j = 0; j < 7; ++j)
            {
                if (state[i][j] == 1)
                {
                    if (canMove(i, j, i - 2, j) || canMove(i, j, i + 2, j) || canMove(i, j, i, j - 2) || canMove(i, j, i, j + 2))
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};// Board类结束标志


//Game（游戏）类
class Game 
{
       // 游戏状态和菜单选项定义
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

//整个游戏流程实现
public:
    void init() 
    {
        initgraph(WIDTH, HEIGHT);
        setbkcolor(WHITE);
        loadimage(&backgroundImg, _T("jidi.jpg")); // 加载背景图片
    }

    void run() 
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

    void handleMouseInput() 
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

    void showChallengeSelection() 
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

    void close() 
    {
        closegraph();
    }

//UI界面绘制
private:
    void showMainMenu() 
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

    void showModeSelection() 
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

    void showRules() 
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

    void showGameOver() 
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

    void playGame() 
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

	// 绘制导入图片背景
    void drawBackground() const
    {
        putimage(0,0,&backgroundImg);
    }


	// 检查点是否在矩形内
    bool PtInRect(const RECT* rect, int x, int y) 
    {
        return (x >= rect->left && x <= rect->right && y >= rect->top && y <= rect->bottom);
    }
};// Game类结束标志

int main() 
{
	Game game;// 创建游戏对象
	game.init();// 初始化游戏
	game.run();// 运行游戏主循环
	game.close();// 关闭图形窗口
    return 0;
}