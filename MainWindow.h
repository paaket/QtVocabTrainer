#pragma once
#include "NavigationWidget.h"
#include "PacksListWidget.h"
#include "HomeWidget.h"
#include "WordsWidget.h"
#include "DatabaseManager.h"
#include "ProfileWidget.h"
#include "SettingsWidget.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QListView>
#include <QSplitter>
#include <QSettings>

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(DatabaseManager& db, QWidget* parent = nullptr);
private:
	DatabaseManager& db;
};