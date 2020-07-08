#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbobj.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ClinicalDB = new DBObj();
    ClinicalDB->db_setpath("../Database/test1.sqlite");
    ClinicalDB->db_init();

    model_pats.setQuery(model_pats_query);

    ui->patsView->setModel(&model_pats);
    ui->patsView->show();
}

MainWindow::~MainWindow()
{
    delete ClinicalDB;
    delete ui;
}

void MainWindow::on_add_pat_Button_clicked()
{
    QString rxr, nhs;

    rxr = ui->rxrEdit->text();
    nhs = ui->nhsEdit->text();

    if(ClinicalDB->db_getpatid(rxr, nhs) < 0) {
        QMessageBox msg;

        msg.setWindowTitle("RXR not valid");
        msg.setText("The is a problem with the supplied RXR number.\nNothing has been added to the database.");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
    }
    else {
        ui->rxrEdit->clear();
        ui->nhsEdit->clear();
        model_pats.setQuery(model_pats_query);
    }
}
