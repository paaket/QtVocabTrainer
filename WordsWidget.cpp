#include "WordsWidget.h"

WordsWidget::WordsWidget(DatabaseManager& dbManager, QWidget* parent) : QWidget(parent), dbManager(dbManager) {
	wordModel = new WordsListModel(this);
	QListView* listView = new QListView(this);
	listView->setModel(wordModel);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(listView);

	wordModel->setWords(dbManager.loadUserWords(1)); //user_id from qsettings
}

void WordsWidget::setPackId(int packId) {
	wordModel->setPackId(packId);
}

void WordsWidget::receiveNewWord(int packId, const QString& english) {
	dbManager.addWord(packId, english, "translation"); // translation
	wordModel->insertWord(packId, english);
}