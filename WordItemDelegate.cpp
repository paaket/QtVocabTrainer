#include "WordItemDelegate.h"

WordItemDelegate::WordItemDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

void WordItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	QStyledItemDelegate::paint(painter, option, index);

	if (option.state & QStyle::State_Selected) {
		const QRect delButtonRect(
			option.rect.right() - 30,
			option.rect.center().y() - 10,
			20,
			20
		);

		painter->save();

		painter->setPen(Qt::gray);
		painter->drawRoundedRect(delButtonRect, 1, 1);
		painter->setPen(Qt::black);
		painter->drawText(delButtonRect, Qt::AlignCenter, "x");

		painter->restore();
	}
}

bool WordItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) {
	if (event->type() == QEvent::MouseButtonPress) {
		QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
		if (mouseEvent->buttons() == Qt::LeftButton) {
			const QRect delButtonRect(
				option.rect.right() - 30,
				option.rect.center().y() - 10,
				20,
				20
			);
			if (delButtonRect.contains(mouseEvent->position().toPoint())) {
				emit delWordRequested(index.data(WordsListModel::Roles::IdRole).toInt());
				return true;
			}
		}
	}
	return false;
}