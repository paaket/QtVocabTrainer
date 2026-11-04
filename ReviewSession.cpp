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

	qint64 answerTime = elapsedTime() - lastQuestionTime;
	QDateTime answeredAt = QDateTime::currentDateTime();
	lastQuestionTime = answerTime;
	ReviewResult result{
		word,
		answer,
		isCorrect,
		answerTime,
		answeredAt
	};
	results.push_back(result);
	if (!isCorrect) mistakes.push_back(questions[currInd]);

	return result;
}

int ReviewSession::getCurrentInd() {
	return currInd;
}

void ReviewSession::start() {
	totalTime = 0;
	startedAt = QDateTime::currentDateTime();
	timer.start();
}

void ReviewSession::finish() {
	if (timer.isValid()) {
		finishedAt = QDateTime::currentDateTime();
		totalTime = timer.elapsed();
		timer.invalidate();
	}
}

qint64 ReviewSession::elapsedTime() {
	return timer.isValid() ? timer.elapsed() : totalTime;
}

ReviewStatistics ReviewSession::getStatistics() {
	return {
		questions,
		startedAt,
		finishedAt,
		totalTime,
		mistakes,
		results,
		static_cast<int>(questions.size() - mistakes.size())
	};
}