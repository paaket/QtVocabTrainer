#include "RecommendationService.h"

bool RecommendationService::isProblematic(const WordRecomendationData& data) {
	int minAttempts = 2;
	double errorThreshold = 0.75;

	if (data.attempts < minAttempts) return false;

	double errorRate = static_cast<double>(data.errors) / data.attempts;

	return errorRate >= errorThreshold;
}

double RecommendationService::calculateTimeFactor(const QDateTime& lastReviewedAt, const QDateTime& now) {
    if (!lastReviewedAt.isValid())
        return 1.0;

    constexpr double maxIncrease = 0.5;
    constexpr double timeConstantDays = 3.0;
    qint64 elapsedSeconds = lastReviewedAt.secsTo(now);
    double elapsedDays = elapsedSeconds / 86400.0;
    elapsedDays = std::max(0.0, elapsedDays);

    return 1.0 + maxIncrease * (1.0 - std::exp(-elapsedDays / timeConstantDays));
}

double RecommendationService::calculateFinalPriority(const WordRecomendationData& data, const QDateTime& now) {
    double basePriority = static_cast<double>(data.errors) * data.errors / data.attempts;

    return basePriority * calculateTimeFactor(data.lastReviewedAt, now);
}

RecommendationService::CategoryAllocation RecommendationService::allocateSlots(
	int totalCount,
	int newAvailable,
	int problematicAvailable,
	int reviewedAvailable) 
{
    Category categories[] = {
        { newAvailable, 5, 0 },
        { problematicAvailable, 3, 0 },
        { reviewedAvailable, 1, 0 }
    };

    int totalAvailable =
        newAvailable + problematicAvailable + reviewedAvailable;
    int remaining = std::min(totalCount, totalAvailable);

    while (remaining > 0) {
        int totalWeight = 0;
        for (const auto& category : categories) {
            if (category.allocated < category.available)
                totalWeight += category.weight;
        }
        if (totalWeight == 0) break;

        int allocatedThisRound = 0;
        struct Remainder {
            int index;
            int value;
        };
        QVector<Remainder> remainders;

        for (int i = 0; i < 3; ++i) {
            Category& category = categories[i];

            if (category.allocated >= category.available)
                continue;

            int numerator = remaining * category.weight;
            int quota = numerator / totalWeight;
            int remainder = numerator % totalWeight;
            int capacity = category.available - category.allocated;
            int actual = std::min(quota, capacity);
            category.allocated += actual;
            allocatedThisRound += actual;

            if (category.allocated < category.available) {
                remainders.push_back({ i, remainder });
            }
        }

        remaining -= allocatedThisRound;
        if (remaining == 0)
            break;

        std::sort(
            remainders.begin(),
            remainders.end(),
            [](const Remainder& a, const Remainder& b) {
                return a.value > b.value;
            }
        );

        int extraAllocated = 0;
        for (const Remainder& remainder : remainders) {
            if (remaining == 0)
                break;

            Category& category = categories[remainder.index];

            if (category.allocated >= category.available)
                continue;

            ++category.allocated;
            --remaining;
            ++extraAllocated;
        }

        if (allocatedThisRound == 0 && extraAllocated == 0)
            break;
    }

    return {
        categories[0].allocated,
        categories[1].allocated,
        categories[2].allocated
    };
}

QVector<Word> RecommendationService::recommendWords(const QVector<WordRecomendationData>& data, int count) {
	QVector<WordRecomendationData> problematic;
	QVector<WordRecomendationData> newWords;
	QVector<WordRecomendationData> reviewed;

	for (const WordRecomendationData& recData : data) {
		if (recData.attempts == 0) {
			newWords.push_back(recData);
		}
        else if (isProblematic(recData)) {
			problematic.push_back(recData);
		}
		else {
			reviewed.push_back(recData);
		}
	}

    QDateTime now = QDateTime::currentDateTime();
	std::sort(problematic.begin(), problematic.end(), [&now](const WordRecomendationData& first, const WordRecomendationData& second) {
		double priorityFirst = calculateFinalPriority(first, now);
        double prioritySecond = calculateFinalPriority(second, now);

		if (priorityFirst != prioritySecond)
			return priorityFirst > prioritySecond;

		double rateFirst = static_cast<double>(first.errors) / first.attempts;
		double rateSecond = static_cast<double>(second.errors) / second.attempts;

		if (rateFirst != rateSecond)
			return rateFirst > rateSecond;

        if (first.attempts != second.attempts)
            return first.attempts < second.attempts;

		return first.lastReviewedAt < second.lastReviewedAt;
	});

    std::shuffle(newWords.begin(), newWords.end(), *QRandomGenerator::global());

    std::shuffle(reviewed.begin(), reviewed.end(), *QRandomGenerator::global());
    std::stable_sort(reviewed.begin(), reviewed.end(), [](const WordRecomendationData& first, const WordRecomendationData& second) {
        return first.lastReviewedAt < second.lastReviewedAt;
    });

    CategoryAllocation allocation = allocateSlots(count, newWords.size(), problematic.size(), reviewed.size());

    QVector<Word> result;
    for (int i = 0; i < allocation.newCount; ++i)
        result.push_back(newWords[i].word);

    for (int i = 0; i < allocation.problematicCount; ++i)
        result.push_back(problematic[i].word);

    for (int i = 0; i < allocation.reviewedCount; ++i)
        result.push_back(reviewed[i].word);

    return result;
}