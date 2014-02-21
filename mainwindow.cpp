#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsolitairecard.cpp"
#include "qcardlist.cpp"
#include "tdalista.cpp"
#include "noded.cpp"
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QLayout>
#include <time.h>
#include <QMessageBox>

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
    shuffle(MainDeck);
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

void MainWindow::on_actionNew_Game_triggered()
{
    for(int i = 1; i < Decks.size(); i++){
        for(int j = Decks.get(i)->cardList->size()-1; j >= 0; j--){
            Decks.get(i)->cardList->end()->offset = Decks.get(0)->offset;
            Decks.get(i)->cardList->end()->move(Decks.get(i)->cardList->get(j)->offset);
            Decks.get(i)->cardList->end()->raise();
            if(!Decks.get(i)->cardList->end()->islocked)
                Decks.get(i)->cardList->end()->flip();
            Decks.get(0)->cardList->add(Decks.get(i)->cardList->end());
            Decks.get(i)->cardList->remove(j);
        }
        Decks.get(i)->updateList();
        for(int i = 0; i < Decks.get(0)->cardList->size(); i++){
            Decks.get(0)->cardList->get(i)->relations = Decks.get(0)->relations;
            Decks.get(0)->cardList->get(i)->parentList = Decks.get(0);
        }
    }
    shuffle(Decks.get(0));
    Decks.get(0)->raise();
    for(int i = 6; i < 13; i++){
        Decks.get(i)->relations->insert(0, Decks.get(0));
        Decks.get(i)->populate();
        Decks.get(i)->updateList();
    }
}

void MainWindow::shuffle(QCardList* toShuffle)
{
    int s = toShuffle->cardList->size();
    srand(time(NULL));
    for (int i=s; i>1; i--)
        toShuffle->cardList->swap(i-1, rand() % i);
}

//WIP, not implemented into game yet but should work.
void MainWindow::checkGameStatus()
{
    int result = 0;
    for(int i = 0; i < Decks.size(); i++){
        if(Decks.get(i)->type == 'A'){
            if(Decks.get(i)->cardList->size() >= 13){
                result++;
            }
        }
    }
    if(result >= 4){
        QMessageBox *msg = new QMessageBox(QMessageBox::Question, "You've Won!", "Do you want to start a new game?", QMessageBox::Yes | QMessageBox::No, this, Qt::Popup);
        msg->setWindowModality(Qt::NonModal);
        msg->setDefaultButton(QMessageBox::Yes);
        int ret = msg->exec();
        int yes = 16384;
        if(ret == yes){
            on_actionNew_Game_triggered();
            return;
        }
        this->close();
    }
}
