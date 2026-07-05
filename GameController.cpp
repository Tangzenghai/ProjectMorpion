#include "GameController.h"
#include <iostream>

GameController::GameController(GameMode mode)
    : game_(mode) {}

void GameController::run() {
    while (!game_.isGameOver()) {
        view_.draw(game_);
        handleTurn();
    }

    view_.draw(game_);
}

void GameController::handleTurn() {
    // TODO 6：
    // 1. 根据当前玩家和游戏模式，选择 HumanPlayer 或 AIPlayer
    // 2. 调用 play 获取坐标
    // 3. 调用 game_.makeMove(row, col)
    // 4. 如果落子失败，提示重新输入
    std::pair<int, int> move;

    if (game_.getMode() == GameMode::HumanVsAI) {
        // 人机对战模式
        if (game_.getCurrentPlayer() == CellState::X) {
            // X 是人类玩家
            move = game_.getHumanX().play(game_.getBoard());
        }
        else {
            // O 是 AI 玩家
            move = game_.getAIPlayer().play(game_.getBoard());
        }
    }
    else {
        // 双人对战模式
        if (game_.getCurrentPlayer() == CellState::X) {
            move = game_.getHumanX().play(game_.getBoard());
        }
        else {
            move = game_.getHumanO().play(game_.getBoard());
        }
    }

    if (!game_.makeMove(move.first, move.second)) {
        std::cout << "落子失败，请重试！\n";
    }
}