#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>

class NavigationWidget : public QWidget {
	Q_OBJECT
public:
	NavigationWidget(QWidget* parent = nullptr);
private:
	int btnHeight = 50;
	int btnWidth = 50;
signals:
	void homeRequested();
	void packsRequested();
	void profileRequested();
	void statisticRequested();
	void settingsRequested();
};