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
    if (!query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY, username TEXT NOT NULL UNIQUE, password TEXT NOT NULL, created_at TIMESTAMPTZ NOT NULL DEFAULT CURRENT_TIMESTAMP);"))
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

	query.prepare("INSERT INTO users(username, password) VALUES (:username, :password);");
	query.bindValue(":username", "test");
	query.bindValue(":password", "123456789");
	if (!query.exec())
		return Result{ 0, query.lastError().text() };
	query.clear();

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

QVector<WordPack> DatabaseManager::loadUserPacks(int userId) {
	QVector<WordPack> arr;
	QSqlQuery query;
	query.prepare("SELECT id, title, created_at FROM packs WHERE user_id = :user_id");
	query.bindValue(":user_id", userId);
	if (!query.exec()) return arr;
	while (query.next()) 
		arr.push_back({ 
			query.value("id").toInt(),
			query.value("title").toString(),
			query.value("created_at").toDateTime().toLocalTime()
		});
	return arr;
}

QVector<Word> DatabaseManager::loadUserWords(int userId) {
	QVector<Word> arr;
	QSqlQuery query;
	query.prepare("SELECT words.id, words.pack_id, words.english, words.translation, words.created_at FROM packs INNER JOIN words ON words.pack_id = packs.id WHERE packs.user_id = :user_id");
	query.bindValue(":user_id", userId);
	if (!query.exec()) return arr;
	while (query.next())
		arr.push_back({
			query.value("id").toInt(),
			query.value("pack_id").toInt(),
			query.value("english").toString(),
			query.value("translation").toString(),
			query.value("created_at").toDateTime().toLocalTime()
		});
	return arr;
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

Result DatabaseManager::registerUser(const QString& username, const QString& password) {
	db.transaction();

	QSqlQuery checkQuery;
	checkQuery.prepare("SELECT id FROM users WHERE username = :username LIMIT 1");
	checkQuery.bindValue(":username", username);
	if (!checkQuery.exec()) {
		db.rollback();
		return Result{ 0, checkQuery.lastError().text() };
	}
	if (checkQuery.next()) {
		db.rollback();
		return Result{ 0, "An account with this username already exists" };
	}

	QSqlQuery insertQuery;
	insertQuery.prepare("INSERT INTO users(username, password) VALUES (:username, :password)");
	insertQuery.bindValue(":username", username);
	insertQuery.bindValue(":password", password);
	if (!insertQuery.exec()) {
		db.rollback();
		return Result{ 0, checkQuery.lastError().text() };
	}

	db.commit();
	return Result{ 1, "" };
}

Result DatabaseManager::loginUser(const QString& username, const QString& password) {
	QSqlQuery query;
	query.prepare("SELECT id, username, created_at FROM users WHERE username = :username AND password = :password LIMIT 1");
	query.bindValue(":username", username);
	query.bindValue(":password", password);
	if (!query.exec())
		return Result{ 0, query.lastError().text() };
	if (!query.next())
		return Result{ 0, "Account not found.\nThe information may have been entered incorrectly."};
	QVariantMap user;
	user["id"] = query.value(0).toInt();
	user["username"] = query.value(1).toDateTime();
	user["created_at"] = query.value(2).toDateTime();
	return Result{ 1, "", user };
}