#pragma once
#include "Word.h"
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

class WordEntryWidget : public QWidget {
	Q_OBJECT
public:
	WordEntryWidget(QWidget* parent = nullptr);
	void setWord(const Word& word);
private:
	QLabel* wordLbl;
	QLineEdit* line;
signals:
	void answerSubmitted(const QString& answer);
};