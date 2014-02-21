#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsolitairecard.cpp"
#include "qcardlist.cpp"
#include "tdalista.cpp"
#include "noded.cpp"
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Slyther's QSolitaire");
    this->setWindowIcon(QIcon(":/icon.png"));
    this->setFixedSize(800, 535);
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    startGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    char types[4] = {'C', 'D', 'H', 'S'};
    char numbers[13] = {'K', 'Q', 'J', '0', '9', '8', '7', '6', '5', '4', '3', '2', 'A'};
    QCardList* MainDeck = new QCardList('M', QPoint(36, 19), ui->centralWidget);
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            MainDeck->cardList->add(new QSolitaireCard(types[i], numbers[j], MainDeck->offset, ui->centralWidget));
        }
    }
    MainDeck->raise();
    QCardList* OffDeck = new QCardList('O', QPoint(145, 19), ui->centralWidget);
    MainDeck->relations->add(OffDeck);
    char DeckTypes[10] = {'M', 'O', 'A', '1', '2', '3', '4', '5', '6', '7'};
    int var = 361;
    Decks.add(MainDeck);
    Decks.add(OffDeck);
    for(int i = 0; i < 4; i++){
        Decks.add(new QCardList(DeckTypes[2], QPoint(var, 19), ui->centralWidget));
        var += 108;
    }
    var = 37;
    for(int i = 3; i < 10; i++){
        Decks.add(new QCardList(DeckTypes[i], QPoint(var, 145), ui->centralWidget));
        var += 108;
    }
    for(int i = 1; i < 13; i++){
        for(int j = 0; j < 13; j++){
            if(i == j)
                continue;
            if(i <= 5 && j == 0)
                continue;
            Decks.get(i)->relations->add(Decks.get(j));
        }
    }
    for(int i = 6; i < 13; i++){
        Decks.get(i)->populate();
        Decks.get(i)->updateList();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::RightButton ){
        QMouseEvent genericEvent(QEvent::MouseButtonDblClick, QPoint(0, 0), Qt::LeftButton, Qt::LeftButton, 0);
        for(int i = 0; i < Decks.size(); i++){
            if(Decks.get(i)->type == 'M' || Decks.get(i)->type == 'A')
                continue;
            int tmp = Decks.get(i)->cardList->size();
            if(tmp > 0)
                Decks.get(i)->cardList->end()->mouseDoubleClickEvent(&genericEvent);
            if(Decks.get(i)->cardList->size() < tmp){
                if(i == 0)
                    i--;
                else
                    i = 0;
            }
        }
    }
}

//WIP, no usar F2/New Game.
void MainWindow::on_actionNew_Game_triggered()
{
    for(int i = Decks.size()-1; i >= 0; i--){
        for(int j = Decks.get(i)->cardList->size()-1; j >= 0; j-- ){
            QSolitaireCard* tmp = Decks.get(i)->cardList->get(j);
            Decks.get(i)->cardList->remove(j);
            delete tmp;
        }
        QCardList* tmp2 = Decks.get(i);
        Decks.remove(i);
        delete tmp2;
    }
    startGame();
}
