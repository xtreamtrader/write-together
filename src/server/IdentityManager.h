/*
 * Author: Franco Ruggeri
 */

#pragma once

#include <QtCore/QSet>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <editor/protocol/Profile.h>

class IdentityManager {
public:
    bool signup(const editor::Profile& profile, const QString& password);
    std::optional<editor::Profile> login(const QString& username, const QString& password);
    bool update_profile(const QString& old_username, const editor::Profile& new_profile,
                        const QString& new_password=QString{});
};
