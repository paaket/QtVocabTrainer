#pragma once
#include <QWidget>
#include <QLabel>
#include <QPUshButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFont>
#include <QPalette>

class FourButtonsWidget : public QWidget {
	Q_OBJECT
public:
	FourButtonsWidget(QWidget* parent = nullptr);
signals:
	void answerSelected(const QString& answer);
};