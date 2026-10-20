#include "WordsListModel.h"

WordsListModel::WordsListModel(QObject* parent) : QAbstractListModel(parent) {}

QVariant WordsListModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid() or index.row() < 0 or index.row() >= visibleWords.size()) return{};

	const Word& word = visibleWords[index.row()];

	if (role == Qt::DisplayRole) return word.english + " - " + word.translation;
	if (role == WordsListModel::IdRole) return word.id;
	if (role == WordsListModel::PackIdRole) return word.packId;
	if (role == WordsListModel::EnglishRole) return word.english;
	if (role == WordsListModel::TranslationRole) return word.translation;

	return {};
}

int WordsListModel::rowCount(const QModelIndex& parent) const {
	if (parent.isValid()) return 0;
	return visibleWords.size();
}

void WordsListModel::setPackId(int packId) {
	beginResetModel();

	currPackId = packId;
	visibleWords.clear();
	for (const Word& word : allWords)
		if (word.packId == currPackId) visibleWords.push_back(word);

	endResetModel();
}

void WordsListModel::insertWord(int packId, const QString& english) {
	Word word{ -1, packId, english, "-" };
	if (packId = currPackId) {
		beginInsertRows(QModelIndex(), visibleWords.size(), visibleWords.size());
		allWords.push_back(word);
		visibleWords.push_back(word);
		endInsertRows();
	}
	else {
		allWords.push_back(word);
	}
}