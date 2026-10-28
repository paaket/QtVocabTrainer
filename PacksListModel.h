#pragma once
#include "WordPack.h"
#include <QAbstractListModel>
#include <QVector>
#include <QString>

class PacksListModel : public QAbstractListModel {
public:
	enum Roles {
		IdRole = Qt::UserRole,
		TitleRole,
		WordCountRole
	};
public:
	PacksListModel(QObject* parent = nullptr);
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	void setPacks(QVector<WordPack> packs);
	void insertPack(int packId, const QString& title, const QDateTime& createdAt);
private:
	QVector<WordPack> packs;
};