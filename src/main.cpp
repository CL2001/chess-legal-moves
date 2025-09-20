#include <iostream>
#include <functional>
#include "legal_moves.hpp"
#include "game_end.hpp"
#include "structs.hpp"

std::vector<int> legalMovesN(const ChessGame& game, int depth) {
    std::vector<int> totals(depth, 0);

    std::function<void(const ChessGame&, int)> dfs = [&](const ChessGame& g, int d) {
        if (d >= depth) return;

        std::vector<Move> moves = LegalMoves::generateLegalMoves(g);
        totals[d] += moves.size();

        for (const auto& move : moves) {
            dfs(move.chess_game, d + 1);
        }
    };

    dfs(game, 0);
    return totals;
}


int main() 
{
    std::cout << "Hello World from main" << std::endl;


    // Change this

    ChessGame game{
        .player_turn = Color::White,
        .board = {
            Piece{Color::White, PieceType::King}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::White, PieceType::Bishop}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::White, PieceType::Knight}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::Black, PieceType::King}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Black, PieceType::Bishop}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Black, PieceType::Knight}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}
        },
        .castle = {' ', ' ', ' ', ' '},
        .en_passant = -1,
        .winner = Winner::Nil
    };



    // Iteration 1
    std::vector<Move> moves = LegalMoves::generateLegalMoves(game);

    for (auto move : moves)
    {
        std::cout << "From " << move.from_square << " to " << move.to_square << std::endl;
    }

    // Winner
    game.winner = GameEnd::calculateEndGame(game, moves);
    switch (game.winner)
    {
    case Winner::White:
        std::cout << "White wins" << std::endl;
        break;

    case Winner::Black:
        std::cout << "Black wins" << std::endl;
        break;

    case Winner::Draw:
        std::cout << "Game is a draw" << std::endl;
        break;

    case Winner::Nil:
        std::cout << "No winner yet" << std::endl;
        break;

    default:
        std::cout << "Unknown game state" << std::endl;
        break;
    }


    // Iteration
    int depth = 4;
    std::vector<int> totals = legalMovesN(game, depth);

    for (int i = 0; i < depth; i++) {
        std::cout << "Depth " << i+1 << ": " << totals[i] << " moves\n";
    }
    return 0;
}
