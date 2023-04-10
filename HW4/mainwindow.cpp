#include <iostream>
#include <QtGlobal>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>>
#include <QDebug>
#include <QTime>
#include <string>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "numplayersdialog.h"
#include "pawn.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    npd = new NumPlayersDialog();
    npd->setModal(true);
    npd->exec();

    ui->setupUi(this);
    QGraphicsView * view = ui->graphicsView;

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene;
    view->setScene(scene);

    // make the scene the same size as the view containing it
    view->setSceneRect(0,0,view->frameSize().width(),view->frameSize().height());

    // add grid lines
    for(int i = 1; i < 10; i++){
        scene->addLine(0,44*i,500,44*i);
    }

    for(int i = 1; i < 10; i++){
        scene->addLine(44*i +2*i,0,44*i +2*i,500);
    }

    // testing square to Coord

    std::vector<int> coord = squareToCoord(84);

    QGraphicsRectItem* rectItem = new QGraphicsRectItem(coord[0], coord[1], 10, 10);

    QPen pen(Qt::black);
    QBrush brush(Qt::blue);
    rectItem->setPen(pen);
    rectItem->setBrush(brush);

    scene->addItem(rectItem);

    qDebug() << coordToSquare(squareToCoord(84));

    // draw ladder from 7 to 100

    QPen pladder(QColor(0, 0xFF, 0, 0x80));
    pladder.setWidth(10);
    scene->addLine(squareToCoord(7)[0],squareToCoord(7)[1], squareToCoord(100)[0],squareToCoord(100)[1], pladder);

    // draw shoot from 99 to 1

    QPen pshoot(QColor(0xFF, 0, 0, 0x80));
    pshoot.setWidth(10);
    scene->addLine(squareToCoord(99)[0],squareToCoord(99)[1], squareToCoord(1)[0],squareToCoord(1)[1], pshoot);

    // starting place

    initPawns(npd->get_num_players());

}

void MainWindow::initPawns(int n){
    QGraphicsView * startView = ui->startSpace;
    QGraphicsScene * startScene = new QGraphicsScene;
    startView->setScene(startScene);

    for(int i = 0; i < n; i++){
        QColor color = QColor();
        switch (i) {
        case 0:
            color.setRed(255);
            break;
        case 1:
            color.setBlue(255);
            break;
        case 2:
            color.setGreen(255);
            break;
        case 3:
            color.setRed(150);
            color.setBlue(150);
            break;
        default:
            break;
        }
        Pawn * p1 = new Pawn(color, i*25, 5);

        startScene->addItem(p1);
    }
}

std::vector<int> MainWindow::squareToCoord(int num){
    std::vector<int> out{0, 0};

    int xtemp = 0;
    int ytemp = 0;

    int row = num/10;

    if(num%10 == 0)
        row--;

    xtemp = (num - row*10) * 44 + 22;
    ytemp = row*44 + 22;

    if(row % 2 == 1)
        xtemp = ui->graphicsView->frameSize().width() - xtemp;
    else
        xtemp -= 44;

    ytemp = ui->graphicsView->frameSize().height() - ytemp;

    out[0] = xtemp;
    out[1] = ytemp;

    return out;
}

int MainWindow::coordToSquare(std::vector<int> c){
    int x = c[0]/44;
    int y = c[1]/44;

    y = qAbs(9-y);

    if(y%2 == 1)
        x = qAbs(9-x);

    y *= 10;

    return y + x + 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}
