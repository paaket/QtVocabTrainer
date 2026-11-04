#pragma once
#include "FourButtonsWidget.h"
#include "WordEntryWidget.h"
#include "CircleWidget.h"
#include "Word.h"
#include "ReviewSession.h"
#include "ReviewQuestion.h"
#include "ReviewResultWidget.h"
#include "DatabaseManager.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QFrame>
#include <QMessageBox>

class ReviewWidget : public QWidget {
	Q_OBJECT
public:
	ReviewWidget(DatabaseManager& dbManager, QWidget* parent = nullptr);
	void startReview(const QVector<Word>& words);
	void showNextQuestion();
private:
	WordEntryWidget* wordEntry;
	CircleWidget* circleWidget;
	QLabel* roundLbl;
	QLabel* titleLbl;
	ReviewResultWidget* reviewResWidget;
	QStackedWidget* stackedWidget;
	ReviewSession* session = nullptr;
	DatabaseManager& dbManager;
signals:
	void returnRequested();
public slots:
	void checkAnswer(const QString& answer);
};