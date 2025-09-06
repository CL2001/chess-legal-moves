// legal_moves.cpp
#include "legal_moves.hpp"

std::vector<Move> castleMoves(ChessGame chess_game)
{
    std::vector<Move> moves;
    return moves;
}

std::vector<Move> whitePawnMoves(const Piece board[64], int index)
{
    std::vector<Move> moves;
    // Invalid
    if (index >= 56 && index <= 63)
    {
        return moves;
    }

    // Double move
    if (index >= 8 && index <= 15 && board[index + 8].piece_type == PieceType::Nil && board[index + 16].piece_type == PieceType::Nil)
    {
        moves.push_back(Move{index, index + 16, Piece{Color::Nil, PieceType::Nil}});
    }

    // Move up
    if (board[index + 8].piece_type == PieceType::Nil)
    {
        moves.push_back(Move{index, index + 8, Piece{Color::Nil, PieceType::Nil}});
    }

    // Diagonal left
    if (board[index + 7].color == Color::Black)
    {
        moves.push_back(Move{index, index + 7, Piece{Color::Nil, PieceType::Nil}});
    }

    // Diagonal right
    if (board[index + 9].color == Color::Black)
    {
        moves.push_back(Move{index, index + 9, Piece{Color::Nil, PieceType::Nil}});
    }

    // Promotion
    if (index >= 48 && index <= 55)
    {
        std::vector<Move> new_moves;
        for (auto move : moves)
        {
            moves.push_back(Move{move.from_square, move.to_square, {Color::White, PieceType::Queen}});
            moves.push_back(Move{move.from_square, move.to_square, {Color::White, PieceType::Knight}});
            moves.push_back(Move{move.from_square, move.to_square, {Color::White, PieceType::Bishop}});
            moves.push_back(Move{move.from_square, move.to_square, {Color::White, PieceType::Rook}});
        }
        return new_moves;
    }
    return moves;
}

std::vector<Move> blackPawnMoves(const Piece board[64], int index)
{
    std::vector<Move> moves;
    // Invalid
    if (index >= 0 && index <= 7)
    {
        return moves;
    }

    // Double move
    if (index >= 48 && index <= 55 && board[index - 8].piece_type == PieceType::Nil && board[index - 16].piece_type == PieceType::Nil)
    {
        moves.push_back(Move{index, index - 16, Piece{Color::Nil, PieceType::Nil}});
    }

    // Move up
    if (board[index - 8].piece_type == PieceType::Nil)
    {
        moves.push_back(Move{index, index - 8, Piece{Color::Nil, PieceType::Nil}});
    }

    // Diagonal left
    if (board[index - 7].color == Color::White)
    {
        moves.push_back(Move{index, index - 7, Piece{Color::Nil, PieceType::Nil}});
    }

    // Diagonal right
    if (board[index - 9].color == Color::White)
    {
        moves.push_back(Move{index, index - 9, Piece{Color::Nil, PieceType::Nil}});
    }

    // Promotion
    if (index >= 8 && index <= 15)
    {
        std::vector<Move> new_moves;
        for (auto move : moves)
        {
            moves.push_back(Move{move.from_square, move.to_square, {Color::Black, PieceType::Queen}});
            moves.push_back(Move{move.from_square, move.to_square, {Color::Black, PieceType::Knight}});
            moves.push_back(Move{move.from_square, move.to_square, {Color::Black, PieceType::Bishop}});
            moves.push_back(Move{move.from_square, move.to_square, {Color::Black, PieceType::Rook}});
        }
        return new_moves;
    }
    return moves;
}

std::vector<Move> knightMoves(const Piece board[64], int index)
{
    std::vector<Move> moves;
    Color piece_color = board[index].color;

    int knight_moves[8] = {-17, -15, -10, -6, 6, 10, 15, 17}; // kight moves (not magic numbers)
    for (int i = 0; i < 8; i++)
    {
        int to_square = knight_moves[i];
        if (board[index].color != piece_color)
        {
            moves.push_back(Move{index, to_square, Piece{Color::Nil, PieceType::Nil}});
        }
    }
    return moves;
}


