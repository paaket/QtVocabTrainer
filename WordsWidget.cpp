#include "WordsWidget.h"

WordsWidget::WordsWidget(QWidget* parent) : QWidget(parent) {
	wordModel = new WordsListModel(this);
	QListView* listView = new QListView(this);
	listView->setModel(wordModel);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(listView);
}

void WordsWidget::setPackId(int packId) {
	wordModel->setPackId(packId);
}

void WordsWidget::receiveNewWord(int packId, const QString& english) {
	wordModel->insertWord(packId, english);
}