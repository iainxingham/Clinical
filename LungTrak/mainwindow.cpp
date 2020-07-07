#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbobj.h"

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
    ClinicalDB->db_getpatid(rxr, nhs);

    ui->rxrEdit->clear();
    ui->nhsEdit->clear();
    model_pats.setQuery(model_pats_query);
}
