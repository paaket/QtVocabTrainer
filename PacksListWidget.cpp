#include "PacksListWidget.h"

PacksListWidget::PacksListWidget(DatabaseManager& dbManager, QWidget* parent) : QWidget(parent), dbManager(dbManager) {
	listModel = new PacksListModel(this);
	QListView* listView = new QListView(this);
	PackItemDelegate* delegate = new PackItemDelegate(listView);
	listView->setModel(listModel);
	listView->setItemDelegate(delegate);

	QPushButton* addPackBtn = new QPushButton("Add pack", this);
	
	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(listView);
	vbox->addWidget(addPackBtn);

	QSettings settings("paket", "QtVocabTrainer");
	auto res = dbManager.loadUserPacks(settings.value("user/id").toInt());
	if (!res.isSuccess) QMessageBox::critical(this, "Critical error", res.error);
	else listModel->setPacks(res.data.value<QVector<WordPack>>());

	connect(listView->selectionModel(), &QItemSelectionModel::currentChanged, this, [this](const QModelIndex& current) {
			if (!current.isValid()) return;
			emit packSelected(current.data(PacksListModel::Roles::IdRole).toInt());
		}
	);
	connect(delegate, &PackItemDelegate::addWordRequested, this, [this](int packId) {
			AddWordDialog* dialog = new AddWordDialog(packId, this);
			connect(dialog, &AddWordDialog::wordSubmitted, this, [this](int packId, const QString& english) {
					emit newWordReceived(packId, english);
				}
			);
			dialog->exec();
		}
	);
	connect(addPackBtn, &QPushButton::clicked, this, [dbManager, this]() {
		AddPackDialog* dialog = new AddPackDialog(this);
		connect(dialog, &AddPackDialog::packSubmitted, this, &PacksListWidget::receiveNewPack);
		dialog->exec();
	});
}

void PacksListWidget::receiveNewPack(const QString& title) {
	QSettings settings("paket", "QtVocabTrainer");
	auto res = dbManager.addPack(settings.value("user/id").toInt(), title);
	if (!res.isSuccess) QMessageBox::critical(this, "Critical error", res.error);
	listModel->insertPack(res.data.toMap()["id"].toInt(), title, res.data.toMap()["created_at"].toDateTime());
}