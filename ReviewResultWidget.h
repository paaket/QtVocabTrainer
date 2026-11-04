#pragma once
#include "ReviewStatistics.h"
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QPalette>
#include <QFont>
#include <QColor>
#include <QFrame>

class ReviewResultWidget : public QWidget {
	Q_OBJECT
public:
	ReviewResultWidget(QWidget* parent = nullptr);
	void setStatistics(const ReviewStatistics& result);
private:
	QLabel* accuracyLbl;
	QLabel* correctLbl;
	QLabel* errorsLbl;
	QLabel* fixedLbl;
	QLabel* notFixedLbl;
	QLabel* totalTimeLbl;
	QLabel* perWordLbl;
	QListWidget* errorsList;
signals:
	void retutnClicked();
};