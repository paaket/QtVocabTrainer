#include "ReviewSession.h"

ReviewSession::ReviewSession(const QVector<Word>& words) {
	QVector<Word> wordsCopy = words;
	std::shuffle(wordsCopy.begin(), wordsCopy.end(), *QRandomGenerator::global());
	QVector<Word> selectedWords = wordsCopy.mid(0, 10);

	for (const Word& word : selectedWords)
		questions.append({ word });
}

ReviewQuestion ReviewSession::getReviewQuestion() {
	currInd++;
	return questions[currInd];
}

bool ReviewSession::isFinished() {
	return currInd == questions.size() - 1;
}

ReviewResult ReviewSession::submitAnswer(const QString& answer) {
	const Word& word = questions[currInd].word;
	const bool isCorrect = answer.compare(word.translation, Qt::CaseInsensitive) == 0 ? true : false;

	ReviewResult result{
		word.id,
		answer,
		isCorrect
	};
	results.push_back(result);
	if (!isCorrect) mistakes.push_back(questions[currInd]);

	return result;
}

int ReviewSession::getCurrentInd() {
	return currInd;
}