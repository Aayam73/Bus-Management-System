#ifndef BOOKINGBUTTONDELEGATE_H
#define BOOKINGBUTTONDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QMouseEvent>

class BookingButtonDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit BookingButtonDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) override;

signals:
    void bookButtonClicked(const QModelIndex &index) const;
};


#endif // BOOKINGBUTTONDELEGATE_H
