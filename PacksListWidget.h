#pragma once
#include "PacksListModel.h"
#include "PackItemDelegate.h"
#include "AddWordDialog.h"
#include "WordsListModel.h"
#include "DatabaseManager.h"
#include "AddPackDialog.h"
#include "WordPack.h"
#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QSettings>
#include <QSettings>
#include <QMessageBox>

class PacksListWidget : public QWidget {
	Q_OBJECT
public:
	PacksListWidget(DatabaseManager& dbManager, QWidget* parent = nullptr);
	void receiveNewPack(const QString& title);
private:
	PacksListModel* listModel;
	DatabaseManager& dbManager;
signals:
	void packSelected(int packId);
	void newWordReceived(int packId, const QString& english);
	void delPackRequested(int packId);
};