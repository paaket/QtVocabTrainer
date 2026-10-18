#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	NavigationWidget* navigation = new NavigationWidget(this);
	PacksListWidget* packs = new PacksListWidget(this);
	HomeWidget* home = new HomeWidget(this);
	WordsWidget* words = new WordsWidget(this);

	QStackedWidget* pages = new QStackedWidget(this);
	pages->addWidget(home);
	pages->addWidget(packs);

	QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
	splitter->addWidget(navigation);
	splitter->addWidget(pages);
	splitter->addWidget(words);

	splitter->setStretchFactor(0, 0);
	splitter->setStretchFactor(1, 1);
	splitter->setStretchFactor(2, 1);

	setCentralWidget(splitter);

	connect(navigation, &NavigationWidget::homeRequested, [pages, home]() {pages->setCurrentWidget(home); });
	connect(navigation, &NavigationWidget::packsRequested, [pages, packs]() {pages->setCurrentWidget(packs); });
	//connect(navigation, &NavigationWidget::profileRequested, [pages, ]() {pages->setCurrentWidget(); });
	//connect(navigation, &NavigationWidget::statisticRequested, [pages, ]() {pages->setCurrentWidget(); });
	//connect(navigation, &NavigationWidget::settingsRequested, [pages, ]() {pages->setCurrentWidget(); });

	connect(packs, &PacksListWidget::packSelected, words, &WordsWidget::setPackId);

	resize(800, 400);
}