#include "PacksListModel.h"

PacksListModel::PacksListModel(QObject* parent) : QAbstractListModel(parent) {}

QVariant PacksListModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid() or index.row() < 0 or index.row() >= packs.size()) return{};

	const WordPack& pack = packs[index.row()];

	if (role == Qt::DisplayRole) return pack.title;
	if (role == PacksListModel::IdRole) return pack.id;
	if (role == PacksListModel::TitleRole) return pack.title;
	// if (role == PacksListModel::WordCountRole) return pack.wordCount;

	return {};
}

int PacksListModel::rowCount(const QModelIndex& parent) const {
	if (parent.isValid()) return 0;
	return packs.size();
}

void PacksListModel::setPacks(QVector<WordPack> packs) {
	beginResetModel();
	this->packs = packs;
	endResetModel();
}