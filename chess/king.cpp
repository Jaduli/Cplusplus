/* king.cpp
 *
 * Contains the functions for a king piece in Chess project.
 *
 * Creator of the program
 * Name: Jade Pitkänen
 * E-Mail: jade.pitkanen@tuni.fi
 *
 * */

#include "king.hh"

King::King(ChessColor col): ChessPiece(col, KING, "king") {}

set<Coord> King::get_allowed_moves(const ChessBoard &board) const
{
    set<Coord> moves;
    auto [row, col] = get_position();
    int i = 0, j = 0;

    // Check the tiles surrounding the king
    for (i = -1; i <= 1; ++i) {
        for (j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            Coord new_pos = { row + i, col + j };
            shared_ptr<ChessPiece> piece = board.get_piece_at(new_pos);
            if (board.coord_in_bounds(new_pos) &&
                (piece == nullptr || piece->get_color() != get_color())) {
                moves.insert(new_pos);
            }
        }
    }
    return moves;
}
