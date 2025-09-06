// legal_moves.hpp
#pragma once
#include <vector>
#include <iostream>


enum class Color {
    White,
    Black,
    Nil
};

enum class PieceType {
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
    Nil
};


struct Piece {
    Color color;
    PieceType piece_type;
};

struct ChessGame
{
    Color player_turn{Color::White};
    Piece board[64]{
        // Rank 1 (White back rank)
        Piece{Color::White, PieceType::Rook},
        Piece{Color::White, PieceType::Knight},
        Piece{Color::White, PieceType::Bishop},
        Piece{Color::White, PieceType::Queen},
        Piece{Color::White, PieceType::King},
        Piece{Color::White, PieceType::Bishop},
        Piece{Color::White, PieceType::Knight},
        Piece{Color::White, PieceType::Rook},

        // Rank 2 (White pawns)
        Piece{Color::White, PieceType::Pawn}, Piece{Color::White, PieceType::Pawn},
        Piece{Color::White, PieceType::Pawn}, Piece{Color::White, PieceType::Pawn},
        Piece{Color::White, PieceType::Pawn}, Piece{Color::White, PieceType::Pawn},
        Piece{Color::White, PieceType::Pawn}, Piece{Color::White, PieceType::Pawn},

        // Rank 3
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},

        // Rank 4
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},

        // Rank 5
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},

        // Rank 6
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
        Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},

        // Rank 7 (Black pawns)
        Piece{Color::Black, PieceType::Pawn}, Piece{Color::Black, PieceType::Pawn},
        Piece{Color::Black, PieceType::Pawn}, Piece{Color::Black, PieceType::Pawn},
        Piece{Color::Black, PieceType::Pawn}, Piece{Color::Black, PieceType::Pawn},
        Piece{Color::Black, PieceType::Pawn}, Piece{Color::Black, PieceType::Pawn},

        // Rank 8 (Black back rank)
        Piece{Color::Black, PieceType::Rook},
        Piece{Color::Black, PieceType::Knight},
        Piece{Color::Black, PieceType::Bishop},
        Piece{Color::Black, PieceType::Queen},
        Piece{Color::Black, PieceType::King},
        Piece{Color::Black, PieceType::Bishop},
        Piece{Color::Black, PieceType::Knight},
        Piece{Color::Black, PieceType::Rook},
    };
    char castle[4]{'K', 'Q', 'k', 'q'};
    int enPassant {-1};
};


struct Move
{
    int from_square;
    int to_square;
    Piece promotion;

    Move(int from, int to, Piece promo = Piece{Color::Nil, PieceType::Nil})
        : from_square(from), to_square(to), promotion(promo) {}
};



namespace LegalMoves
{
std::vector<Move> generateLegalMoves(ChessGame);
ChessGame updateGame(ChessGame, Move);
}