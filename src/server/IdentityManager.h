/*
 * Identity manager. It provides an interface for: signup, login, logout, update profile.
 *
 * A session is authenticated and bound to a user after signup or login. Note that it is not thread-safe to use the
 * same session from different threads.
 *
 * Author: Franco Ruggeri
 */

#pragma once

#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <cte/protocol/Profile.h>

class IdentityManager {
    QHash<int,QString> sessions_;     // session_id -> username, for authenticated sessions
    mutable QMutex m_sessions_;

public:
    IdentityManager();
    bool signup(int session_id, const cte::Profile& profile, const QString& password);
    std::optional<cte::Profile> login(int session_id, const QString& username, const QString& password);
    void logout(int session_id);
    bool update_profile(int session_id, const cte::Profile& new_profile, const QString& new_password=QString{});

    bool authenticated(int session_id) const;
    std::optional<QString> username(int session_id) const;
};