std::vector<Move> bishopMoves(const Piece board[64], int index)
{
    std::vector<Move> moves;
    Color piece_color = board[index].color;

    // bottom left
    int bottom_left_index = index - 9;
    while (bottom_left_index % 8 != 7 && bottom_left_index >= 0)
    {
        if (board[index].color == Color::Nil)
        {
            moves.push_back(Move{index, bottom_left_index, Piece{Color::Nil, PieceType::Nil}});
        }
        else if (board[index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move{index, bottom_left_index, Piece{Color::Nil, PieceType::Nil}});
            break;
        }
        bottom_left_index -= 9;
    }

    // bottom right
    int bottom_right_index = index - 7;
    while (bottom_right_index % 8 != 0 && bottom_right_index >= 0)
    {
        if (board[index].color == Color::Nil)
        {
            moves.push_back(Move{index, bottom_right_index, Piece{Color::Nil, PieceType::Nil}});
        }
        else if (board[index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move{index, bottom_right_index, Piece{Color::Nil, PieceType::Nil}});
            break;
        }
        bottom_right_index -= 7;
    }

    // up left
    int up_left_index = index + 7;
    while (up_left_index % 8 != 7 && up_left_index < 64)
    {
        if (board[index].color == Color::Nil)
        {
            moves.push_back(Move{index, up_left_index, Piece{Color::Nil, PieceType::Nil}});
        }
        else if (board[index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move{index, up_left_index, Piece{Color::Nil, PieceType::Nil}});
            break;
        }
        up_left_index += 7;
    }

    // up right
    int up_right_index = index + 9;
    while (up_right_index % 8 != 0 && up_right_index < 64)
    {
        if (board[index].color == Color::Nil)
        {
            moves.push_back(Move{index, up_right_index, Piece{Color::Nil, PieceType::Nil}});
        }
        else if (board[index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move{index, up_right_index, Piece{Color::Nil, PieceType::Nil}});
            break;
        }
        up_right_index += 9;
    }
    return moves;
}


std::vector<Move> rookMoves(const Piece board[64], int index)
{
    std::vector<Move> moves;
    Color piece_color = board[index].color;

    // left
    int left_index = index - 1;
    while (left_index % 8 != 7)
    {
        if (board[index].color == Color::Nil)
        {
            moves.push_back(Move{index, left_index, Piece{Color::Nil, PieceType::Nil}});
        }
        else if (board[index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move{index, left_index, Piece{Color::Nil, PieceType::Nil}});
            break;
        }
        left_index--;
    }

    // right
    int right_index = index + 1;
    while (right_index % 8 != 0)
    {
        if (board[index].color == Color::Nil)
        {
            moves.push_back(Move{index, right_index, Piece{Color::Nil, PieceType::Nil}});
        }
        else if (board[index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move{index, right_index, Piece{Color::Nil, PieceType::Nil}});
            break;
        }
        right_index++;
    }

    // bottom
    int bottom_index = index - 8;
    while (bottom_index >= 0)
    {
        if (board[index].color == Color::Nil)
        {
            moves.push_back(Move{index, bottom_index, Piece{Color::Nil, PieceType::Nil}});
        }
        else if (board[index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move{index, bottom_index, Piece{Color::Nil, PieceType::Nil}});
            break;
        }
        bottom_index -= 8;
    }

    // up
    int up_index = index + 8;
    while (up_index < 64)
    {
        if (board[index].color == Color::Nil)
        {
            moves.push_back(Move{index, up_index, Piece{Color::Nil, PieceType::Nil}});
        }
        else if (board[index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move{index, up_index, Piece{Color::Nil, PieceType::Nil}});
            break;
        }
        up_index += 8;
    }

    return moves;
}

std::vector<Move> kingMoves(const Piece board[64], int index)
{
    std::vector<Move> moves;
    Color piece_color = board[index].color;

    int knight_moves[8] = {-9, -8, -7, -1, 1, 7, 8, 9}; // king moves (not magic numbers)
    for (int i = 0; i < 8; i++)
    {
        int to_square = knight_moves[i];
        if (board[index].color != piece_color)
        {
            moves.push_back(Move{index, to_square, Piece{Color::Nil, PieceType::Nil}});
        }
    }
    return moves;
}

std::vector<Move> generatePseudoLegalMoves(ChessGame chess_game)
{
    std::vector<Move> pseudo_moves;

    // En passant

    // Normal
    for (int i = 0; i < 64; i++)
    {  
        Piece piece = chess_game.board[i];
        if (chess_game.player_turn != piece.color)
        {
            continue;
        }
        std::vector<Move> new_moves;
        std::vector<Move> new_moves2;
        switch (piece.piece_type) 
        {
        case PieceType::Pawn:
            new_moves = piece.color == Color::White ? whitePawnMoves(chess_game.board, i) : blackPawnMoves(chess_game.board, i);
            break;
        case PieceType::Knight:
            new_moves = knightMoves(chess_game.board, i);
            break;
        case PieceType::Bishop:
            new_moves = bishopMoves(chess_game.board, i);
            break;
        case PieceType::Rook:
            new_moves = rookMoves(chess_game.board, i);
            break;
        case PieceType::Queen:
            new_moves = rookMoves(chess_game.board, i);
            new_moves2 = bishopMoves(chess_game.board, i);
            new_moves.insert(new_moves.end(), new_moves2.begin(), new_moves2.end());
            break;
        case PieceType::King:
            new_moves = kingMoves(chess_game.board, i);
            break;
        default:
            break;
        }
        pseudo_moves.insert(pseudo_moves.end(), new_moves.begin(), new_moves.end());
    }
    return pseudo_moves;
}

std::vector<Move> LegalMoves::generateLegalMoves(ChessGame chess_game)
{
    std::vector<Move> moves = generatePseudoLegalMoves(chess_game);

    // Add Castle Moves
    std::vector<Move> castle_moves = castleMoves(chess_game);
    
    return moves;
}