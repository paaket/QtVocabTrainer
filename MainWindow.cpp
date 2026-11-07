#include "MainWindow.h"

MainWindow::MainWindow(DatabaseManager& db, RecommendationService& recService, QWidget* parent) : db(db), recService(recService), QMainWindow(parent) {
	NavigationWidget* navigation = new NavigationWidget(this);
	PacksListWidget* packs = new PacksListWidget(db, this);
	HomeWidget* home = new HomeWidget(this);
	WordsWidget* words = new WordsWidget(db, this);
	ProfileWidget* profile = new ProfileWidget(this);
	SettingsWidget* settings = new SettingsWidget(this);
	ReviewWidget* review = new ReviewWidget(db, recService, this);
	EmptyWidget* emptyWidget = new EmptyWidget(this);

	QStackedWidget* menuPages = new QStackedWidget(this);
	menuPages->addWidget(home);
	menuPages->addWidget(packs);
	menuPages->addWidget(profile);
	menuPages->addWidget(settings);

	QStackedWidget* wordsPages = new QStackedWidget(this);
	wordsPages->addWidget(emptyWidget);
	wordsPages->addWidget(words);
	wordsPages->addWidget(review);

	QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
	splitter->addWidget(navigation);
	splitter->addWidget(menuPages);
	splitter->addWidget(wordsPages);

	splitter->setStretchFactor(0, 0);
	splitter->setStretchFactor(1, 1);
	splitter->setStretchFactor(2, 1);

	setCentralWidget(splitter);

	connect(navigation, &NavigationWidget::homeRequested, [menuPages, home]() {menuPages->setCurrentWidget(home); });
	connect(navigation, &NavigationWidget::packsRequested, [menuPages, packs]() {menuPages->setCurrentWidget(packs); });
	connect(navigation, &NavigationWidget::profileRequested, [menuPages, profile]() {menuPages->setCurrentWidget(profile); });
	//connect(navigation, &NavigationWidget::statisticRequested, [menuPages, ]() {menuPages->setCurrentWidget(); });
	connect(navigation, &NavigationWidget::settingsRequested, [menuPages, settings]() {menuPages->setCurrentWidget(settings); });

	connect(packs, &PacksListWidget::packSelected, words, &WordsWidget::setPackId);
	connect(packs, &PacksListWidget::packSelected, [wordsPages, words]() {wordsPages->setCurrentWidget(words); });
	connect(packs, &PacksListWidget::newWordReceived, words, &WordsWidget::receiveNewWord);

	connect(profile, &ProfileWidget::LogoutRequested, this, [this]() {
		QSettings settings("paket", "QtVocabTrainer");
		settings.setValue("auth/remember", false);
		settings.remove("user/id");
		settings.remove("user/username");
		settings.remove("user/created_at");

		this->close();
	});
	connect(settings, &SettingsWidget::DeleteAccountRequested, this, [this, &db]() {
		QSettings settings("paket", "QtVocabTrainer");

		db.deleteAccount(settings.value("user/id").toInt());

		settings.setValue("auth/remember", false);
		settings.remove("user/id");
		settings.remove("user/username");
		settings.remove("user/created_at");

		this->close();
	});
	connect(words, &WordsWidget::startReviewClicked, this, [wordsPages, review, words]() { 
		review->startReview(words->getWords());
		wordsPages->setCurrentWidget(review); 
	});
	connect(review, &ReviewWidget::returnRequested, this, [wordsPages, words]() { wordsPages->setCurrentWidget(words); });

	resize(800, 400);
}