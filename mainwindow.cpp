#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qsolitairecard.cpp"
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
    char types[4] = {'C', 'D', 'H', 'S'};
    char numbers[13] = {'K', 'Q', 'J', '0', '9', '8', '7', '6', '5', '4', '3', '2', 'A'};
    TDALISTA<QSolitaireCard*>* lista = new TDALISTA<QSolitaireCard*>();
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 13; j++){
            lista->add(new QSolitaireCard(types[i], numbers[j], QPoint(50, 50), ui->centralWidget));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    //event->accept();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    //event->accept();
}
