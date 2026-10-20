#include "PackItemDelegate.h"

PackItemDelegate::PackItemDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

void PackItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	QStyledItemDelegate::paint(painter, option, index);

    if (option.state & QStyle::State_Selected) {
        const QRect buttonRect(
            option.rect.right() - 30,
            option.rect.center().y() - 10,
            20,
            20
        );
        painter->save();
        painter->setPen(Qt::gray);
        painter->drawRoundedRect(buttonRect, 1, 1);
        painter->setPen(Qt::black);
        painter->drawText(buttonRect, Qt::AlignCenter, "+");
        painter->restore();
    }
}

bool PackItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            const QRect buttonRect(
                option.rect.right() - 30,
                option.rect.center().y() - 10,
                20,
                20
            );
            if (buttonRect.contains(mouseEvent->position().toPoint())) {
                emit addWordRequested(index.data(PacksListModel::Roles::IdRole).toInt());
                return true;
            }
        }
    }
    return false;
}