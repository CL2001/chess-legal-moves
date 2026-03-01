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
    castle = ["'.'", "'.'", "'.'", "'.'"]
    if board.has_kingside_castling_rights(chess.WHITE): castle[0] = "'K'"
    if board.has_queenside_castling_rights(chess.WHITE): castle[1] = "'Q'"
    if board.has_kingside_castling_rights(chess.BLACK): castle[2] = "'k'"
    if board.has_queenside_castling_rights(chess.BLACK): castle[3] = "'q'"

    # En passant target
    en_passant = board.ep_square if board.ep_square is not None else -1

    # Build output
    out = []
    out.append(f"ChessGame game; // {fen}")
    out.append(f"game.player_turn = {player_turn};")
    out.append("game.board = {")
    for r in range(8):
        row = board_pieces[r*8:(r+1)*8]
        out.append("    " + ", ".join(row) + ("," if r < 7 else ""))
    out.append("};")
    out.append(f"game.castle = {{{', '.join(castle)}}};")
    out.append(f"game.en_passant = {en_passant};")
    out.append(f"game.winner = Winner::Nil;")
    return "\n".join(out)


def fen_to_board_string(fen: str) -> str:
    board_part = fen.split()[0]
    ranks = board_part.split('/')

    result = []

    # FEN is rank 8 → 1, we want 1 → 8
    for rank in reversed(ranks):
        for c in rank:
            if c.isdigit():
                result.extend('.' * int(c))
            else:
                result.append(c)

    board = ''.join(result)
    assert len(board) == 64
    return board


def fen_to_uint_64(fen: str) -> str:
    board = chess.Board(fen)
    value = 0

    for square in chess.SQUARES:  # 0..63 (a1..h8)
        if board.piece_at(square) is not None:
            bit = 63 - square
            value |= (1 << bit)

    return f"0x{value:016x}ULL"



if __name__ == "__main__":
    #fen = "k1K5/1R6/8/8/8/8/8/8 b - - 1 1"
    #fen = "rnbqkbnr/ppppppp1/8/P6p/8/8/1PPPPPPP/RNBQKBNR b KQkq - 0 2"
    fen = "r1bB1rk1/6bn/1n4p1/1p1PPp1p/pPp1P1P1/7P/P2QN1B1/R3K2R b KQ b3 0 20"
    #fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    print("fen_to_board_string")
    print(fen_to_board_string(fen))
    print("fen to uint64")
    print(fen_to_uint_64(fen))
    print("fen_to_chessgame")
    print(fen_to_chessgame(fen))
    board = chess.Board(fen)
    #for move in board.legal_moves:
    #    print(move)
    #print("[legal moves, legal moves depth 2, ....]")
    #print(count_legal_moves(board, iterations=4))
