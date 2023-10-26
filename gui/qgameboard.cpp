#include "gui/qgameboard.h"
#include "core/board.h"
#include "core/game.h"
#include "gui/qtile.h"
#include "core/tile.h"
#include "gui/qresetbutton.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QString>

#include <QDebug>
#include "qgameboard.h"

QGameBoard::~QGameBoard()
{
    delete game;
}

QGameBoard::QGameBoard(QWidget *parent) : QWidget(parent)
{
    // set default size
    resize(650, 450);

    // create the main layout
    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    labelLayout = new QHBoxLayout();

    // will be created in drawBoard()
    boardLayout = NULL;

    // create the game and register as observer
    game = new Game(4);
    game->registerObserver(this);

    // create the gui board and draw it
    gui_board.resize(game->getGameBoard()->getDimension());
    for (int i = 0; i < game->getGameBoard()->getDimension(); ++i)
        gui_board[i].resize(game->getGameBoard()->getDimension());
    for (int i = 0; i < game->getGameBoard()->getDimension(); ++i)
        for (int j = 0; j < game->getGameBoard()->getDimension(); ++j)
            gui_board[i][j] = NULL;
    drawBoard();

    // create the score widget and add it to the board
    score = new QLabel(QString("SCORE: %1").arg(game->getScore()));
    score->setStyleSheet("QLabel { color: rgb(235,224,214); font: 16pt; }");
    score->setFixedHeight(50);
    labelLayout->insertWidget(1, score, 0, Qt::AlignRight);

    // create the score message widget and add it to the board
    scoreHistory = new Score();
    scoreHistory->readFromJson();
    scoreMessage = new QLabel(QString("MAXSCORE: %1 TIME: %2").arg(scoreHistory->getValues()->maxScore).arg(scoreHistory->getValues()->time));
    scoreMessage->setStyleSheet("QLabel { color: rgb(235,224,214); font: 16pt; }");
    scoreMessage->setFixedHeight(50);
    labelLayout->insertWidget(0, scoreMessage, 0, Qt::AlignLeft);

    mainLayout->insertLayout(1, labelLayout);

    // style sheet of the board
    setStyleSheet("QGameBoard { background-color: rgb(187,173,160) }");

    connect(gameOverWindow.getResetBtn(), SIGNAL(clicked()), this, SLOT(resetGame()));
}

void QGameBoard::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        game->move(UP);
        break;
    case Qt::Key_Left:
        game->move(LEFT);
        break;
    case Qt::Key_Right:
        game->move(RIGHT);
        break;
    case Qt::Key_Down:
        game->move(DOWN);
        break;
    }
}

void QGameBoard::notify()
{
    if (game->isGameOver())
    {
        gameOverWindow.show();
        scoreHistory->writeToJson(game->getScore());
    }
    if (game->won())
    {
        score->setText(QString("You hit 2048, congratulations! Keep playing to increase your score.\t\t SCORE: %1").arg(game->getScore()));
        scoreHistory->writeToJson(game->getScore());
    }
    else
    {
        score->setText(QString("SCORE: %1").arg(game->getScore()));
    }

    drawBoard();
}

void QGameBoard::drawBoard()
{
    delete boardLayout;
    boardLayout = new QGridLayout();
    for (int i = 0; i < game->getGameBoard()->getDimension(); ++i)
    {
        for (int j = 0; j < game->getGameBoard()->getDimension(); ++j)
        {
            delete gui_board[i][j];
            gui_board[i][j] = new QTile(game->getGameBoard()->getTile(i, j));
            boardLayout->addWidget(gui_board[i][j], i, j);
            gui_board[i][j]->draw();
        }
    }
    mainLayout->insertLayout(0, boardLayout);
}

void QGameBoard::showScoreHistory()
{
    scoreHistory->readFromJson(); // 得到scoreInfo
    qDebug() << scoreHistory->getValues()->maxScore << scoreHistory->getValues()->time;
    scoreMessage->setText(QString("MaxScore: %1 Time: %2").arg(scoreHistory->getValues()->maxScore).arg(scoreHistory->getValues()->time));
}
void QGameBoard::resetGame()
{
    showScoreHistory();
    game->restart();
    drawBoard();
    score->setText(QString("SCORE: %1").arg(game->getScore()));
    gameOverWindow.hide();
}
