#pragma once
#include "Word.h"
#include "ReviewQuestion.h"
#include "ReviewResult.h"
#include <QRandomGenerator>
#include <algorithm>

class ReviewSession {
public:
	ReviewSession(const QVector<Word>& words);
	ReviewQuestion getReviewQuestion();
	bool isFinished();
	ReviewResult submitAnswer(const QString& answer);
	int getCurrentInd();
private:
	QVector<ReviewQuestion> questions;
	QVector<ReviewResult> results;
	QVector<ReviewQuestion> mistakes;
	int currInd = -1;
};