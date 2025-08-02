#include "accountwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QQmlContext>

AccountWindow::AccountWindow(QObject *parent, const QString &username)
    : QObject(parent), m_username(username)
{
}

QString AccountWindow::username() const { return m_username; }
void AccountWindow::setUsername(const QString &username)
{
    if (m_username != username) {
        m_username = username;
        qDebug() << "C++ Set - Username:" << m_username;
        emit usernameChanged();
        loadUserData();
    }
}

QString AccountWindow::phone() const { return m_phone; }
void AccountWindow::setPhone(const QString &phone)
{
    if (m_phone != phone) {
        m_phone = phone;
        qDebug() << "C++ Set - Phone:" << m_phone;
        emit phoneChanged();
    }
}

QString AccountWindow::email() const { return m_email; }
void AccountWindow::setEmail(const QString &email)
{
    if (m_email != email) {
        m_email = email;
        qDebug() << "C++ Set - Email:" << m_email;
        emit emailChanged();
    }
}

QString AccountWindow::address() const { return m_address; }
void AccountWindow::setAddress(const QString &address)
{
    if (m_address != address) {
        m_address = address;
        qDebug() << "C++ Set - Address:" << m_address;
        emit addressChanged();
    }
}

QString AccountWindow::profilePic() const { return m_profilePic; }
void AccountWindow::setProfilePic(const QString &profilePic)
{
    if (m_profilePic != profilePic) {
        m_profilePic = profilePic;
        qDebug() << "C++ Set - Profile Pic:" << (m_profilePic.isEmpty() ? "[EMPTY]" : "[IMAGE DATA]");
        emit profilePicChanged();
    }
}

void AccountWindow::loadUserData()
{
    if (m_username.isEmpty()) {
        qWarning() << "Username not set, cannot load user data.";
        return;
    }

    QSqlDatabase db = QSqlDatabase::database("main");
    if (!db.isOpen()) {
        qWarning() << "Database is not open in loadUserData!";
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT phone, email, address, profile_pic FROM users WHERE username = :username");
    query.bindValue(":username", m_username);

    if (query.exec() && query.next()) {
        m_phone = query.value(0).toString();
        m_email = query.value(1).toString();
        m_address = query.value(2).toString();

        QByteArray imageData = query.value(3).toByteArray();
        if (!imageData.isEmpty()) {
            m_profilePic = QString("data:image/png;base64,%1").arg(QString(imageData.toBase64()));
        } else {
            m_profilePic.clear();
        }

        qDebug() << "C++ Set - Profile Pic:" << (m_profilePic.isEmpty() ? "[EMPTY]" : "[IMAGE DATA]");

        emit phoneChanged();
        emit emailChanged();
        emit addressChanged();
        emit profilePicChanged();

        qDebug() << "Loaded data for username:" << m_username;
    } else {
        qWarning() << "Failed to load user data:" << query.lastError().text();
    }
}

bool AccountWindow::updateUserData()
{
    if (m_username.isEmpty()) {
        qWarning() << "Username not set, cannot update user data.";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database("main");
    if (!db.isOpen()) {
        qWarning() << "Database not open in updateUserData!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE users SET phone = :phone, email = :email, address = :address, profile_pic = :profilePic WHERE username = :username");
    query.bindValue(":phone", m_phone);
    query.bindValue(":email", m_email);
    query.bindValue(":address", m_address);

    if (m_profilePic.startsWith("data:image")) {
        QString base64Data = m_profilePic.section(',', 1);
        query.bindValue(":profilePic", QByteArray::fromBase64(base64Data.toUtf8()));
    } else {
        query.bindValue(":profilePic", QByteArray());
    }

    query.bindValue(":username", m_username);

    if (query.exec()) {
        qDebug() << "User data updated for username:" << m_username;
        return true;
    } else {
        qWarning() << "Failed to update user data:" << query.lastError().text();
        return false;
    }
}

void AccountWindow::openFileSelectionDialog()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr,
                                                    tr("Select Profile Picture"), QDir::homePath(),
                                                    tr("Image Files (*.png *.jpg *.jpeg)"));

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray imageData = file.readAll();
            file.close();

            QString base64Data = QString("data:image/png;base64,%1").arg(QString(imageData.toBase64()));
            setProfilePic(base64Data);
            updateUserData();
        } else {
            qWarning() << "Failed to open file:" << file.errorString();
        }
    }
}
