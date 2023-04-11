#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QMainWindow>

#include "numplayersdialog.h"
#include "manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::vector<int> squareToCoord(int num);
    int coordToSquare(std::vector<int>);

    void initPawns(int);

private slots:
    void on_roll_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    NumPlayersDialog *npd;
    Manager* m;

    bool pawnMoving = false;
};
#endif // MAINWINDOW_H
