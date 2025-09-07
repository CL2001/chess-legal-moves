// legal_moves.cpp
#include "legal_moves.hpp"

std::vector<Move> castleMoves(ChessGame chess_game)
{
    std::vector<Move> moves;
    return moves;
}

std::vector<Move> enPassantMoves(ChessGame chess_game)
{
    std::vector<Move> moves;
    if (chess_game.player_turn == Color::White)
    {
        if (chess_game.board[chess_game.enPassant - 7] == Piece(Color::White, PieceType::Pawn))
        {
            moves.push_back(Move(chess_game.enPassant - 7, chess_game.enPassant));
        }
        if (chess_game.board[chess_game.enPassant - 9] == Piece(Color::White, PieceType::Pawn))
        {
            moves.push_back(Move(chess_game.enPassant - 7, chess_game.enPassant));
        }
    }
    if (chess_game.player_turn == Color::Black)
    {
        if (chess_game.board[chess_game.enPassant + 7] == Piece(Color::Black, PieceType::Pawn))
        {
            moves.push_back(Move(chess_game.enPassant + 7, chess_game.enPassant));
        }
        if (chess_game.board[chess_game.enPassant + 9] == Piece(Color::Black, PieceType::Pawn))
        {
            moves.push_back(Move(chess_game.enPassant + 7, chess_game.enPassant));
        }
    }
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
        moves.push_back(Move(index, index + 16));
    }

    // Move up
    if (board[index + 8].piece_type == PieceType::Nil)
    {
        moves.push_back(Move(index, index + 8));
    }

    // Diagonal left
    if (board[index + 7].color == Color::Black)
    {
        moves.push_back(Move(index, index + 7));
    }

    // Diagonal right
    if (board[index + 9].color == Color::Black)
    {
        moves.push_back(Move(index, index + 9));
    }

    // Promotion
    if (index >= 48 && index <= 55)
    {
        std::vector<Move> new_moves;
        for (auto move : moves)
        {
            moves.push_back(Move(move.from_square, move.to_square, Piece(Color::White, PieceType::Queen)));
            moves.push_back(Move(move.from_square, move.to_square, Piece(Color::White, PieceType::Knight)));
            moves.push_back(Move(move.from_square, move.to_square, Piece(Color::White, PieceType::Bishop)));
            moves.push_back(Move(move.from_square, move.to_square, Piece(Color::White, PieceType::Rook)));
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
        moves.push_back(Move(index, index - 16));
    }

    // Move up
    if (board[index - 8].piece_type == PieceType::Nil)
    {
        moves.push_back(Move(index, index - 8));
    }

    // Diagonal left
    if (board[index - 7].color == Color::White)
    {
        moves.push_back(Move(index, index - 7));
    }

    // Diagonal right
    if (board[index - 9].color == Color::White)
    {
        moves.push_back(Move(index, index - 9));
    }

    // Promotion
    if (index >= 8 && index <= 15)
    {
        std::vector<Move> new_moves;
        for (auto move : moves)
        {
            moves.push_back(Move(move.from_square, move.to_square, Piece(Color::Black, PieceType::Queen)));
            moves.push_back(Move(move.from_square, move.to_square, Piece(Color::Black, PieceType::Knight)));
            moves.push_back(Move(move.from_square, move.to_square, Piece(Color::Black, PieceType::Bishop)));
            moves.push_back(Move(move.from_square, move.to_square, Piece(Color::Black, PieceType::Rook)));
        }
        return new_moves;
    }
    return moves;
}

