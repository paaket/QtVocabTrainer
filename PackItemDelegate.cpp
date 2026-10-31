#include "PackItemDelegate.h"

PackItemDelegate::PackItemDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

void PackItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
	QStyledItemDelegate::paint(painter, option, index);

    if (option.state & QStyle::State_Selected) {
        const QRect addButtonRect(
            option.rect.right() - 60,
            option.rect.center().y() - 10,
            20,
            20
        );
        const QRect delBtnRect(
            option.rect.right() - 30,
            option.rect.center().y() - 10,
            20,
            20
        );

        painter->save();

        painter->setPen(Qt::gray);
        painter->drawRoundedRect(addButtonRect, 1, 1);
        painter->drawRoundedRect(delBtnRect, 1, 1);
        painter->setPen(Qt::black);
        painter->drawText(addButtonRect, Qt::AlignCenter, "+");
        painter->drawText(delBtnRect, Qt::AlignCenter, "x");

        painter->restore();
    }
}

bool PackItemDelegate::editorEvent(QEvent* event, QAbstractItemModel* model, const QStyleOptionViewItem& option, const QModelIndex& index) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            const QRect addButtonRect(
                option.rect.right() - 60,
                option.rect.center().y() - 10,
                20,
                20
            );
            const QRect delBtnRect(
                option.rect.right() - 30,
                option.rect.center().y() - 10,
                20,
                20
            );
            if (addButtonRect.contains(mouseEvent->position().toPoint())) {
                emit addWordRequested(index.data(PacksListModel::Roles::IdRole).toInt());
                return true;
            }
            if (delBtnRect.contains(mouseEvent->position().toPoint())) {
                emit delPackRequested(index.data(PacksListModel::Roles::IdRole).toInt());
                return true;
            }
        }
    }
    return false;
}