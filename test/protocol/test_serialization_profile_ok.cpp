/*
 * Author: Franco Ruggeri
 */

#include <cte/protocol/ProfileOkMessage.h>
#include <QtCore/QSharedPointer>
#include <assert.h>

int main() {
    QSharedPointer<cte::Message> message1 = QSharedPointer<cte::ProfileOkMessage>::create();
    QSharedPointer<cte::Message> message2 = cte::Message::deserialize(message1->serialize());
    assert(*message1 == *message2);

    return 0;
}