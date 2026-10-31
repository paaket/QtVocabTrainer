#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QGridLayout>

class AddWordDialog : public QDialog {
	Q_OBJECT
public:
	AddWordDialog(int packId, QWidget* parent = nullptr);
signals:
	void wordSubmitted(int packId, const QString& english);
private:
	int packId;
	QLineEdit* wordLine;
};