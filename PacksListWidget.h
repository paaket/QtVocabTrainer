#pragma once
#include "PacksListModel.h"
#include "PackItemDelegate.h"
#include "AddWordDialog.h"
#include "WordsListModel.h"
#include "DatabaseManager.h"
#include <QWidget>
#include <QListView>
#include <QVBoxLayout>

class PacksListWidget : public QWidget {
	Q_OBJECT
public:
	PacksListWidget(DatabaseManager& dbManager, QWidget* parent = nullptr);
private:
	DatabaseManager& dbManager;
signals:
	void packSelected(int packId);
	void newWordReceived(int packId, const QString& english);
};