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
	if (role == WordsListModel::CreatedAtRole) return word.created_at;

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

void WordsListModel::insertWord(const Word& word) {
	if (word.packId == currPackId) {
		beginInsertRows(QModelIndex(), visibleWords.size(), visibleWords.size());
		allWords.push_back(word);
		visibleWords.push_back(word);
		endInsertRows();
	}
	else {
		allWords.push_back(word);
	}
}

void WordsListModel::setWords(QVector<Word> words) {
	beginResetModel();
	this->allWords = words;
	endResetModel();
}

void WordsListModel::deleteWord(int wordId) {
	int wordVisInd = 0;
	for (int i = 0; i < visibleWords.size(); i++)
		if (visibleWords[i].id == wordId) wordVisInd = i;

	beginRemoveRows(QModelIndex(), wordVisInd, wordVisInd);
	visibleWords.erase(visibleWords.begin() + wordVisInd);
	endRemoveRows();

	int wordAllInd = 0;
	for (int i = 0; i < allWords.size(); i++)
		if (allWords[i].id == wordId) wordAllInd = i;
	allWords.erase(allWords.begin() + wordAllInd);
}