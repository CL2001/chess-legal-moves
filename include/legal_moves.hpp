// legal_moves.hpp
#pragma once
#include <vector>


enum class Color {
    White,
    Black
};

struct ChessGame
{
    Color player_turn{Color::White};
    char board[64]{
        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
        'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
    };
    char castle[4]{'K', 'Q', 'k', 'q'};
    int enPassant {-1};
};


struct Move
{
    int from_square;
    int to_square;
    ChessGame chess_game;
};



namespace LegalMoves
{
std::vector<Move> generateLegalMoves(ChessGame);
}