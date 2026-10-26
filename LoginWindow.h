#pragma once
#include "RegistrationWindow.h"
#include "DatabaseManager.h"
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSettings>

class LoginWindow : public QDialog {
public:
	LoginWindow(DatabaseManager& dbManager, QWidget* parent = nullptr);
private:
	QLineEdit* loginLine;
	QLineEdit* passwordLine;
	DatabaseManager& dbManager;
};