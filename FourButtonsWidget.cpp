#include "FourButtonsWidget.h"

FourButtonsWidget::FourButtonsWidget(QWidget* parent) : QWidget(parent) {
	QFont wordFont;
	wordFont.setPointSize(28);

	QLabel* wordLbl = new QLabel("Word", this);
	wordLbl->setFont(wordFont);
	QLabel* infoLbl = new QLabel("choose the correct translation of the word:", this);
	QPalette infoPalette = infoLbl->palette();
	infoPalette.setColor(QPalette::WindowText, Qt::lightGray);
	infoLbl->setPalette(infoPalette);

	QPushButton* firstBtn = new QPushButton("first", this);
	QPushButton* secondBtn = new QPushButton("second", this);
	QPushButton* thirdBtn = new QPushButton("third", this);
	QPushButton* fourthBtn = new QPushButton("fourth", this);
	firstBtn->setMinimumSize(100, 50);
	secondBtn->setMinimumSize(100, 50);
	thirdBtn->setMinimumSize(100, 50);
	fourthBtn->setMinimumSize(100, 50);

	QGridLayout* btnGrid = new QGridLayout();
	btnGrid->addWidget(firstBtn, 0, 0);
	btnGrid->addWidget(secondBtn, 0, 1);
	btnGrid->addWidget(thirdBtn, 1, 0);
	btnGrid->addWidget(fourthBtn, 1, 1);

	QVBoxLayout* wordVbox = new QVBoxLayout();
	wordVbox->addWidget(wordLbl, 0, Qt::AlignHCenter);
	wordVbox->addWidget(infoLbl, 0, Qt::AlignHCenter);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addLayout(wordVbox);
	vbox->addLayout(btnGrid);

	connect(firstBtn, &QPushButton::clicked, [firstBtn, this]() { emit answerSelected(firstBtn->text()); });
	connect(secondBtn, &QPushButton::clicked, [secondBtn, this]() { emit answerSelected(secondBtn->text()); });
	connect(thirdBtn, &QPushButton::clicked, [thirdBtn, this]() { emit answerSelected(thirdBtn->text()); });
	connect(fourthBtn, &QPushButton::clicked, [fourthBtn, this]() { emit answerSelected(fourthBtn->text()); });
}