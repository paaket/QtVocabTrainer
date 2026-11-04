#pragma once
#include "WordRecomendationData.h"
#include "Word.h"
#include <QVector>

class RecommendationService {
public:
	RecommendationService();
	QVector<Word> recommendWords(const QVector<WordRecomendationData>& data, int count);
};