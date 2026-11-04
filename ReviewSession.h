#pragma once
#include "Word.h"
#include "ReviewQuestion.h"
#include "ReviewResult.h"
#include "ReviewStatistics.h"
#include <QElapsedTimer>
#include <QRandomGenerator>
#include <QDateTime>
#include <algorithm>

class ReviewSession {
public:
	ReviewSession(const QVector<Word>& words);
	ReviewQuestion getReviewQuestion();
	bool isFinished();
	ReviewResult submitAnswer(const QString& answer);
	int getCurrentInd();
	void start();
	void finish();
	qint64 elapsedTime();
	ReviewStatistics getStatistics();
private:
	QElapsedTimer timer;
	qint64 lastQuestionTime = 0;
	qint64 totalTime = 0;
	QDateTime startedAt;
	QDateTime finishedAt;
	QVector<ReviewQuestion> questions;
	QVector<ReviewResult> results;
	QVector<ReviewQuestion> mistakes;
	int currInd = -1;
};