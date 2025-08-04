#include "sessionmanager.h"

SessionManager::SessionManager(QObject *parent)
    : QObject(parent), m_userId(-1)
{
}

int SessionManager::userId() const {
    return m_userId;
}

void SessionManager::setUserId(int id) {
    if (m_userId != id) {
        m_userId = id;
        emit userIdChanged(id);
    }
}

QString SessionManager::username() const {
    return m_username;
}

void SessionManager::setUsername(const QString &name) {
    if (m_username != name) {
        m_username = name;
        emit usernameChanged(name);
    }
}

bool SessionManager::isLoggedIn() const {
    return m_userId != -1;
}

void SessionManager::logout() {
    setUserId(-1);
    setUsername("");
}
