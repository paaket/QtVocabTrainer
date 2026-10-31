#pragma once
#include "WordsListModel.h"
#include <QStyledItemDelegate>
#include <QPainter>
#include <QMouseEvent>

class WordItemDelegate : public QStyledItemDelegate {
	Q_OBJECT
public:
	WordItemDelegate(QObject* parent = nullptr);
	virtual void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	virtual bool editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) override;
signals:
	void delWordRequested(int wordId);
};