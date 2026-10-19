#pragma once
#include <QStyledItemDelegate>
#include <QPainter>

class PackItemDelegate : public QStyledItemDelegate {
public:
	PackItemDelegate(QObject* parent = nullptr);
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	//bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;
};