std::vector<Move> knightMoves(const Piece board[64], int index)
{
    std::vector<Move> moves;
    Color piece_color = board[index].color;

    int knight_moves_left[4] = {index - 17, index - 10, index + 6, index + 15}; // kight moves (not magic numbers)
    int knight_moves_right[4] = {index - 15, index - 6, index + 10, index + 17};
    for (int i = 0; i < 4; i++)
    {
        if (knight_moves_left[i] < 64 && knight_moves_left[i] > 0 && 
            index % 8 > knight_moves_left[i] % 8 && board[knight_moves_left[i]].color != piece_color)
        {
            moves.push_back(Move(index, knight_moves_left[i]));
        }
        if (knight_moves_right[i] < 64 && knight_moves_right[i] > 0 && 
            index % 8 < knight_moves_right[i] % 8 && board[knight_moves_right[i]].color != piece_color)
        {
            moves.push_back(Move(index, knight_moves_right[i]));
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
        if (board[bottom_left_index].color == Color::Nil)
        {
            moves.push_back(Move(index, bottom_left_index));
        }
        else if (board[bottom_left_index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move(index, bottom_left_index));
            break;
        }
        bottom_left_index -= 9;
    }

    // bottom right
    int bottom_right_index = index - 7;
    while (bottom_right_index % 8 != 0 && bottom_right_index >= 0)
    {
        if (board[bottom_right_index].color == Color::Nil)
        {
            moves.push_back(Move(index, bottom_right_index));
        }
        else if (board[bottom_right_index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move(index, bottom_right_index));
            break;
        }
        bottom_right_index -= 7;
    }

    // up left
    int up_left_index = index + 7;
    while (up_left_index % 8 != 7 && up_left_index < 64)
    {
        if (board[up_left_index].color == Color::Nil)
        {
            moves.push_back(Move(index, up_left_index));
        }
        else if (board[up_left_index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move(index, up_left_index));
            break;
        }
        up_left_index += 7;
    }

    // up right
    int up_right_index = index + 9;
    while (up_right_index % 8 != 0 && up_right_index < 64)
    {
        if (board[up_right_index].color == Color::Nil)
        {
            moves.push_back(Move(index, up_right_index));
        }
        else if (board[up_right_index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move(index, up_right_index));
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
        if (board[left_index].color == Color::Nil)
        {
            moves.push_back(Move(index, left_index));
        }
        else if (board[left_index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move(index, left_index));
            break;
        }
        left_index--;
    }

    // right
    int right_index = index + 1;
    while (right_index % 8 != 0)
    {
        if (board[right_index].color == Color::Nil)
        {
            moves.push_back(Move(index, right_index));
        }
        else if (board[right_index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move(index, right_index));
            break;
        }
        right_index++;
    }

    // bottom
    int bottom_index = index - 8;
    while (bottom_index >= 0)
    {
        if (board[bottom_index].color == Color::Nil)
        {
            moves.push_back(Move(index, bottom_index));
        }
        else if (board[bottom_index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move(index, bottom_index));
            break;
        }
        bottom_index -= 8;
    }

    // up
    int up_index = index + 8;
    while (up_index < 64)
    {
        if (board[up_index].color == Color::Nil)
        {
            moves.push_back(Move(index, up_index));
        }
        else if (board[up_index].color == piece_color)
        {
            break;
        }
        else
        {
            moves.push_back(Move(index, up_index));
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

    int king_moves_left[3] = {index - 9, index - 1, index + 7}; // king moves (not magic numbers)
    int king_moves_right[3] = {index - 7, index + 1, index + 9};
    int king_moves[2] = {index - 8, index + 8};
    for (int i = 0; i < 3; i++)
    {
        if (king_moves_left[i] < 64 && king_moves_left[i] > 0 && 
            index % 8 > king_moves_left[i] % 8 && board[king_moves_left[i]].color != piece_color)
        {
            moves.push_back(Move(index, king_moves_left[i]));
        }
        if (king_moves_right[i] < 64 && king_moves_right[i] > 0 && 
            index % 8 < king_moves_right[i] % 8 && board[king_moves_left[i]].color != piece_color)
        {
            moves.push_back(Move(index, king_moves_right[i]));
        }
        if (i < 3 && king_moves[i] < 64 && king_moves[i] > 0 && 
            board[king_moves[i]].color != piece_color)
        {
            moves.push_back(Move(index, king_moves[i]));
        }
    }
    return moves;
}

std::vector<Move> generatePseudoLegalMoves(ChessGame chess_game)
{
    std::vector<Move> pseudo_moves;

    // En passant
    if (chess_game.enPassant != -1)
    {
        pseudo_moves = enPassantMoves(chess_game);
    }
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