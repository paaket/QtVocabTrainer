#pragma once
#include "Word.h"
#include <QAbstractListModel>
#include <QVector>

class WordsListModel : public QAbstractListModel {
public:
	enum Roles {
		IdRole = Qt::UserRole,
		PackIdRole,
		EnglishRole,
		TranslationRole
	};
public:
	WordsListModel(QObject* parent = nullptr);
	QVariant data(const QModelIndex& index, int role) const override;
	int rowCount(const QModelIndex& parent) const override;
	void setPackId(int packId);
private:
	QVector<Word> allWords {
		{ 0, 0, "apple", "translate" },
		{ 1, 0, "car", "translate" },
		{ 2, 1, "book", "translate" },
		{ 3, 1, "pen", "translate" },
		{ 4, 1, "door", "translate" },
		{ 5, 1, "number", "translate" },
		{ 6, 2, "sky", "translate" },
		{ 7, 2, "sun", "translate" },
		{ 8, 2, "rain", "translate" }
	};
	QVector<Word> visibleWords;
	int currPackId = -1;
};