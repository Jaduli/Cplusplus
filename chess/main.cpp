/* Chess
 *
 * Desctiption:
 * A simple game of chess. Choose a piece to move and move it according
 * to the rules of chess. Valid places to move will be marked with a red
 * border. Win by taking the opponent's king. Game can be restarted with
 * the reset button.
 *
 * Creator of the program
 * Name: Jade Pitkänen
 * E-Mail: jade.pitkanen@tuni.fi
 *
 * */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
