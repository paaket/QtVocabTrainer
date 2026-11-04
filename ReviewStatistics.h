#pragma once
#include "ReviewQuestion.h"
#include "ReviewResult.h"
#include <QVector>
#include <QDateTime>

struct ReviewStatistics {
	QVector<ReviewQuestion> questions;
	QDateTime startedAt;
	QDateTime finishedAt;
	qint64 durationMs;
	QVector<ReviewQuestion> mistakes;
	QVector<ReviewResult> results;
	int correctAnswers;
};