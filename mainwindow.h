#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tdalista.h"
#include "qsolitairecard.h"
#include "qcardlist.h"
#include <cstdlib>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TDALISTA<QCardList*> Decks;
    void startGame();
    void shuffle(QCardList* toShuffle);
    void checkGameStatus();
private:
    Ui::MainWindow *ui;
protected:
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_actionNew_Game_triggered();
};

#endif // MAINWINDOW_H
