#ifndef ACCOUNTWINDOW_H
#define ACCOUNTWINDOW_H

#include <QObject>
#include <QQuickView>

class AccountWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString profilePic READ profilePic WRITE setProfilePic NOTIFY profilePicChanged)

public:
    explicit AccountWindow(QObject *parent = nullptr, const QString &username = "");
    QString username() const;
    void setUsername(const QString &username);

    QString phone() const;
    void setPhone(const QString &phone);

    QString email() const;
    void setEmail(const QString &email);

    QString address() const;
    void setAddress(const QString &address);

    QString profilePic() const;
    void setProfilePic(const QString &profilePic);

    Q_INVOKABLE bool updateUserData();
    void loadUserData();
    Q_INVOKABLE void openFileSelectionDialog();
    QQuickView* view() const;

signals:
    void usernameChanged();
    void phoneChanged();
    void emailChanged();
    void addressChanged();
    void profilePicChanged();

private:
    QString m_username;
    QString m_phone;
    QString m_email;
    QString m_address;
    QString m_profilePic;

    QQuickView *m_view = nullptr;
};

#endif // ACCOUNTWINDOW_H
