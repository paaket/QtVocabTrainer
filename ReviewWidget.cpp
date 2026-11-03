#include "ReviewWidget.h"

ReviewWidget::ReviewWidget(QWidget* parent) : QWidget(parent) {
	QLabel* titleLbl = new QLabel("Repetition of words", this);
	roundLbl = new QLabel("Round 1/10", this);

	circleWidget = new CircleWidget(this);
	wordEntry = new WordEntryWidget(this);

	QStackedWidget* stackedWidget = new QStackedWidget();
	stackedWidget->addWidget(wordEntry);

	QGridLayout* grid = new QGridLayout();
	grid->addWidget(titleLbl, 0, 0, Qt::AlignLeft);
	grid->addWidget(roundLbl, 0, 1, Qt::AlignRight);
	grid->addWidget(circleWidget, 1, 0, 1, 2, Qt::AlignHCenter | Qt::AlignTop);

	QVBoxLayout* vbox = new QVBoxLayout();
	vbox->addLayout(grid);
	vbox->addWidget(stackedWidget);

	QFrame* frame = new QFrame(this);
	frame->setFrameShape(QFrame::StyledPanel);
	frame->setFrameShadow(QFrame::Sunken);

	QVBoxLayout* frameVbox = new QVBoxLayout(frame);
	frameVbox->addLayout(vbox);

	QVBoxLayout* mainVbox = new QVBoxLayout(this);
	mainVbox->addWidget(frame);

	connect(wordEntry, &WordEntryWidget::answerSubmitted, this, &ReviewWidget::checkAnswer);
}

void ReviewWidget::startReview(const QVector<Word>& words) {
	delete session;
	session = new ReviewSession(words);

	ReviewQuestion question = session->getReviewQuestion();
	wordEntry->setWord(question.word);
}

void ReviewWidget::checkAnswer(const QString& answer) {
	ReviewResult result = session->submitAnswer(answer);

	if (result.isCorrect) {
		//show yspeh
		circleWidget->colorCircle(session->getCurrentInd(), Qt::green);
	}
	else {
		circleWidget->colorCircle(session->getCurrentInd(), Qt::red);
		//show translation, transcription, ...
	}
	showNextQuestion();
}

void ReviewWidget::showNextQuestion() {
	if (session->isFinished()) {
		//show session result
		return;
	}
	ReviewQuestion question = session->getReviewQuestion();
	wordEntry->setWord(question.word);
	roundLbl->setText("Round " + QString::number(session->getCurrentInd() + 1) + "/10");
}