/*
 * Author: Franco Ruggeri
 */

#include <cte/protocol/SignupOkMessage.h>

namespace cte {
    SignupOkMessage::SignupOkMessage() : Message(MessageType::signup_ok) {}

    SignupOkMessage::SignupOkMessage(const QJsonObject &json_object) : Message(MessageType::signup_ok) {}

    bool SignupOkMessage::operator==(const Message& other) const {
        const SignupOkMessage *o = dynamic_cast<const SignupOkMessage*>(&other);
        return o != nullptr && this->type() == o->type();
    }
}
