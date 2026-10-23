#include "board.h"

// 获取指定位置状态
int Board::getState(int x, int y) const
{
    if (x >= 0 && x < 7 && y >= 0 && y < 7)
    {
        return state[x][y];
    }
    return -1;
}

// 获取剩余棋子数
int Board::getRemainingPieces() const
{
    return remainingPieces;
}

// 获取当前游戏模式
GameMode Board::getCurrentMode() const
{
    return currentMode;
}

// 选择或移动棋子
bool Board::selectOrMove(int mouseX, int mouseY)
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
bool Board::undoMove()
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
void Board::reset(GameMode mode)
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
bool Board::getHint()
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
std::string Board::encodeBoard() const
{
    std::string s;
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
            s += (state[i][j] == 1 ? '1' : '0');// 将棋子位置编码为字符串
    return s;
}

// 切换提示显示状态
void Board::toggleHint()
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
void Board::draw() const
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

// 尝试移动棋子
bool Board::tryMove(int fromX, int fromY, int toX, int toY) const
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
bool Board::canMove(int fromX, int fromY, int toX, int toY) const
{
    if (toX < 0 || toX >= 7 || toY < 0 || toY >= 7) return false;
    if (layout[toX][toY] != 1) return false;
    return tryMove(fromX, fromY, toX, toY);//再返回上面检查逻辑进行移动判断
}

// 优化后的评估函数 - 启发式函数
int Board::evaluateBoard() const
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
vector<AIMoveHint> Board::getAllPossibleMoves() const
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
Board Board::simulateMove(const AIMoveHint& move) const
{
    Board newBoard = *this;

    newBoard.state[move.fromX][move.fromY] = 0;
    newBoard.state[move.toX][move.toY] = 1;
    newBoard.state[(move.fromX + move.toX) / 2][(move.fromY + move.toY) / 2] = 0;
    newBoard.remainingPieces--;

    return newBoard;
}

// 使用A*算法寻找最佳移动
AIMoveHint Board::findBestMoveUsingAStar(int maxDepth) const
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
int Board::aStarSearch(const Board& board, int depth) const
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
bool Board::dfsSolve(Board& board, std::vector<AIMoveHint>& path, int depthLimit, std::unordered_set<std::string>* visited)
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

// 判断是否胜利
bool Board::isWin() const
{
    return remainingPieces == 1;
}

// 判断是否失败
bool Board::isLose() const
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