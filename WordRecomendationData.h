#pragma once
#include "Word.h"
#include <QDateTime>

struct WordRecomendationData {
	Word word;
	int attempts = 0;
	int errors = 0;
	QDateTime lastReviewedAt;
};