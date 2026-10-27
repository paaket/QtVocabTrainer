#include "MainWindow.h"

MainWindow::MainWindow(DatabaseManager& db, QWidget* parent) : db(db), QMainWindow(parent) {
	NavigationWidget* navigation = new NavigationWidget(this);
	PacksListWidget* packs = new PacksListWidget(db, this);
	HomeWidget* home = new HomeWidget(this);
	WordsWidget* words = new WordsWidget(db, this);
	ProfileWidget* profile = new ProfileWidget(this);
	SettingsWidget* settings = new SettingsWidget(this);

	QStackedWidget* pages = new QStackedWidget(this);
	pages->addWidget(home);
	pages->addWidget(packs);
	pages->addWidget(profile);
	pages->addWidget(settings);

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
	connect(navigation, &NavigationWidget::profileRequested, [pages, profile]() {pages->setCurrentWidget(profile); });
	//connect(navigation, &NavigationWidget::statisticRequested, [pages, ]() {pages->setCurrentWidget(); });
	connect(navigation, &NavigationWidget::settingsRequested, [pages, settings]() {pages->setCurrentWidget(settings); });

	connect(packs, &PacksListWidget::packSelected, words, &WordsWidget::setPackId);
	connect(packs, &PacksListWidget::newWordReceived, words, &WordsWidget::receiveNewWord);

	connect(settings, &SettingsWidget::LogoutRequested, this, [this]() {
		QSettings settings("paket", "QtVocabTrainer");
		settings.setValue("auth/remember", false);
		settings.remove("user/id");
		settings.remove("user/username");
		settings.remove("user/created_at");

		this->close();
	});

	resize(800, 400);
}