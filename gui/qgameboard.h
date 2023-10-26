#ifndef QGAMEBOARD_H
#define QGAMEBOARD_H

#include "core/observer.h"
#include "qgameoverwindow.h"
#include "core/score.h"
#include <QVector>
#include <QWidget>

class QResetButton;
class Game;
class QKeyEvent;
class QTile;
class QGridLayout;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;

class QGameBoard : public QWidget, public Observer
{
    Q_OBJECT
public:
    explicit QGameBoard(QWidget *parent = 0);
    ~QGameBoard();

    void notify();

private:
    Game *game;
    Score *scoreHistory;
    // gui representation of board
    QVector<QVector<QTile *>> gui_board;
    // main layout
    QVBoxLayout *mainLayout;
    // grid layout of board
    QGridLayout *boardLayout;
    // score widget
    QLabel *score;
    // score message widget
    QLabel *scoreMessage;
    // label layout
    QHBoxLayout *labelLayout;
    // game over widget
    QGameOverWindow gameOverWindow;
    // winner widget
    QLabel *youwin;

    void drawBoard();
    void showScoreHistory();
protected:
    void keyPressEvent(QKeyEvent *event);

signals:

public slots:
    void resetGame();
};

#endif // QGAMEBOARD_H
