#pragma once
#include "Config.h"
#include "Result.h"
#include <QSqlDatabase>
#include <QSqlQUery>
#include <QSqlError>
#include <QString>

class DatabaseManager {
public:
	DatabaseManager();
	Result connectDb();
	Result addWord(int packId, const QString& english, const QString& translation);
private:
	QSqlDatabase db;
	Config config;
};