#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QObject>

class SessionManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int userId READ userId NOTIFY userIdChanged)
    Q_PROPERTY(QString username READ username NOTIFY usernameChanged)
public:
    explicit SessionManager(QObject *parent = nullptr);

    int userId() const;
    void setUserId(int id);

    QString username() const;
    void setUsername(const QString &name);

    bool isLoggedIn() const;
    void logout();

signals:
    void userIdChanged(int);
    void usernameChanged(const QString &);


private:
    int m_userId = -1;
    QString m_username;
};

#endif // SESSIONMANAGER_H
