#include "MainWindow.h"
#include "DatabaseManager.h"
#include "LoginWindow.h"
#include <QApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    DatabaseManager dbManager;
    auto res = dbManager.connectDb();
    if (!res.isSuccess) {
        qDebug() << "db error: " << res.error;
        return 1;
    }

    /*res = dbManager.createUsersTable();
    if (!res.isSuccess) {
        qDebug() << "users table error: " << res.error;
        return 1;
    }
    res = dbManager.createPacksTable();
    if (!res.isSuccess) {
        qDebug() << "packs table error: " << res.error;
        return 1;
    }
    res = dbManager.createWordsTable();
    if (!res.isSuccess) {
        qDebug() << "wirds table error: " << res.error;
        return 1;
    }*/

    /*res = dbManager.insertTestData();
    if (!res.isSuccess) {
        qDebug() << "test data insert error: " << res.error;
        return 1;
    }*/

    /*QSettings settings("paket", "QtVocabTrainer");
    if (!settings.value("user/remember_me").toBool()) {
        
    }*/

    QSettings settings("paket", "QtVocabTrainer");
    bool login = settings.value("auth/remember", false).toBool();
    if (!login) {
        LoginWindow loginWindow;
        if (loginWindow.exec() == QDialog::Accepted) login = true;
    }
    if (login) {
        MainWindow window(dbManager);
        window.show();
        return app.exec();
    }

    return 0;
}