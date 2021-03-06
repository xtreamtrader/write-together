#include <cte/protocol/create_message.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>
#include <cassert>

int main() {
    const QString document_name("test name");

    QSharedPointer<cte::Message> message1 = QSharedPointer<cte::CreateMessage>::create(document_name);
    QSharedPointer<cte::Message> message2 = cte::Message::deserialize(message1->serialize());
    assert(*message1 == *message2);

    return 0;
}