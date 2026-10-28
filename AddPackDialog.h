#pragma once
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>

class AddPackDialog : public QDialog {
	Q_OBJECT
public:
	AddPackDialog(QWidget* parent = nullptr);
private:
	QLineEdit* titleLine;
signals:
	void packSubmitted(const QString& title);
};