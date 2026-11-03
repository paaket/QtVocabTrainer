#include "WordEntryWidget.h"

WordEntryWidget::WordEntryWidget(QWidget* parent) : QWidget(parent) {
	QFont wordFont;
	wordFont.setPointSize(28);
	QFont lineFont;
	lineFont.setPointSize(16);

	wordLbl = new QLabel("Word");
	wordLbl->setFont(wordFont);

	QLabel* infoLbl = new QLabel("enter the translation of the word:", this);
	QPalette infoPalette = infoLbl->palette();
	infoPalette.setColor(QPalette::WindowText, Qt::lightGray);
	infoLbl->setPalette(infoPalette);

	line = new QLineEdit(this);
	line->setPlaceholderText("enter the translation here");
	line->setFont(lineFont);
	line->setMinimumSize(100, 50);

	QPushButton* checkBnt = new QPushButton("Check", this);
	checkBnt->setMinimumSize(100, 50);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(wordLbl, 0, Qt::AlignCenter);
	vbox->addWidget(infoLbl, 0, Qt::AlignBottom | Qt::AlignHCenter);
	vbox->addWidget(line);
	vbox->addWidget(checkBnt);

	connect(checkBnt, &QPushButton::clicked, this, [this]() {
		if (line->text().isEmpty() or line->text().trimmed().isEmpty()) {
			QMessageBox::warning(this, "Error", "The response cannot be empty");
			return;
		}
		emit answerSubmitted(line->text().trimmed());
	});
}

void WordEntryWidget::setWord(const Word& word) {
	wordLbl->setText(word.english);
	line->clear();
}