#pragma once
#include <QWidget>
#include <QSettings>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QDateTime>
#include <QPushButton>

class ProfileWidget : public QWidget {
	Q_OBJECT
public:
	ProfileWidget(QWidget* parent = nullptr);
signals:
	void LogoutRequested();
};