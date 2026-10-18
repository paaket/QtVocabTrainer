#pragma once
#include "NavigationWidget.h"
#include "PacksListWidget.h"
#include "HomeWidget.h"
#include "WordsWidget.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QListView>
#include <QSplitter>

class MainWindow : public QMainWindow {
public:
	MainWindow(QWidget* parent = nullptr);
};