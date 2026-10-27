#include "WordsWidget.h"

WordsWidget::WordsWidget(DatabaseManager& dbManager, QWidget* parent) : QWidget(parent), dbManager(dbManager) {
	wordModel = new WordsListModel(this);
	QListView* listView = new QListView(this);
	listView->setModel(wordModel);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(listView);

	QSettings settings("paket", "QtVocabTrainer");
	wordModel->setWords(dbManager.loadUserWords(settings.value("user/id").toInt()));
}

void WordsWidget::setPackId(int packId) {
	wordModel->setPackId(packId);
}

void WordsWidget::receiveNewWord(int packId, const QString& english) {
	dbManager.addWord(packId, english, "translation"); // translation
	wordModel->insertWord(packId, english);
}