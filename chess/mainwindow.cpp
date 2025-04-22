/* mainwindow.cpp
 *
 * Functions for the main window UI in Chess project.
 *
 * Creator of the program
 * Name: Jade Pitkänen
 * E-Mail: jade.pitkanen@tuni.fi
 *
 * */

#include "mainwindow.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      piece_chosen_(nullptr),
      reset_button_(new QPushButton(this)),
      quit_button_(new QPushButton(this)),
      info_text_(new QLabel(this))
{
    this->resize(8*TILE_SIZE, 9*TILE_SIZE);
    game_.start_game();
    init_board();
    init_buttons();
    draw_board();
}

MainWindow::~MainWindow() {

}

void MainWindow::handle_clicks(int row, int col) {
    ChessBoard board = game_.get_board();
    ChessColor in_turn = game_.get_current_turn();

    if (!piece_chosen_) {
        // If no piece chosen, valid choices are tiles with a pieces
        // from in-turn color that can be moved
        auto piece = board.get_piece_at(row, col);

        if (!piece || (piece->get_color() != in_turn)) {
            return;
        }

        set<Coord> moves = piece->get_allowed_moves(board);

        if (moves.empty()) {
            if (in_turn == WHITE) {
                info_text_->setText("Cannot move piece. White's turn.");
            }
            else {
                info_text_->setText("Cannot move piece. Black's turn.");
            }
            return;
        }

        for (Coord c : moves) {
            // Mark allowed move locations with a red border
            tiles_.at(c)->setStyleSheet("background-color: red;");
        }
        piece_chosen_ = piece;

        info_text_->setText("Choose where to move the piece.");
    }
    else {
        // If a piece has been chosen, valid clicks are locations that
        // the piece can move to.
        if (!(game_.make_move(piece_chosen_, {row, col}))) {
            return;
        }

        // Draw board with new move
        draw_board();

        if (game_.get_game_state() != IN_PROGRESS) {
            victory();
            return;
        }

        if (in_turn == WHITE) {
            info_text_->setText("Piece moved. Black's turn.");
        }
        else {
            info_text_->setText("Piece moved. White's turn.");
        }

        piece_chosen_ = nullptr;
    }
}

void MainWindow::handle_reset() {
    // Reset board
    game_.start_game();

    piece_chosen_ = nullptr;
    info_text_->setText("Board reset. White starts.");
    draw_board();
}

void MainWindow::handle_quit() {
    this->close();
}

void MainWindow::init_board() {
    int x = 0, y = 0;

    for (y = 0; y < BOARD_SIZE; ++y) {
        for (x = 0; x < BOARD_SIZE; ++x) {
            // Create buttons for the board
            QPushButton* new_tile = new QPushButton(this);
            new_tile->setGeometry(x * TILE_SIZE, y * TILE_SIZE,
                                  TILE_SIZE, TILE_SIZE);

            // Connect the button to slot along with its position
            connect(new_tile, &QPushButton::clicked, this, [=]() {
                handle_clicks(y, x);
            });

            tiles_.insert({{y,x}, new_tile});
        }
    }
}

void MainWindow::init_buttons() {
    // Initialize reset button
    reset_button_->setGeometry(8*TILE_SIZE-2*BUTTON_WIDTH-2*MARGIN,
                               8*TILE_SIZE+MARGIN,
                               BUTTON_WIDTH, BUTTON_HEIGHT);
    connect(reset_button_, &QPushButton::clicked,
            this, &MainWindow::handle_reset);
    reset_button_->setText("Reset");

    // Initialize quit button
    quit_button_->setGeometry(8*TILE_SIZE-BUTTON_WIDTH-MARGIN,
                              8*TILE_SIZE+MARGIN,
                              BUTTON_WIDTH, BUTTON_HEIGHT);
    quit_button_->setText("Quit");
    connect(quit_button_, &QPushButton::clicked,
            this, &MainWindow::handle_quit);

    // Initialize info text
    info_text_->setGeometry(MARGIN, 8*TILE_SIZE+MARGIN,
                            8*TILE_SIZE-2*BUTTON_WIDTH-3*MARGIN,
                            BUTTON_HEIGHT);
    info_text_->setText("White starts. Click on a piece to be moved.");
}

void MainWindow::draw_board() {
    int x = 0, y = 0;

    std::string image_name;
    ChessBoard board = game_.get_board();

    for (y = 0; y < BOARD_SIZE; ++y) {
        for (x = 0; x < BOARD_SIZE; ++x) {
            auto piece = board.get_piece_at(y,x);
            auto tile = tiles_.at({y,x});

            // Make sure tiles are enabled
            tile->setEnabled(true);

            image_name = ":/pieces/";
            if (piece == nullptr) {
                // Empty spots are marked with black and white squares
                // in a repeating pattern
                if ((x + y) % 2 == 0) {
                    image_name += "empty-bl.png";
                }
                else {
                    image_name += "empty-wt.png";
                }
            }
            else {
                // Add color to filename
                if (piece->get_color() == WHITE) {
                    image_name += "wt-";
                }
                else {
                    image_name += "bl-";
                }
                // Add piece name to filename
                image_name += piece->get_name();
                image_name += "-on-";

                // Add board tile color to filename
                if ((x + y) % 2 == 0) {
                    image_name += "bl.png";
                }
                else {
                    image_name += "wt.png";
                }
            }
            QPixmap image(QString::fromStdString(image_name));

            // Make sure border color is white & set correct image while
            // leaving space for border color
            tile->setStyleSheet("background-color: white;");
            tile->setIcon(image);
            tile->setIconSize(image.rect().size()/(2.2));
        }
    }
}

void MainWindow::victory() {
    int x = 0, y = 0;

    for (y = 0; y < BOARD_SIZE; ++y) {
        for (x = 0; x < BOARD_SIZE; ++x) {
            // Deactivate the tiles
            tiles_.at({y,x})->setEnabled(false);
        }
    }
    if (game_.get_game_state() == WHITE_WIN) {
        info_text_->setText("White wins! Reset board to play again.");
    }
    else {
        info_text_->setText("Black wins! Reset board to play again.");
    }
}
