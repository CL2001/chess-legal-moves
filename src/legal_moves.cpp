// legal_moves.cpp
#include "legal_moves.hpp"

Color getPieceColor(char piece)
{
    //std::cout << piece << std::endl;
    if (piece == ' ')
    {
        return Color::Nil;
    }
    return piece < 90 ? Color::White : Color::Black;
}


std::vector<Move> generatePseudoLegalMoves(ChessGame chess_game)
{
    std::vector<Move> pseudo_moves;

    if (chess_game.player_turn == Color::White)
    {
        for (int i = 0; i < 64; i++)
        {
            std::vector<Move> new_moves;
            switch (chess_game.board[i]) 
            {
            case 'P':
                break;
            case 'R':
                break;
            case 'N':
                break;
            case 'B':
                break;
            case 'Q':
                break;
            case 'k':
                break;
            default:
                break;
            } 
            // Insturction here
        }
    }
    else
    {
        for (int i = 0; i < 64; i++)
        {
            switch (chess_game.board[i]) 
            {
            case 'p':
                break;
            case 'r':
                break;
            case 'n':
                break;
            case 'b':
                break;
            case 'q':
                break;
            case 'k':
                break;
            default:
                break;
            }
        }
    }
    return pseudo_moves;
}

std::vector<Move> LegalMoves::generateLegalMoves(ChessGame chess_game)
{
    std::vector<Move> moves = generatePseudoLegalMoves(chess_game);
    
    return moves;
}