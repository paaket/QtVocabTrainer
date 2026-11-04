#include "ReviewWidget.h"

ReviewWidget::ReviewWidget(DatabaseManager& dbManager, QWidget* parent) : QWidget(parent), dbManager(dbManager) {
	titleLbl = new QLabel("Repetition of words", this);
	roundLbl = new QLabel("Round 1/10", this);

	circleWidget = new CircleWidget(this);
	wordEntry = new WordEntryWidget(this);
	reviewResWidget = new ReviewResultWidget(this);

	stackedWidget = new QStackedWidget();
	stackedWidget->addWidget(wordEntry);
	stackedWidget->addWidget(reviewResWidget);

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
	connect(reviewResWidget, &ReviewResultWidget::retutnClicked, this, [this]() {
		emit returnRequested();
		stackedWidget->setCurrentWidget(wordEntry);
		circleWidget->resetCirclies();
	});
}

void ReviewWidget::startReview(const QVector<Word>& words) {
	delete session;
	session = new ReviewSession(words);

	ReviewQuestion question = session->getReviewQuestion();
	wordEntry->setWord(question.word);
	session->start();
}

void ReviewWidget::checkAnswer(const QString& answer) {
	ReviewResult result = session->submitAnswer(answer);

	if (result.isCorrect) circleWidget->colorCircle(session->getCurrentInd(), Qt::green);
	else circleWidget->colorCircle(session->getCurrentInd(), Qt::red);
	showNextQuestion();
}

void ReviewWidget::showNextQuestion() {
	if (session->isFinished()) {
		session->finish();
		titleLbl->setText("Repetition complete!");
		roundLbl->setText("");
		reviewResWidget->setStatistics(session->getStatistics());
		stackedWidget->setCurrentWidget(reviewResWidget);

		auto res = dbManager.saveReviewSession(session->getStatistics());
		if (!res.isSuccess) QMessageBox::critical(this, "Critical error", res.error);

		return;
	}
	ReviewQuestion question = session->getReviewQuestion();
	wordEntry->setWord(question.word);
	roundLbl->setText("Round " + QString::number(session->getCurrentInd() + 1) + "/10");
}