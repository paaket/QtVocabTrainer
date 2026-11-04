#pragma once
#include "Word.h"
#include <QString>
#include <QDateTime>

struct ReviewResult {
	Word word;
	QString answer;
	bool isCorrect;
	qint64 time;
	QDateTime answeredAt;
};