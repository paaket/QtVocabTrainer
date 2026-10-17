#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	PacksListModel* packsModel = new PacksListModel(this);
	QListView* packsView = new QListView(this);
	packsView->setModel(packsModel);

	

	QStackedWidget* pages = new QStackedWidget(this);

	resize(750, 600);
}