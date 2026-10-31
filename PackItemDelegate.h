#pragma once
#include "PacksListModel.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include <QMouseEvent>

class PackItemDelegate : public QStyledItemDelegate {
	Q_OBJECT
public:
	PackItemDelegate(QObject* parent = nullptr);
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;
signals:
	void addWordRequested(int packId);
	void delPackRequested(int packId);
};