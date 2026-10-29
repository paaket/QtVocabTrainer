#pragma once
#include "Config.h"
#include "Result.h"
#include "Word.h"
#include "WordPack.h"
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQUery>
#include <QSqlError>
#include <QString>
#include <QVariantMap>

class DatabaseManager {
public:
	DatabaseManager();
	Result connectDb();
	Result createUsersTable();
	Result createPacksTable();
	Result createWordsTable();
	Result insertTestData();
	Result loadUserPacks(int userId);
	Result loadUserWords(int userId);
	Result addWord(int packId, const QString& english, const QString& translation);
	Result registerUser(const QString& username, const QString& password);
	Result loginUser(const QString& username, const QString& password);
	Result addPack(int userId, const QString& title);
private:
	QSqlDatabase db;
	Config config;
};