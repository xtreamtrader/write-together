/*
 * Author: Franco Ruggeri
 */

#include <protocol/ErrorMessage.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>

using namespace collaborative_text_editor;

int main() {
    const QString reason("test reason");

    QSharedPointer<Message> message1 = QSharedPointer<ErrorMessage>::create(reason);
    QSharedPointer<Message> message2 = Message::deserialize(message1->serialize());
    assert(*message1 == *message2);

    return 0;
}