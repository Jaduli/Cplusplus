/* bishop.cpp
 *
 * Contains the functions for a bishop piece in Chess project.
 *
 * Creator of the program
 * Name: Jade Pitkänen
 * E-Mail: jade.pitkanen@tuni.fi
 *
 * */

#include "bishop.hh"

Bishop::Bishop(ChessColor col): ChessPiece(col, BISHOP, "bishop") {}

set<Coord> Bishop::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> moves;

    auto [row, col] = get_position();

    int i = 0;

    // Check diagonal movements
    // Bottom-right
    for (i = 1; i < BOARD_SIZE; ++i) {
        Coord c = {row - i, col + i};
        if (!board.coord_in_bounds(c)) break; // Not in bounds

        auto piece = board.get_piece_at(c);
        if (!piece)
            moves.insert(c); // Empty spot
        else {
            if (piece->get_color() != get_color())
                moves.insert(c); // Can take
            break;
        }
    }

    // Bottom-left
    for (i = 1; i < BOARD_SIZE; ++i) {
        Coord c = {row - i, col - i};
        if (!board.coord_in_bounds(c)) break;

        auto piece = board.get_piece_at(c);
        if (!piece)
            moves.insert(c);
        else {
            if (piece->get_color() != get_color())
                moves.insert(c);
            break;
        }
    }

    // Top-right
    for (i = 1; i < BOARD_SIZE; ++i) {
        Coord c = {row + i, col + i};
        if (!board.coord_in_bounds(c)) break;

        auto piece = board.get_piece_at(c);
        if (!piece)
            moves.insert(c);
        else {
            if (piece->get_color() != get_color())
                moves.insert(c);
            break;
        }
    }

    // Top-left
    for (int i = 1; i < BOARD_SIZE; ++i) {
        Coord c = {row + i, col - i};
        if (!board.coord_in_bounds(c)) break;

        auto piece = board.get_piece_at(c);
        if (!piece)
            moves.insert(c);
        else {
            if (piece->get_color() != get_color())
                moves.insert(c);
            break;
        }
    }

    return moves;
}
