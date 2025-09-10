import chess

def count_legal_moves(board, iterations=4):
    from copy import deepcopy

    boards = [deepcopy(board)]
    move_counts = []

    for _ in range(iterations):
        next_boards = []
        for b in boards:
            for move in b.legal_moves:
                new_board = deepcopy(b)
                new_board.push(move)
                next_boards.append(new_board)
        move_counts.append(len(next_boards))
        boards = next_boards

    return move_counts


def piece_to_cpp(piece):
    if piece is None:
        return "Piece{Color::Nil, PieceType::Nil}"

    color = "Color::White" if piece.color == chess.WHITE else "Color::Black"
    type_map = {
        chess.PAWN: "PieceType::Pawn",
        chess.ROOK: "PieceType::Rook",
        chess.KNIGHT: "PieceType::Knight",
        chess.BISHOP: "PieceType::Bishop",
        chess.QUEEN: "PieceType::Queen",
        chess.KING: "PieceType::King",
    }
    return f"Piece{{{color}, {type_map[piece.piece_type]}}}"


def fen_to_chessgame(fen: str) -> str:
    board = chess.Board(fen)

    # Player turn
    player_turn = "Color::White" if board.turn == chess.WHITE else "Color::Black"

    # Board pieces (a1 = index 0 → h8 = index 63)
    board_pieces = []
    for square in chess.SQUARES:  # a1..h8
        piece = board.piece_at(square)
        board_pieces.append(piece_to_cpp(piece))

    # Castling rights
    castle = []
    if board.has_kingside_castling_rights(chess.WHITE): castle.append("'K'")
    if board.has_queenside_castling_rights(chess.WHITE): castle.append("'Q'")
    if board.has_kingside_castling_rights(chess.BLACK): castle.append("'k'")
    if board.has_queenside_castling_rights(chess.BLACK): castle.append("'q'")

    # En passant target
    en_passant = board.ep_square if board.ep_square is not None else -1

    # Build output
    out = []
    out.append("ChessGame game{")
    out.append(f"    .player_turn = {player_turn},")
    out.append("    .board = {")
    for r in range(8):
        row = board_pieces[r*8:(r+1)*8]
        out.append("        " + ", ".join(row) + ("," if r < 7 else ""))
    out.append("    },")
    out.append(f"    .castle = {{{', '.join(castle)}}},")
    out.append(f"    .enPassant = {en_passant}")
    out.append("};")
    return "\n".join(out)


if __name__ == "__main__":
    fen = "r1b1kbnr/ppp1p1pp/2P2p2/8/8/8/PPPB1PPP/RN2KBNR w KQ - 0 7"
    #fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    print(fen_to_chessgame(fen))
    board = chess.Board(fen)
    print("[legal moves, legal moves depth 2, ....]")
    print(count_legal_moves(board, iterations=4))
