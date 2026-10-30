#pragma once
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSettings>

class DeleteAccountDialog : public QDialog {
	Q_OBJECT
public:
	DeleteAccountDialog(QWidget* parent = nullptr);
private:
	QLineEdit* line;
signals:
	void DeleteAccountRequested();
};