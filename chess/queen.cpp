/* queen.cpp
 *
 * Contains the functions for a queen piece in Chess project.
 *
 * Creator of the program
 * Name: Jade Pitkänen
 * E-Mail: jade.pitkanen@tuni.fi
 *
 * */

#include "queen.hh"

Queen::Queen(ChessColor col): ChessPiece(col, QUEEN, "queen") {}

set<Coord> Queen::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> moves;

    auto [row, col] = get_position();

    int i = 0;

    // Vertical & horizontal (same as rook)
    for (i = row + 1; i < BOARD_SIZE; ++i) {
        Coord c = {i, col};
        if (!board.coord_in_bounds(c)) break;

        auto piece = board.get_piece_at(c);
        if (!piece) {
            moves.insert(c);
        } else {
            if (piece->get_color() != get_color())
                moves.insert(c);
            break;
        }
    }

    for (i = row - 1; i >= 0; --i) {
        Coord c = {i, col};
        if (!board.coord_in_bounds(c)) break;

        auto piece = board.get_piece_at(c);
        if (!piece) {
            moves.insert(c);
        } else {
            if (piece->get_color() != get_color())
                moves.insert(c);
            break;
        }
    }

    for (i = col + 1; i < BOARD_SIZE; ++i) {
        Coord c = {row, i};
        if (!board.coord_in_bounds(c)) break;

        auto piece = board.get_piece_at(c);
        if (!piece) {
            moves.insert(c);
        } else {
            if (piece->get_color() != get_color())
                moves.insert(c);
            break;
        }
    }

    for (i = col - 1; i < BOARD_SIZE; --i) {
        Coord c = {row, i};
        if (!board.coord_in_bounds(c)) break;

        auto piece = board.get_piece_at(c);
        if (!piece) {
            moves.insert(c);
        } else {
            if (piece->get_color() != get_color())
                moves.insert(c);
            break;
        }
    }

    // Diagonals (same as bishop)
    for (int i = 1; i < BOARD_SIZE; ++i) {
        Coord c{row - i, col - i};
        if (!board.coord_in_bounds(c)) break;
        auto piece = board.get_piece_at(c);
        if (!piece) moves.insert(c);
        else {
            if (piece->get_color() != get_color()) moves.insert(c);
            break;
        }
    }

    for (int i = 1; i < BOARD_SIZE; ++i) {
        Coord c{row - i, col + i};
        if (!board.coord_in_bounds(c)) break;
        auto piece = board.get_piece_at(c);
        if (!piece) moves.insert(c);
        else {
            if (piece->get_color() != get_color()) moves.insert(c);
            break;
        }
    }

    for (int i = 1; i < BOARD_SIZE; ++i) {
        Coord c{row + i, col - i};
        if (!board.coord_in_bounds(c)) break;
        auto piece = board.get_piece_at(c);
        if (!piece) moves.insert(c);
        else {
            if (piece->get_color() != get_color()) moves.insert(c);
            break;
        }
    }

    for (int i = 1; i < BOARD_SIZE; ++i) {
        Coord c{row + i, col + i};
        if (!board.coord_in_bounds(c)) break;
        auto piece = board.get_piece_at(c);
        if (!piece) moves.insert(c);
        else {
            if (piece->get_color() != get_color()) moves.insert(c);
            break;
        }
    }

    return moves;
}
