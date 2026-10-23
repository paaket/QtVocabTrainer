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

Result DatabaseManager::createUsersTable() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY, username TEXT NOT NULL UNIQUE, created_at TIMESTAMPTZ NOT NULL DEFAULT CURRENT_TIMESTAMP);"))
        return Result{ 0, query.lastError().text() };
    return Result{ 1, "" };
}

Result DatabaseManager::createPacksTable() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS packs (id INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY, user_id INTEGER NOT NULL, title TEXT NOT NULL, created_at TIMESTAMPTZ NOT NULL DEFAULT CURRENT_TIMESTAMP, FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE);"))
        return Result{ 0, query.lastError().text() };
    return Result{ 1, "" };
}

Result DatabaseManager::createWordsTable() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS words (id INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY, pack_id INTEGER NOT NULL, english TEXT NOT NULL, translation TEXT NOT NULL, created_at TIMESTAMPTZ NOT NULL DEFAULT CURRENT_TIMESTAMP, FOREIGN KEY (pack_id) REFERENCES packs(id) ON DELETE CASCADE);"))
        return Result{ 0, query.lastError().text() };
    return Result{ 1, "" };
}

Result DatabaseManager::insertTestData() {
	QSqlQuery query;

	/*query.prepare("INSERT INTO users(username) VALUES (:username);");
	query.bindValue(":username", "test");
	if (!query.exec())
		return Result{ 0, query.lastError().text() };
	query.clear();*/

	query.prepare("INSERT INTO packs(user_id, title) VALUES (:user_id, :title);");
	query.bindValue(":user_id", 1);
	query.bindValue(":title", "first");
	if (!query.exec())
		return Result{ 0, query.lastError().text() };
	query.clear();

	query.prepare("INSERT INTO words(pack_id, english, translation) VALUES (:pack_id, :english, :translation);");
	query.bindValue(":pack_id", 1);
	query.bindValue(":english", "english");
	query.bindValue(":translation", "translation");
	if (!query.exec()) {
		qDebug() << query.lastError().text();
		return Result{ 0, query.lastError().text() };
	}
	query.clear();

	return Result{ 1, "" };
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