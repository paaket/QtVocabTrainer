#include "PacksListWidget.h"

PacksListWidget::PacksListWidget(DatabaseManager& dbManager, QWidget* parent) : QWidget(parent), dbManager(dbManager) {
	PacksListModel* listModel = new PacksListModel(this);
	QListView* listView = new QListView(this);
	PackItemDelegate* delegate = new PackItemDelegate(listView);
	listView->setModel(listModel);
	listView->setItemDelegate(delegate);
	
	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(listView);

	listModel->setPacks(dbManager.loadUserPacks(1)); //user_id from qsettings

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
}