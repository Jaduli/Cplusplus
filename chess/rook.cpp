/* rook.cpp
 *
 * Contains the functions for a rook piece in Chess project.
 *
 * Creator of the program
 * Name: Jade Pitkänen
 * E-Mail: jade.pitkanen@tuni.fi
 *
 * */

#include "rook.hh"

Rook::Rook(ChessColor col): ChessPiece(col, ROOK, "rook") {}

set<Coord> Rook::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> moves;

    auto [row, col] = get_position();

    int i = 0;

    // Check vertical movement
    for (i = row + 1; i < BOARD_SIZE; ++i) {
        Coord c = {i, col};
        if (!board.coord_in_bounds(c)) break; // Not in bounds

        auto piece = board.get_piece_at(c);
        if (!piece) { // Empty spot
            moves.insert(c);
        } else {
            if (piece->get_color() != get_color())
                moves.insert(c); // Can take
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

    // Check horizontal movement
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

    return moves;
}
