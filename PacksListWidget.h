#pragma once
#include "PacksListModel.h"
#include "PackItemDelegate.h"
#include <QWidget>
#include <QListView>
#include <QVBoxLayout>

class PacksListWidget : public QWidget {
	Q_OBJECT
public:
	PacksListWidget(QWidget* parent = nullptr);
signals:
	void packSelected(int packId);
};