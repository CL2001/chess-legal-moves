#include <iostream>
#include <functional>
#include "chess.hpp"
#include "structs.hpp"

std::vector<int> legalMovesN(const ChessGame& game, int depth) {
    std::vector<int> totals(depth, 0);

    std::function<void(const ChessGame&, int)> dfs = [&](const ChessGame& g, int d) {
        if (d >= depth) return;

        std::vector<Move> moves = Chess::generateLegalMoves(g);
        totals[d] += moves.size();

        for (const auto& move : moves) {
            dfs(move.chess_game, d + 1);
        }
    };

    dfs(game, 0);
    return totals;
}


void mainTest() 
{
    std::cout << "Hello World from main" << std::endl;


    // Change this

    ChessGame game{
        .player_turn = Color::Black,
        .board = {
            Piece{Color::White, PieceType::Rook}, Piece{Color::White, PieceType::Knight}, Piece{Color::White, PieceType::Bishop}, Piece{Color::White, PieceType::Queen}, Piece{Color::White, PieceType::King}, Piece{Color::White, PieceType::Bishop}, Piece{Color::White, PieceType::Knight}, Piece{Color::White, PieceType::Rook},
            Piece{Color::Nil, PieceType::Nil}, Piece{Color::White, PieceType::Pawn}, Piece{Color::White, PieceType::Pawn}, Piece{Color::White, PieceType::Pawn}, Piece{Color::White, PieceType::Pawn}, Piece{Color::White, PieceType::Pawn}, Piece{Color::White, PieceType::Pawn}, Piece{Color::White, PieceType::Pawn},
            Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::White, PieceType::Pawn}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Black, PieceType::Pawn},
            Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::Black, PieceType::Pawn}, Piece{Color::Black, PieceType::Pawn}, Piece{Color::Black, PieceType::Pawn}, Piece{Color::Black, PieceType::Pawn}, Piece{Color::Black, PieceType::Pawn}, Piece{Color::Black, PieceType::Pawn}, Piece{Color::Black, PieceType::Pawn}, Piece{Color::Nil, PieceType::Nil},
            Piece{Color::Black, PieceType::Rook}, Piece{Color::Black, PieceType::Knight}, Piece{Color::Black, PieceType::Bishop}, Piece{Color::Black, PieceType::Queen}, Piece{Color::Black, PieceType::King}, Piece{Color::Black, PieceType::Bishop}, Piece{Color::Black, PieceType::Knight}, Piece{Color::Black, PieceType::Rook}
        },
        .castle = {'K', 'Q', 'k', 'q'},
        .en_passant = -1,
        .winner = Winner::Nil
    };



    // Iteration 1
    std::vector<Move> moves = Chess::generateLegalMoves(game);

    for (auto move : moves)
    {
        std::cout << "From " << move.from_square << " to " << move.to_square << std::endl;
    }

    // Winner
    game.winner = Chess::calculateEndGame(game, moves);
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
}


char piece_to_char(const Piece& piece) {
    if (piece.piece_type == PieceType::Nil)
        return '.';

    char c;
    switch (piece.piece_type) {
        case PieceType::Pawn:   c = 'P'; break;
        case PieceType::Rook:   c = 'R'; break;
        case PieceType::Knight: c = 'N'; break;
        case PieceType::Bishop: c = 'B'; break;
        case PieceType::Queen:  c = 'Q'; break;
        case PieceType::King:   c = 'K'; break;
        default: return '.';
    }

    return (piece.color == Color::Black) ? std::tolower(c) : c;
}


void print_board(const ChessGame& game) {
    std::cout << "\n  +------------------------+\n";
    for (int rank = 7; rank >= 0; --rank) {
        std::cout << rank + 1 << " | ";
        for (int file = 0; file < 8; ++file) {
            int idx = rank * 8 + file;
            std::cout << piece_to_char(game.board[idx]) << ' ';
        }
        std::cout << "|\n";
    }
    std::cout << "  +------------------------+\n";
    std::cout << "    a b c d e f g h\n\n";

    std::cout << "Castling {" << game.castle[0] << ", " << game.castle[1] << ", " << game.castle[2] << ", " << game.castle[3] << "}" << "\n";
    std::cout << "En Passant {" << game.en_passant << "}\n";
    std::cout << "Turn: " << (game.player_turn == Color::White ? "White" : "Black") << std::endl;
}


int square_from_notation(const std::string& notation) {
    if (notation.size() != 2) return -1;
    char file = std::tolower(notation[0]);
    char rank = notation[1];
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') return -1;
    int file_idx = file - 'a';
    int rank_idx = rank - '1';
    return rank_idx * 8 + file_idx;
}


void mainLoop(Color player_color)
{
    ChessGame game;
    print_board(game);
    while (true)
    {
        std::vector<Move> moves = Chess::generateLegalMoves(game);
        if (Chess::calculateEndGame(game, moves) != Winner::Nil)
        {
            std::cout << "Game end" << std::endl;
            break;
        }

        if (player_color == Color::Nil || player_color == game.player_turn)
        {
            std::string input;
            std::cout << ((game.player_turn == Color::White) ? "White" : "Black") << " to move: ";
            std::cin >> input;

            if (input == "exit") {
                std::cout << "Exiting game...\n";
                break;
            }

            if (input.size() != 4) {
                std::cout << "Invalid input format. Use a1a2 format.\n";
                continue;
            }

            int from = square_from_notation(input.substr(0, 2));
            int to = square_from_notation(input.substr(2, 2));

            if (from == -1 || to == -1) {
                std::cout << "Invalid square coordinates.\n";
                continue;
            }

            bool found = false;
            bool promotion = false;
            for (const auto& move : moves)
            {
                if (move.from_square == from && move.to_square == to && move.promotion != Piece())
                {
                    promotion = true;
                    break;
                }
                if (move.from_square == from && move.to_square == to && move.promotion == Piece())
                {
                    game = move.chess_game;
                    found = true;
                    break;
                }
            }

            if (promotion)
            {
                Piece promotion_piece = Piece();
                while(true)
                {
                    std::string input;
                    std::cout << "Choose promotion (q, r, b, n): ";
                    std::cin >> input;

                    if (input.size() != 1) {
                        std::cout << "Invalid input format. Use a1a2 format.\n";
                        continue;
                    }
                    char choice = std::tolower(input[0]);
                    switch (choice)
                    {
                    case 'q':
                        promotion_piece = Piece(game.player_turn, PieceType::Queen);
                        break;
                    case 'r':
                        promotion_piece = Piece(game.player_turn, PieceType::Rook);
                        break;
                    case 'b':
                        promotion_piece = Piece(game.player_turn, PieceType::Bishop);
                        break;
                    case 'n':
                        promotion_piece = Piece(game.player_turn, PieceType::Knight);
                        break;
                    default:
                        std::cout << "Invalid choice. Try again.\n";
                        continue;
                    }
                    break;
                }
                for (const auto& move : moves)
                {
                    if (move.from_square == from && move.to_square == to && move.promotion == promotion_piece)
                    {
                        game = move.chess_game;
                        found = true;
                        break;
                    }
                }
            }

            if (!found) {
                std::cout << "Illegal move. Try again.\n";
            }    
        } 
        else 
        {
            // Chessbot
        }
        print_board(game);
    }
}


int main()
{
    //mainTest();
    Color player_color = Color::Nil; // Nil for pvp, color for bots
    mainLoop(player_color);
    return 0;
}