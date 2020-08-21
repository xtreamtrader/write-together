/*
 * Author: Antonino Musmeci, Stefano Di Blasio
 */


#pragma once

#include <optional>
#include <QtCore/QString>
#include <QtCore/QJsonObject>
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>
#include <cte/protocol/Message.h>
#include <cte/protocol/Document.h>
#include <cte/protocol/Profile.h>
#include <cte/crdt/Symbol.h>
#include <cte/client/utility.h>
#include <cte/client/fileInfo.h>
#include <cte/client/UserInfo.h>
#include <cte/network/Socket.h>
#define PORT 1111


using namespace cte;

class myClient : public QObject {
    Q_OBJECT
    QSharedPointer<QTimer> wait_on_connection_, connecting_interrupt_; // the second for qt backward compatibility
    int connection_attempts_;
    QSharedPointer<Message> message_to_send_;
    UserInfo new_user;
    QString host_address_, fallback_host_address_, host_to_connect_;
    quint16 port_;
    bool ssl_handshake_failed_;
    // only for qt backward compatibility
    QAbstractSocket::SocketState previous_state_;

public:
    Socket *socket;

//    Profile user;
    UserInfo user;

    myClient(QObject *parent = nullptr);

    void login(QString &email, QString &password);

    void send_message(const QSharedPointer<Message>& request);

//    std::tuple<bool, QString> signup(QString& username, QString& email, QString& password);

    void logout();


    void new_file(const QString& filename);

    bool change_password(const QString& new_password);

    void sendErase(int pos);

    void open_file(const QString& filename);


    void file_close(const fileInfo& file);


    bool change_username(const QString &new_username);

    std::optional<QString> get_uri(const QString &filename);

    void get_documents_form_server();

    void sendErase(const Document &document, const Symbol &s);

    void sendInsert(const Document &document, const Symbol &s);

    void send_cursor(Document document, Symbol cursor_position);

    void signup(QString &username, QString &email, QString &password, QString name, QString surname);

public slots:
    void connect(const QString& ip_address = "localhost", quint16 ip_port = 1111);

private slots:
    void handle_connection_error(QAbstractSocket::SocketError error); // mainly for server unreachable
    void handle_changed_state(QAbstractSocket::SocketState new_state);
    void timeout_on_connection();
    void handle_ssl_handshake(const QList<QSslError>& errors); // error in verifying the peer
    void connection_enctypted(); // the connection is established and encrypted
    void attempt_timeout(); // to retry if less than maximum attempts or to signal timeout error
    void process_response(); // elaborate server message (response)
    void process_data_from_server(); // process any "interactive" message from the server

signals:
    void generic_error(const QString& error);
    void host_connected(bool result);
    void timeout_expired(const QString& message_type);
    void authentication_result(bool authenticated, const QString& error_message);
    void profile_update_result(bool authenticated, const QString& error_message);
    void user_documents(const QSet<Document>& documents);
    void document(fileInfo& file);

    void user_added(const Profile& user_profile, int site_id);
    void user_removed(const QString& username, int site_id);
    void char_inserted(const Symbol& symbol);
    void char_removed(const Symbol& symbol);
    void cursor(const Symbol& symbol, const QString& username);
};


