#include "progressthread.h"
#include <QFile>
#include <QDebug>
#include <mainwindow.h>

double finalEstSize;
QString finalFile;
int percent;
MainWindow* myParent;


void ProgressThread::setEstSize(double size)
{
    finalEstSize = size;
}

void ProgressThread::printSomething()
{
    qDebug() <<"catfishHHHH" << endl;
}

int ProgressThread::getPercent()
{
    return percent;
}

void ProgressThread::setPercent()
{

}

void ProgressThread::setParent(MainWindow* parent)
{
  myParent = parent;
}

void ProgressThread::setFinalFile(QString file)
{
    finalFile = file;
}

void ProgressThread::run(){
    bool isRunning = true;
    while (isRunning) {
       double currentSize = checkCurrentSize(finalFile);
       percent = (currentSize/finalEstSize)*100;
       qDebug() << "The Output File is currently :" << currentSize << endl;
       qDebug() << "percent should be" << percent;
       QObject::connect(this,SIGNAL(valueChanged(int)),myParent,SLOT(setMyPercent(int)));
       emit valueChanged(percent);
       double diff = finalEstSize - currentSize;
       if(diff < 4096){
           percent = 100;
           isRunning = false;
       }
    }
}

double ProgressThread::checkCurrentSize(QString inputfile){
   QFile myFile(inputfile);
   double currentSize = myFile.size();
   return currentSize;
}
