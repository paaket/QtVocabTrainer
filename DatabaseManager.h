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
	QVector<WordPack> loadUserPacks(int userId);
	QVector<Word> loadUserWords(int userId);
	Result addWord(int packId, const QString& english, const QString& translation);
	Result registerUser(const QString& username, const QString& password);
	Result loginUser(const QString& username, const QString& password);
private:
	QSqlDatabase db;
	Config config;
};