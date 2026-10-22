#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() {
	db = QSqlDatabase::addDatabase("QPSQL");
}

Result DatabaseManager::connectDb() {
	db.setHostName(config.host);
	db.setPort(config.port);
	db.setDatabaseName(config.dbName);
	db.setUserName(config.username);
	db.setPassword(config.password);

	if (!db.open()) return Result{ 0, db.lastError().text() };
	return Result{ 1 , "" };
}

Result DatabaseManager::addWord(int packId, const QString& english, const QString& translation) {
	QSqlQuery query;
	query.prepare("INSERT INTO words(pack_id, english, translation) VALUES (:pack_id, :english, :translation);");
	query.bindValue(":pack_id", packId);
	query.bindValue(":english", english);
	query.bindValue(":translation", translation);
	if (!query.exec()) return Result{ 0, query.lastError().text() };
	return Result{ 1, "" };
}