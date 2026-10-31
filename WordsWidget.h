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

class WordsWidget : public QWidget {
public:
	WordsWidget(DatabaseManager& dbManager, QWidget* parent = nullptr);
private:
	WordsListModel* wordModel;
	DatabaseManager& dbManager;
public slots:
	void setPackId(int packId);
	void receiveNewWord(int packId, const QString& english);
};