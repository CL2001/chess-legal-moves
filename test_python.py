import chess
import chess.pgn
import io
import time

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


def pgn_to_cpp_vector(pgn_string: str, include_initial=True) -> str:
    pgn_io = io.StringIO(pgn_string)
    game = chess.pgn.read_game(pgn_io)

    board = game.board()

    positions = []

    # Include starting position if desired
    if include_initial:
        positions.append(fen_to_chessgame(board.fen()))

    # Play moves one by one
    for move in game.mainline_moves():
        board.push(move)
        positions.append(fen_to_chessgame(board.fen()))

    # Build vector output
    out = []
    out.append("std::vector<ChessGame> game_positions = {")
    for i, pos in enumerate(positions):
        out.append("([]{")
        out.append(pos)
        out.append("return game;")
        out.append("}())" + ("," if i < len(positions) - 1 else ""))
    out.append("};")

    return "\n".join(out)


def pgn_to_fen_vector(pgn_string: str, include_initial=True) -> str:
    pgn_io = io.StringIO(pgn_string)
    game = chess.pgn.read_game(pgn_io)

    board = game.board()
    fens = []

    # Include starting position if desired
    if include_initial:
        fens.append(board.fen())

    # Play moves one by one
    for move in game.mainline_moves():
        board.push(move)
        fens.append(board.fen())

    # Build C++ vector<string>
    out = []
    out.append("std::vector<std::string> fen_positions = {")
    for i, fen in enumerate(fens):
        escaped = fen.replace("\\", "\\\\").replace('"', '\\"')
        out.append(f'    "{escaped}"' + ("," if i < len(fens) - 1 else ""))
    out.append("};")

    return "\n".join(out)


def pgn_to_check_vector(pgn_string: str, include_initial=True) -> str:
    pgn_io = io.StringIO(pgn_string)
    game = chess.pgn.read_game(pgn_io)

    board = game.board()

    checks = []

    # Include starting position if desired
    if include_initial:
        checks.append(board.is_check())

    # Play moves one by one
    for move in game.mainline_moves():
        board.push(move)
        checks.append(board.is_check())

    # Build C++ vector<bool>
    out = []
    out.append("std::vector<bool> position_is_check = {")
    for i, val in enumerate(checks):
        cpp_bool = "true" if val else "false"
        out.append("    " + cpp_bool + ("," if i < len(checks) - 1 else ""))
    out.append("};")

    return "\n".join(out)


def pgn_to_fen_check_pairs(pgn_string: str, include_initial=True) -> str:
    pgn_io = io.StringIO(pgn_string)
    game = chess.pgn.read_game(pgn_io)

    board = game.board()
    pairs = []

    # Include starting position if desired
    if include_initial:
        pairs.append((board.fen(), board.is_check()))

    # Play moves one by one
    for move in game.mainline_moves():
        board.push(move)
        pairs.append((board.fen(), board.is_check()))

    # Build C++ vector<pair<string,bool>>
    out = []
    out.append("std::vector<std::pair<std::string, bool>> fen_check_positions = {")
    for i, (fen, is_check) in enumerate(pairs):
        escaped = fen.replace("\\", "\\\\").replace('"', '\\"')
        cpp_bool = "true" if is_check else "false"
        out.append(f'    std::make_pair("{escaped}", {cpp_bool})' + ("," if i < len(pairs) - 1 else ""))
    out.append("};")

    return "\n".join(out)


def pgn_to_all_fens(pgn_file_path: str, start_game: int = 1, end_game: int = None, delay: float = 0.0) -> list[str]:
    """
    Reads a PGN file and returns a list of FEN strings for every position of games in the range [start_game, end_game].

    Args:
        pgn_file_path (str): Path to the PGN file.
        start_game (int): 1-based index of the first game to include.
        end_game (int): 1-based index of the last game to include (inclusive). If None, goes to end of file.
        delay (float): Optional delay in seconds between processing positions (useful for testing).

    Returns:
        List[str]: List of FEN strings for every position in the specified games.
    """
    all_fens = []
    with open(pgn_file_path, "r", encoding="utf-8") as pgn:
        game_number = 1
        while True:
            game = chess.pgn.read_game(pgn)
            if game is None:
                break  # No more games

            if game_number >= start_game and (end_game is None or game_number <= end_game):
                board = game.board()
                # Include starting position
                all_fens.append(board.fen())

                # Push moves and record FEN after each move
                for move in game.mainline_moves():
                    board.push(move)
                    all_fens.append(board.fen())

                    if delay > 0:
                        time.sleep(delay)

            if end_game is not None and game_number >= end_game:
                break

            game_number += 1

    return all_fens


def fens_to_check_pairs(fens: list[str], only_checks: bool = False) -> str:
    """
    Converts a list of FENs into a C++ vector of pairs (FEN, is_check).

    Args:
        fens (list[str]): List of FEN strings.
        only_checks (bool): If True, include only positions where the side to move is in check.

    Returns:
        str: C++ code for std::vector<std::pair<std::string,bool>>.
    """
    pairs = []

    for fen in fens:
        board = chess.Board(fen)
        is_check = board.is_check()
        if only_checks and not is_check:
            continue
        pairs.append((fen, is_check))

    # Build C++ vector<pair<string,bool>>
    out = []
    out.append("std::vector<std::pair<std::string, bool>> fen_check_positions = {")
    for i, (fen, is_check) in enumerate(pairs):
        escaped = fen.replace("\\", "\\\\").replace('"', '\\"')
        cpp_bool = "true" if is_check else "false"
        out.append(f'    std::make_pair("{escaped}", {cpp_bool})' + ("," if i < len(pairs) - 1 else ""))
    out.append("};")

    return "\n".join(out)


if __name__ == "__main__":
    """
    fen = "rnbq1bnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQ1BNR w KQkq - 0 1"
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
    """


    fens_list = pgn_to_all_fens("games.pgn", start_game=1, end_game=500)


    # Use the list of FENs we already generated
    fen_check_output = fens_to_check_pairs(fens_list, only_checks=True)

    with open("fen_check_positions.hpp", "w", encoding="utf-8") as f:
        f.write(fen_check_output)  # write all positions
        # f.write(fen_check_only_output)  # optional: write only checks

    print("C++ header written to fen_check_positions.hpp")
