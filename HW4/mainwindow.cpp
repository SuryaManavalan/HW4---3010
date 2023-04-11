#include <iostream>
#include <QtGlobal>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>>
#include <QDebug>
#include <QTime>
#include <string>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "numplayersdialog.h"
#include "pawn.h"
#include "player.h"
#include "manager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    npd = new NumPlayersDialog();
    npd->setModal(true);
    npd->exec();

    m = new Manager();

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
        color.setAlpha(0x90);
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
        Pawn * p1 = new Pawn(color, squareToCoord(1+i)[0],  squareToCoord(1+i)[1]);
//        Pawn * p1 = new Pawn(color, i*25, 5);
        Player * player = new Player(i+1, p1);
        player->setCurrSqr(1+i);

        m->addPlayer(player);

        scene->addItem(p1);
//        startScene->addItem(p1);
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

void MainWindow::on_roll_clicked()
{
    if(!pawnMoving){
        pawnMoving = true;

        int sqr = rand()%5 +1;
        qDebug() << sqr;
        ui->rollLabel->setText(QString::number(sqr));

        Player *player = m->getPlayers()[m->getTurn()-1];
        Pawn *pawn = player->getPawn();

        int newSQR = sqr + coordToSquare({pawn->get_x(), pawn->get_y()});
        int real_x = squareToCoord(sqr + coordToSquare({pawn->get_x(), pawn->get_y()}))[0];
        int real_y = squareToCoord(sqr + coordToSquare({pawn->get_x(), pawn->get_y()}))[1];


        sqr = player->getCurrSqr() + sqr;

        // Define the final position of the Pawn
        int final_x = squareToCoord(sqr)[0];
        int final_y = squareToCoord(sqr)[1];
        int speed = 5;

        // Create a QTimer object
        QTimer* timer = new QTimer(this);

        // Set the interval (in milliseconds) to update the position
        int interval = 50; // Update the position every 100 milliseconds
        timer->setInterval(interval);

        // Connect the timer to a function that updates the position of the Pawn


        connect(timer, &QTimer::timeout, [=]() {
            // Calculate the distance between the current position and the final position
            int dx = (final_x - pawn->get_x());
            int dy = (final_y - pawn->get_y());
            float distance = std::sqrt(dx*dx + dy*dy);

            qDebug() << "dx,dy:  : " << dx << ", " << dy;
            qDebug() << "distence : " << distance;


            // Calculate the unit vector pointing from the current position to the final position
            float ux = dx / distance;
            float uy = dy / distance;

            int new_x = pawn->get_x() + speed*ux; // Calculate the new x position based on the speed
            int new_y = pawn->get_y() + speed*uy; // Keep the same y position
            pawn->move(new_x, new_y); // Update the position of the Pawn
            scene->update(); // Repaint the scene to show the updated position

            if(distance < 10){//(qAbs(pawn->get_x() - final_x) < 7 && qAbs(pawn->get_y() - final_y) < 7 ){
                timer->stop(); // Stop the timer

                pawn->move(real_x, real_y);
                scene->update();

                player->setPrevSqr(player->getCurrSqr());
                player->setCurrSqr(newSQR);

                m->nextTurn();
                pawnMoving = false;
            }
        });

        // Start the timer
        timer->start();
    }
}

