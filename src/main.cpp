#include <iostream>
#include "legal_moves.hpp"

std::vector<int> legalMoves4(ChessGame game1)
{
    std::vector<int> totals = {0, 0, 0, 0};
    std::vector<Move> moves1 = LegalMoves::generateLegalMoves(game1);
    totals[0] = moves1.size();
    for (auto move1 : moves1)
    {
        ChessGame game2 = LegalMoves::updateGame(game1, move1);
        std::vector<Move> moves2 = LegalMoves::generateLegalMoves(game2);
        totals[1] += moves2.size();

        for (auto move2 : moves2)
        {
            ChessGame game3 = LegalMoves::updateGame(game2, move2);
            std::vector<Move> moves3 = LegalMoves::generateLegalMoves(game3);
            totals[2] += moves3.size();

            for (auto move3 : moves3)
            {
                ChessGame game4 = LegalMoves::updateGame(game3, move3);
                std::vector<Move> moves4 = LegalMoves::generateLegalMoves(game4);
                totals[3] += moves4.size();        
            }             
        }   
    }
    return totals;
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

    // Iteration 4
    std::vector<int> totals = legalMoves4(game);
    std::cout << "After 1 iteration there is " << totals[0] << " moves possible" << std::endl;
    std::cout << "After 2 iteration there is " << totals[1] << " moves possible" << std::endl;
    std::cout << "After 3 iteration there is " << totals[2] << " moves possible" << std::endl;
    std::cout << "After 4 iteration there is " << totals[3] << " moves possible" << std::endl;
    return 0;
}
