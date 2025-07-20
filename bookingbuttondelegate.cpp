#include "BookingButtonDelegate.h"
#include <QApplication>
#include <QStyleOptionButton>
#include <QStyle>
#include <QDebug>
#include <QtGui/qevent.h>

BookingButtonDelegate::BookingButtonDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void BookingButtonDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const {
    QStyleOptionButton button;
    button.rect = option.rect;
    button.text = "Book";
    button.state = QStyle::State_Enabled;

    QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
}

bool BookingButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                        const QStyleOptionViewItem &option, const QModelIndex &index) {
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (option.rect.contains(mouseEvent->pos())) {
            emit bookButtonClicked(index);
        }
    }
    return true;
}
