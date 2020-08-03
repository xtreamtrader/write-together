/*
 * Author: Franco Ruggeri
 */

#include <editor/protocol/OpenMessage.h>
#include <editor/protocol/Document.h>
#include <editor/protocol/Profile.h>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>

int main() {
    const editor::Document document("test owner", "test name");
    const QString sharing_link("fnsc:test_uri");
    const int site_id = 1;
    const editor::Profile profile("test username", "test name", "test surname", QImage{});

    QSharedPointer<editor::Message> message1, message2;

    // with document (owner + name), without optional arguments
    message1 = QSharedPointer<editor::OpenMessage>::create(document);
    message2 = editor::Message::deserialize(message1->serialize());
    assert(*message1 == *message2);

    // with document (owner + name), with optional arguments
    message1 = QSharedPointer<editor::OpenMessage>::create(document, site_id, profile);
    message2 = editor::Message::deserialize(message1->serialize());
    assert(*message1 == *message2);

    // with sharing link
    message1 = QSharedPointer<editor::OpenMessage>::create(sharing_link);
    message2 = editor::Message::deserialize(message1->serialize());
    assert(*message1 == *message2);

    return 0;
}