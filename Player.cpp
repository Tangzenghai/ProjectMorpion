#include "Player.h"
#include <iostream>
#include <limits>

Player::Player(CellState mark) : mark_(mark) {}

CellState Player::getMark() const {
    return mark_;
}

HumanPlayer::HumanPlayer(CellState mark) : Player(mark) {}

std::pair<int, int> HumanPlayer::play(const Board& board) {
    // TODO 2：
    // 1. 从命令行输入 row 和 col
    // 2. 如果输入非法，需要清理输入流
    // 3. 返回玩家输入的坐标
    int row, col;

    while (true) {
        std::cout << "请输入落子坐标（行 列，用空格分隔，范围 0~2）：";

        if (!(std::cin >> row >> col)) {
            // 输入非法（非数字），清理输入流
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "输入无效，请重新输入！\n";
            continue;
        }

        // 检查坐标是否在棋盘范围内
        if (!board.isInside(row, col)) {
            std::cout << "坐标超出范围（0~2），请重新输入！\n";
            continue;
        }

        // 检查格子是否已被占用
        if (!board.isEmpty(row, col)) {
            std::cout << "该位置已被占用，请重新输入！\n";
            continue;
        }

        return { row, col };
    }
}

  

AIPlayer::AIPlayer(CellState mark) : Player(mark) {}

std::pair<int, int> AIPlayer::play(const Board& board) {
    // TODO 3：
    // 简单 AI：从左到右、从上到下寻找第一个空格
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board.isEmpty(row, col)) {
                std::cout << "AI 落子位置：(" << row << ", " << col << ")\n";
                return { row, col };
            }
        }
    }

    // 棋盘已满（正常情况下不会走到这里）
    return { -1, -1 };
}