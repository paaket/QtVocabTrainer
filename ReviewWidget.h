#pragma once
#include "FourButtonsWidget.h"
#include "WordEntryWidget.h"
#include "CircleWidget.h"
#include "Word.h"
#include "ReviewSession.h"
#include "ReviewQuestion.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QFrame>

class ReviewWidget : public QWidget {
	Q_OBJECT
public:
	ReviewWidget(QWidget* parent = nullptr);
	void startReview(const QVector<Word>& words);
	void showNextQuestion();
private:
	WordEntryWidget* wordEntry;
	CircleWidget* circleWidget;
	QLabel* roundLbl;
	ReviewSession* session = nullptr;
public slots:
	void checkAnswer(const QString& answer);
};