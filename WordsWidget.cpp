#include "WordsWidget.h"

WordsWidget::WordsWidget(DatabaseManager& dbManager, QWidget* parent) : QWidget(parent), dbManager(dbManager) {
	wordModel = new WordsListModel(this);
	QListView* listView = new QListView(this);
	WordItemDelegate* delegate = new WordItemDelegate(listView);
	listView->setModel(wordModel);
	listView->setItemDelegate(delegate);

	QFont numFont;
	numFont.setPointSize(20);

	wordsNumLbl = new QLabel("None", this);
	QLabel* wordTextLbl = new QLabel("total words", this);
	wordsNumLbl->setFont(numFont);

	QFrame* hLine = new QFrame(this);
	hLine->setFrameShape(QFrame::HLine);
	hLine->setFrameShadow(QFrame::Sunken);

	QGridLayout* grid = new QGridLayout();
	grid->addWidget(wordsNumLbl, 0, 0);
	grid->addWidget(wordTextLbl, 1, 0, Qt::AlignTop | Qt::AlignLeft);
	grid->addWidget(hLine, 2, 0, 1, 2);

	QPushButton* startBtn = new QPushButton("Start review", this);
	startBtn->setMinimumHeight(40);

	QFrame* panel = new QFrame(this);
	panel->setFrameShape(QFrame::StyledPanel);
	panel->setFrameShadow(QFrame::Sunken);

	QVBoxLayout* panelVbox = new QVBoxLayout(panel);
	panelVbox->addLayout(grid);
	panelVbox->addWidget(startBtn);
	panelVbox->addWidget(listView);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(panel);

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
	connect(startBtn, &QPushButton::clicked, this, [this]() {
		emit startReviewClicked();
	});
}

void WordsWidget::setPackId(int packId) {
	wordModel->setPackId(packId);
	int wordsNum = wordModel->getVisibleWordsCount();
	wordsNumLbl->setText(QString::number(wordsNum));
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

QVector<Word> WordsWidget::getWords() {
	return wordModel->getCurrWords();
}