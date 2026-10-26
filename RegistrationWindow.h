#pragma once
#include "DatabaseManager.h"
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

class RegistrationWindow : public QDialog {
public:
	RegistrationWindow(DatabaseManager& dbManager, QWidget* parent = nullptr);
private:
	QLineEdit* loginLine;
	QLineEdit* passwordLine;
	QLineEdit* repPasswordLine;
	DatabaseManager& dbManager;
};