#include "bookingwindow.h"
#include "homewindow.h"
#include <QDebug>
#include <QQmlContext>

BookingWindow::BookingWindow(QObject *parent)
    : QObject(parent)
{
    m_view = new QQuickView();
    m_view->rootContext()->setContextProperty("bookingWindow", this);
    m_view->setSource(QUrl("qrc:/Qml/BookingPage.qml"));
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    qDebug() << "BookingWindow created at" << this;

}

BookingWindow::~BookingWindow()
{
    if (m_view) {
        m_view->close();
        m_view->deleteLater();
        m_view = nullptr;
    }
}

void BookingWindow::setRouteData(const QString &routeId, const QString &from,
                                 const QString &to, const QString &departure,
                                 const QString &arrival, const QString &price,
                                 const QString &bus, const QString &driver,
                                 const QString &phone, const QString &seats) {
    if (m_routeId != routeId) { m_routeId = routeId; emit routeIdChanged(routeId); }
    if (m_fromLocation != from) { m_fromLocation = from; emit fromLocationChanged(from); }
    if (m_toLocation != to) { m_toLocation = to; emit toLocationChanged(to); }
    if (m_departureTime != departure) { m_departureTime = departure; emit departureTimeChanged(departure); }
    if (m_arrivalTime != arrival) { m_arrivalTime = arrival; emit arrivalTimeChanged(arrival); }
    if (m_ticketPrice != price) { m_ticketPrice = price; emit ticketPriceChanged(price); }
    if (m_busNo != bus) { m_busNo = bus; emit busNoChanged(bus); }
    if (m_driverInfo != driver) { m_driverInfo = driver; emit driverInfoChanged(driver); }
    if (m_contactPhone != phone) { m_contactPhone = phone; emit contactPhoneChanged(phone); }
    if (m_seatNo != seats) { m_seatNo = seats; emit seatNoChanged(seats); }

    qDebug() << "Booking data updated in C++ object:";
    qDebug() << "Route ID:" << m_routeId << "From:" << m_fromLocation << "To:" << m_toLocation;


}

void BookingWindow::showHomeWindow()
{
    qDebug() << "showHomeWindow() called from QML. Opening HomeWindow...";
    HomeWindow *home = new HomeWindow;
    home->show();
}



void BookingWindow::payNowClicked()
{
    this->view()->hide();  // Or close()

    if (!m_paymentHandler) {
        m_paymentHandler = new PaymentHandler(this->parent());
    }
    m_paymentHandler->view()->show();

}

void BookingWindow::closeWindow() {
    if (m_view) {
        m_view->close();
    }
}
