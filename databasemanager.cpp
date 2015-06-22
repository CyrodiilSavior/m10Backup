#include "databasemanager.h"
#include <QSql>


 QSqlDatabase myDb;

 QList<QList<QString> > myItems;


 void DatabaseManager::connect()
 {
     myDb = QSqlDatabase::addDatabase("QSQLITE");
     myDb.setDatabaseName("/Volumes/Dev/Projects/C++/m10Backup/m10BackupData.db");
              qDebug() << "Database Opened!" << endl;
 }


 QList<QList<QString> > DatabaseManager::update()
 {

     if(myDb.open()){

         QSqlQuery qry;

         QList<QString> IDs;
         QList<QString> BackupNames;
         QList<QString> BackupFrom;
         QList<QString> BackupTo;

         //Populate IDs
         QString tmp;
         if(qry.exec("SELECT ID FROM Backups")){
             while(qry.next()){
                 tmp = qry.value(0).toString();
                 IDs.append(tmp);
             }
         }

         //Populate Names
         if(qry.exec("SELECT \"Backup Name\" FROM Backups")){
             while(qry.next()){
                 tmp = qry.value(0).toString();
                 BackupNames.append(tmp);
             }
         }

         //Populate Froms
         if(qry.exec("SELECT \"Backup From\" FROM Backups")){
             while(qry.next()){
                 tmp = qry.value(0).toString();
                 BackupFrom.append(tmp);
             }
         }

         //Populate Tos
         if(qry.exec("SELECT \"Backup To\" FROM Backups")){
             while(qry.next()){
                 tmp = qry.value(0).toString();
                 BackupTo.append(tmp);
             }
         }



         myItems.append(IDs);
         myItems.append(BackupNames);
         myItems.append(BackupFrom);
         myItems.append(BackupTo);

         IDs.clear();
         BackupNames.clear();
         BackupFrom.clear();
         BackupTo.clear();

         qry.clear();
         myDb.close();


                 return myItems;
     }
     else
         qDebug() << "Databse Failed1" << endl;

 }

 void DatabaseManager::addNewBackup(int id, QString backupName, QString backupFrom, QString backupTo, QString Schedule)
 {

        if(myDb.open()){

            qDebug() << "Attampting to add..." << endl;
            QSqlQuery qry2;
            QString myCommand = "INSERT INTO Backups VALUES (2,\"" + backupName + "\","       + "\"" + backupFrom + "\","               + "\"" + backupTo + "\")";
            qDebug() << myCommand << endl;
         if(qry2.exec(myCommand)){
             qDebug() << "Row Added Successfully!" << endl;
         }

        }
        else{
            qDebug() << myDb.lastError();
        }

 }

DatabaseManager::DatabaseManager()
{

}

DatabaseManager::~DatabaseManager()
{
    myDb.close();
}



