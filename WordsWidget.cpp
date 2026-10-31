#include "WordsWidget.h"

WordsWidget::WordsWidget(DatabaseManager& dbManager, QWidget* parent) : QWidget(parent), dbManager(dbManager) {
	wordModel = new WordsListModel(this);
	QListView* listView = new QListView(this);
	WordItemDelegate* delegate = new WordItemDelegate(listView);
	listView->setModel(wordModel);
	listView->setItemDelegate(delegate);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(listView);

	QSettings settings("paket", "QtVocabTrainer");
	auto res = dbManager.loadUserWords(settings.value("user/id").toInt());
	if (!res.isSuccess) QMessageBox::critical(this, "Critical error", res.error);
	else wordModel->setWords(res.data.value<QVector<Word>>());

	connect(delegate, &WordItemDelegate::delWordRequested, this, [&dbManager, this](int wordId) {
		auto questionRes = QMessageBox::question(this, "Removing a word", "Are you sure you want to delete the selected word?\nThis action cannot be undone.");
		if (questionRes == QMessageBox::Yes) {
			auto dbRes = dbManager.deleteWord(wordId);
			if (!dbRes.isSuccess) QMessageBox::critical(this, "Critical error", dbRes.error);
			else wordModel->deleteWord(wordId);
		}
	});
}

void WordsWidget::setPackId(int packId) {
	wordModel->setPackId(packId);
}

void WordsWidget::receiveNewWord(int packId, const QString& english) {
	auto res = dbManager.addWord(packId, english, "translation"); // translation
	Word word = {
		res.data.toMap()["id"].toInt(),
		packId,
		english,
		"translation", // translation
		res.data.toMap()["created_at"].toDateTime()
	};
	if (!res.isSuccess) QMessageBox::critical(this, "Critical error", res.error);
	else wordModel->insertWord(word);
}