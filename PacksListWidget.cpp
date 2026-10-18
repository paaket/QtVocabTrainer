#include "PacksListWidget.h"

PacksListWidget::PacksListWidget(QWidget* parent) : QWidget(parent) {
	PacksListModel* listModel = new PacksListModel(this);
	QListView* listView = new QListView(this);
	listView->setModel(listModel);
	
	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(listView);

	connect(listView->selectionModel(), &QItemSelectionModel::currentChanged, this, [this](const QModelIndex& current) {
			if (!current.isValid()) return;
			emit packSelected(current.data(PacksListModel::Roles::IdRole).toInt());
		}
	);
}