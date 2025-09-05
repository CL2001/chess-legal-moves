#include <iostream>
#include "legal_moves.hpp"

std::vector<Move> legalMoves(std::vector<Move> previous_moves)
{
    std::vector<Move> next_moves;
    for (auto move : previous_moves)
    {
        std::vector<Move> res = LegalMoves::generateLegalMoves(move.chess_game);
        next_moves.insert(next_moves.end(), res.begin(), res.end());
    }
    return next_moves;
}


int main() 
{
    std::cout << "Hello World from main" << std::endl;


    // Change this
    ChessGame game{
        .player_turn = Color::Black,
        .board = {
            'R', 'N', ' ', ' ', 'K', 'B', 'N', 'R',
            'P', 'P', 'P', 'B', ' ', 'P', 'P', 'P',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', 'P', ' ', ' ', 'p', ' ', ' ',
            'p', 'p', 'p', ' ', 'p', ' ', 'p', 'p',
            'r', ' ', 'b', 'k', 'Q', 'b', 'n', 'r'
        },
        .castle = {'K', 'Q'},
        .enPassant = -1
    };

    

    // Iteration 1
    std::vector<Move> moves = LegalMoves::generateLegalMoves(game);

    for (auto move : moves)
    {
        std::cout << "From " << move.from_square << " to " << move.to_square << std::endl;
    }
    std::cout << "After 1 iteration there is " << moves.size() << " moves possible" << std::endl;

    // Iteration 2
    std::vector<Move> moves_iter2 = legalMoves(moves);
    std::cout << "After 2 iterations there is " << moves_iter2.size() << " moves possible" << std::endl;

    // Iteration 3
    std::vector<Move> moves_iter3 = legalMoves(moves_iter2);
    std::cout << "After 3 iterations there is " << moves_iter3.size() << " moves possible" << std::endl;

    // Iteration 4
    std::vector<Move> moves_iter4 = legalMoves(moves_iter3);
    std::cout << "After 4 iterations there is " << moves_iter4.size() << " moves possible" << std::endl;
    return 0;
}
