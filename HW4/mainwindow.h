#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <QMainWindow>

#include "numplayersdialog.h"

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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    NumPlayersDialog *npd;
};
#endif // MAINWINDOW_H
