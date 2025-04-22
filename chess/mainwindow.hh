/* mainwindow.hh
 *
 * Header class for the main window in Chess project.
 * Makes an interactive UI for a game of chess.
 *
 * Creator of the program
 * Name: Jade Pitkänen
 * E-Mail: jade.pitkanen@tuni.fi
 *
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <map>
#include <set>
#include "chess.hh"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Handles the clicks on the gameboard, e.g. piece choices
    // and movement.
    void handle_clicks(int row, int col);

    // Handles the reset button to reset the gameboard.
    void handle_reset();

    // Handles the quit button which closes the window.
    void handle_quit();

private:
    // Size constants
    const int TILE_SIZE = 64;
    const int BUTTON_WIDTH = TILE_SIZE;
    const int BUTTON_HEIGHT = BUTTON_WIDTH / 2;
    const int MARGIN = TILE_SIZE / 4;

    // Game which uses the chess class
    Chess game_;

    // Piece chosen to be moved after clicked
    std::shared_ptr<ChessPiece> piece_chosen_;

    // Tiles of the board consisting of push buttons
    std::map<Coord, QPushButton*> tiles_;

    // Button to reset the board
    QPushButton* reset_button_;

    // Button to quit the window
    QPushButton* quit_button_;

    // Info text to tell info on the game
    QLabel* info_text_;

    // Initializes the board with square buttons
    void init_board();

    // Initialized reset and quit buttons as well as the info label
    void init_buttons();

    // Draws the chess board with images
    void draw_board();

    // Victory function when king captured
    void victory();
};

#endif // MAINWINDOW_HH
