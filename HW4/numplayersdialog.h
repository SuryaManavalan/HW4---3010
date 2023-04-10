#ifndef NUMPLAYERSDIALOG_H
#define NUMPLAYERSDIALOG_H

#include <QDialog>

namespace Ui {
class NumPlayersDialog;
}

class NumPlayersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NumPlayersDialog(QWidget *parent = nullptr);
    ~NumPlayersDialog();
    int get_num_players() const {return numPlayers;};

private slots:
    void on_submitButton_clicked();

private:
    Ui::NumPlayersDialog *ui;
    int numPlayers;
};

#endif // NUMPLAYERSDIALOG_H
