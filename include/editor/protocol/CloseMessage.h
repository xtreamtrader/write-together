/*
 * Author: Franco Ruggeri
 */

#pragma once

#include <QtCore/QString>
#include <QtCore/QJsonObject>
#include <editor/protocol/Message.h>
#include <editor/protocol/Document.h>

namespace editor {
    class CloseMessage : public Message {
        Document document_;
        std::optional<QString> username_;

        CloseMessage(const QJsonObject& json_object);
        QJsonObject json() const override;
        friend Message;

    public:
        CloseMessage(const Document& document);
        CloseMessage(const Document& document, const QString& username);
        bool operator==(const Message& other) const override;
        Document document() const;
        std::optional<QString> username() const;
    };
}
