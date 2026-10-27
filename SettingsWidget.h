#pragma once
#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QPushButton>

class SettingsWidget : public QWidget {
	Q_OBJECT
public:
	SettingsWidget(QWidget* parent = nullptr);
signals:
	void LogoutRequested();
};