#pragma once

#include <QtCore/QJsonObject>
#include <cte/protocol/message.h>
#include <cte/protocol/document.h>
#include <cte/protocol/format.h>
#include <cte/crdt/symbol.h>

namespace cte {
    class InsertMessage : public Message {
        Document document_;
        Symbol symbol_;
        Format format_;

        explicit InsertMessage(const QJsonObject& json_object);
        QJsonObject json() const override;
        friend Message;

    public:
        InsertMessage(const Document& document, const Symbol& symbol, const Format& format);
        bool operator==(const Message& other) const override;
        Document document() const;
        Symbol symbol() const;
        Format format() const;
    };
}
