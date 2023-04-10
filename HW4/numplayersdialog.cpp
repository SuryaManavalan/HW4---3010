#include "numplayersdialog.h"
#include "ui_numplayersdialog.h"

NumPlayersDialog::NumPlayersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumPlayersDialog)
{
    ui->setupUi(this);
}

NumPlayersDialog::~NumPlayersDialog()
{
    delete ui;
}

void NumPlayersDialog::on_submitButton_clicked()
{
    numPlayers = ui->NumSpin->value();
    this->close();
}

