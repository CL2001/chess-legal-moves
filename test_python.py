import chess

def count_legal_moves(board, iterations=4):
    from copy import deepcopy

    # Start with the initial board
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




def fen_to_chessgame(fen: str) -> str:
    board = chess.Board(fen)

    # Player turn
    player_turn = "Color::White" if board.turn == chess.WHITE else "Color::Black"

    # Board pieces (row 8 → row 1, left to right)
    board_chars = []
    for square in chess.SQUARES:
        piece = board.piece_at(square)
        board_chars.append(piece.symbol().upper() if piece and piece.color == chess.WHITE
                           else piece.symbol() if piece else ' ')

    # Castling rights
    castle = []
    if board.has_kingside_castling_rights(chess.WHITE): castle.append('K')
    if board.has_queenside_castling_rights(chess.WHITE): castle.append('Q')
    if board.has_kingside_castling_rights(chess.BLACK): castle.append('k')
    if board.has_queenside_castling_rights(chess.BLACK): castle.append('q')

    # En passant target
    en_passant = board.ep_square if board.ep_square is not None else -1

    # Build output
    out = []
    out.append("ChessGame game{")
    out.append(f"    .player_turn = {player_turn},")
    out.append("    .board = {")
    out.append("        " + ", ".join(f"'{c}'" for c in board_chars[:8]) + ",")
    for r in range(1, 8):
        row = board_chars[r*8:(r+1)*8]
        out.append("        " + ", ".join(f"'{c}'" for c in row) + ("," if r < 7 else ""))
    out.append("    },")
    out.append(f"    .castle = {{{', '.join(f'\'{c}\'' for c in castle)}}},")
    out.append(f"    .enPassant = {en_passant}")
    out.append("};")
    return "\n".join(out)


if __name__ == "__main__":
    fen = "r1bkQbnr/ppp1p1pp/2P2p2/8/8/8/PPPB1PPP/RN2KBNR b KQ - 3 6"
    print(fen_to_chessgame(fen))
    board = chess.Board(fen)  # starting position
    print("[legal moves, legal moves depth 2, ....]")
    print(count_legal_moves(board, iterations=4))
