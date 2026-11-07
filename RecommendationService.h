#pragma once
#include "WordRecomendationData.h"
#include "Word.h"
#include <QVector>
#include <QRandomGenerator>
#include <algorithm>
#include <cmath>

class RecommendationService {
public:
	struct CategoryAllocation {
		int newCount = 0;
		int problematicCount = 0;
		int reviewedCount = 0;
	};
	struct Category {
		int available = 0;
		int weight = 0;
		int allocated = 0;
	};
	QVector<Word> recommendWords(const QVector<WordRecomendationData>& data, int count);
private:
	static bool isProblematic(const WordRecomendationData& data);
	static CategoryAllocation allocateSlots(int totalCount, int newAvailable, int problematicAvailable, int reviewedAvailable);
	static double calculateTimeFactor(const QDateTime& lastReviewedAt);
	static double calculateFinalPriority(const WordRecomendationData& data);
};