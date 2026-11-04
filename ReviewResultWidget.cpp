#include "ReviewResultWidget.h"

ReviewResultWidget::ReviewResultWidget(QWidget* parent) : QWidget(parent) {
	accuracyLbl = new QLabel("None%", this);
	QFont accuracyFont;
	accuracyFont.setPointSize(20);
	QPalette accuracyPalette = accuracyLbl->palette();
	accuracyPalette.setColor(QPalette::WindowText, Qt::green);
	accuracyLbl->setFont(accuracyFont);
	accuracyLbl->setPalette(accuracyPalette);

	QLabel* accuracyInfoLbl = new QLabel("accuracy without corrections", this);
	QFont accInfoFont;
	accInfoFont.setPointSize(10);
	accuracyInfoLbl->setFont(accInfoFont);

	correctLbl = new QLabel("None correct", this);
	errorsLbl = new QLabel("None mistakes", this);
	fixedLbl = new QLabel("None fixed", this);
	notFixedLbl = new QLabel("None not fixed", this);

	QFrame* answerHLine = new QFrame(this);
	answerHLine->setFrameShape(QFrame::HLine);
	answerHLine->setFrameShadow(QFrame::Sunken);

	QGridLayout* answerGrid = new QGridLayout();
	answerGrid->addWidget(accuracyLbl, 0, 0);
	answerGrid->addWidget(accuracyInfoLbl, 0, 1);
	answerGrid->addWidget(correctLbl, 1, 0);
	answerGrid->addWidget(errorsLbl, 1, 1);
	answerGrid->addWidget(fixedLbl, 2, 0);
	answerGrid->addWidget(notFixedLbl, 2, 1);
	answerGrid->addWidget(answerHLine, 3, 0, 1, 2);

	QFont boldFont;
	boldFont.setBold(true);

	QLabel* timeHeadLbl = new QLabel("Time", this);
	timeHeadLbl->setFont(boldFont);
	QLabel* totalTimeHeadLbl = new QLabel("Total time", this);
	totalTimeLbl = new QLabel("None", this);
	QLabel* perWordHeadLbl = new QLabel("Per word", this);
	perWordLbl = new QLabel("None", this);

	QFrame* timeHLine = new QFrame(this);
	timeHLine->setFrameShape(QFrame::HLine);
	timeHLine->setFrameShadow(QFrame::Sunken);

	QGridLayout* timeGrid = new QGridLayout();
	timeGrid->addWidget(timeHeadLbl, 0, 0);
	timeGrid->addWidget(totalTimeHeadLbl, 1, 0);
	timeGrid->addWidget(totalTimeLbl, 1, 1);
	timeGrid->addWidget(perWordHeadLbl, 2, 0);
	timeGrid->addWidget(perWordLbl, 2, 1);
	timeGrid->addWidget(timeHLine, 3, 0, 1, 2);

	errorsList = new QListWidget(this);
	QLabel* listHead = new QLabel("Words for review", this);
	listHead->setFont(boldFont);

	QVBoxLayout* listVbox = new QVBoxLayout();
	listVbox->addWidget(listHead);
	listVbox->addWidget(errorsList);

	QPushButton* returnBackBtn = new QPushButton("Return to the words", this);

	QVBoxLayout* mainVbox = new QVBoxLayout(this);
	mainVbox->addLayout(answerGrid);
	mainVbox->addLayout(timeGrid);
	mainVbox->addLayout(listVbox);
	mainVbox->addWidget(returnBackBtn);

	connect(returnBackBtn, &QPushButton::clicked, this, [this]() { emit retutnClicked(); });
}

void ReviewResultWidget::setStatistics(const ReviewStatistics& result) {
	if (result.correctAnswers != 0) {
		double proportion = static_cast<double>(result.correctAnswers) / result.questions.size();
		accuracyLbl->setText(QString::number(proportion * 100) + "%");
	}
	else accuracyLbl->setText("0%");
	correctLbl->setText(QString::number(result.correctAnswers) + " correct");
	errorsLbl->setText(QString::number(result.mistakes.size()) + " mistakes");
	//fixedLbl->setText("");
	//notFixedLbl->setText("");
	QTime totalTime = QTime::fromMSecsSinceStartOfDay(result.durationMs);
	totalTimeLbl->setText(totalTime.toString("mm:ss"));
	QTime perWordTime = QTime::fromMSecsSinceStartOfDay(result.durationMs / result.questions.size());
	perWordLbl->setText("~" + perWordTime.toString("mm:ss"));

	errorsList->clear();
	for (const ReviewQuestion& question : result.mistakes)
		errorsList->addItem(question.word.english + " - " + question.word.translation);
}