#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <quaziputil.h>
#include <QStringList>
#include <QFileDialog>
#include <QDebug>
#include <iostream>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include "threadmanager.h"
#include <progressthread.h>
#include <newbackup.h>
#include <QDataStream>
#include <QList>
#include <databasemanager.h>

DatabaseManager d;
QList<QList<QString> > databaseItems;
QList<QString> IDs;
QList<QString> BackupNames;
QList<QString> BackupFrom;
QList<QString> BackupTo;


int MainWindow::getCurrentID()
{
    int myCount = ui->listWidget_2->count();
}

void MainWindow::refresh()
{
    qDebug() << "Refreshing..." << endl;


    ui->listWidget_2->clear();
    databaseItems = d.update();
    IDs = databaseItems.at(0);
    BackupNames = databaseItems.at(1);
    BackupFrom = databaseItems.at(2);
    BackupTo = databaseItems.at(3);

    for(int i=0;i<IDs.length();i++){
        ui->listWidget_2->addItem(BackupNames.at(i));
        qDebug() << "IDS: " << IDs.at(i);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    d.connect();
    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_actionQuit_triggered()
{
    MainWindow::lower();
}

void MainWindow::on_actionLoad_mtb_Backup_File_triggered()
{
   ui->listWidget->clear();
   QString fileName = QFileDialog::getOpenFileName(this,
   tr("Open File"),"",
   tr("m10 Backup File (*.mtb);;All Files (*)"));
   QFile file(fileName);
   if(!file.exists()){
       return;
   }
   QuazipUtil q;
   QStringList files = q.listFiles(fileName);
   for(int i =0; i<files.length();i++){
          ui->listWidget->addItem("/"+files.at(i));
   }


}


void MainWindow::on_button1_released()
{
      QString fileName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
              "/",
              QFileDialog::ShowDirsOnly
              |QFileDialog::DontResolveSymlinks);
       ui->lineEdit_backupFrom->setText(fileName);
}

void MainWindow::on_button2_released()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save m10 Backup file"), "",
        tr("m10 Backup File (*.mtb);;All Files (*)"));
    ui->lineEdit_outputFolder->setText(fileName);
}

void MainWindow::on_button3_released()
{
    if(ui->lineEdit_backupFrom->text()==""&&ui->lineEdit_outputFolder->text()==""){
        return;
    }

    //Perform Backup
    ui->progressBar->setVisible(true);
    QString backupFrom = ui->lineEdit_backupFrom->text();
    QString backupTo = ui->lineEdit_outputFolder->text();
    int length = backupTo.length()-1;
    QString subString = backupTo.right(3);
    qDebug() << subString;
    if(subString!="mtb"){
        backupTo.replace(backupTo.length()-4,".mtb");

        ui->lineEdit_outputFolder->setText(backupTo);
    }
    ThreadManager mThread;
    ProgressThread* p = new ProgressThread;
    p->setParent(this);
    mThread.setBackupFrom(backupFrom);
    mThread.setBackupTo(backupTo);
    p->setFinalFile(backupTo);
    ThreadManager *t = new ThreadManager;
    t->setProgressManagerToPass(p);
    t->start();

}

void MainWindow::on_actionNew_Backup_triggered()
{
    NewBackup* n = new NewBackup();
    n->show();

}

void MainWindow::setMyPercent(int percent)
{
  ui->progressBar->setValue(percent);
}

void MainWindow::on_actionLoad_Previous_Backup_triggered()
{

    QList<QString> myPrefs;
    QString mtpFileName = QFileDialog::getOpenFileName(this,
    tr("Open File"),"",
    tr("m10 Backup File (*.mtp);;All Files (*)"));

    QFile fileToRead(mtpFileName);

    if(!fileToRead.open(QIODevice::ReadOnly)){
        qDebug() << "Read Failed!" << endl;
    }

    QDataStream in(&fileToRead);
    in.setVersion(QDataStream::Qt_5_3);
    in >> myPrefs;
    fileToRead.flush();
    fileToRead.close();

    for(int i =0; i<myPrefs.length();i++){
        qDebug() <<myPrefs.at(i) << endl;
    }

    d.addNewBackup(getCurrentID(),myPrefs.at(1),myPrefs.at(2),myPrefs.at(3),myPrefs.at(4));

}

void MainWindow::on_pushButton_2_clicked()
{

        refresh();

 }
