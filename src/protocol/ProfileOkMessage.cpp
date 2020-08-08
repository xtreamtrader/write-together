/*
 * Author: Franco Ruggeri
 */

#include <cte/protocol/ProfileOkMessage.h>

namespace cte {
    ProfileOkMessage::ProfileOkMessage() : Message(MessageType::profile_ok) {}

    ProfileOkMessage::ProfileOkMessage(const QJsonObject &json_object) : Message(MessageType::profile_ok) {}

    bool ProfileOkMessage::operator==(const Message& other) const {
        const ProfileOkMessage *o = dynamic_cast<const ProfileOkMessage*>(&other);
        return o != nullptr && this->type() == o->type();
    }
}
