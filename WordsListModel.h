#pragma once
#include "Word.h"
#include <QAbstractListModel>
#include <QVector>

class WordsListModel : public QAbstractListModel {
	Q_OBJECT
public:
	enum Roles {
		IdRole = Qt::UserRole,
		PackIdRole,
		EnglishRole,
		TranslationRole,
		CreatedAtRole
	};
public:
	WordsListModel(QObject* parent = nullptr);
	QVariant data(const QModelIndex& index, int role) const override;
	int rowCount(const QModelIndex& parent) const override;
	void setPackId(int packId);
	void setWords(QVector<Word> words);
	void deleteWord(int wordId);
private:
	QVector<Word> allWords;
	QVector<Word> visibleWords;
	int currPackId = -1;
public slots:
	void insertWord(const Word& word);
};