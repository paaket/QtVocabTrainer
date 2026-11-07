#pragma once
#include "WordsListModel.h"
#include "DatabaseManager.h"
#include "Word.h"
#include "WordItemDelegate.h"
#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QSettings>
#include <QMessageBox>
#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QFont>
#include <QFrame>

class WordsWidget : public QWidget {
	Q_OBJECT
public:
	WordsWidget(DatabaseManager& dbManager, QWidget* parent = nullptr);
	QVector<Word> getWords();
private:
	QLabel* wordsNumLbl;
	WordsListModel* wordModel;
	DatabaseManager& dbManager;
public slots:
	void setPackId(int packId);
	void receiveNewWord(int packId, const QString& english);
signals:
	void startReviewClicked();
};