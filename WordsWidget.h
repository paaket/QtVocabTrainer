#pragma once
#include "WordsListModel.h"
#include <QWidget>
#include <QListView>
#include <QVBoxLayout>

class WordsWidget : public QWidget {
public:
	WordsWidget(QWidget* parent = nullptr);
private:
	WordsListModel* wordModel;
public slots:
	void setPackId(int packId);
};