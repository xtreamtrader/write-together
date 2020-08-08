/*
 * SQL injection protection: all the queries are done as prepared statements.
 *
 * Author: Franco Ruggeri
 */

#include "db_utility_secret.h"
#include <QtCore/QVariant>
#include <cte/database/db_utility.h>

namespace cte {
    static const QString driver_type("QMYSQL");
    static const QString database_name("collaborative_text_editor");
    static const QString hostname("127.0.0.1");
    static const QString username("collaborative_text_editor");
    static const QString password("?PdSPr0j3ct!");

    QSqlDatabase connect_to_database() {
        return connect_to_database(driver_type, database_name, hostname, username, password);
    }

    QSqlQuery query_select_profile(const QSqlDatabase& database, const QString& username, bool for_update) {
        QString query_string = QString{} +
                "SELECT * FROM user WHERE username=:username" +
                (for_update ? " FOR UPDATE" : "");
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":username", username);
        return query;
    }

    QSqlQuery query_insert_profile(const QSqlDatabase& database, const Profile& profile, const QString& password) {
        QString query_string = "INSERT INTO user (username, password, name, surname, icon) "
                               "VALUES (:username, :password, :name, :surname, :icon)";
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":username", profile.username());
        query.bindValue(":password", password);
        query.bindValue(":name", profile.name());
        query.bindValue(":surname", profile.surname());
        query.bindValue(":icon", profile.icon());
        return query;
    }

    QSqlQuery query_update_profile(const QSqlDatabase& database, const QString& old_username,
                                   const Profile& new_profile, const QString& new_password) {
        bool update_password = new_password.isNull();
        QString query_string = QString{} +
                "UPDATE user SET username=:username, " +
                (update_password ? "password=:password, " : "") +
                "name=:name, surname=:surname, icon=:icon WHERE username=:old_username";
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":old_username", old_username);
        query.bindValue(":username", new_profile.username());
        query.bindValue(":name", new_profile.name());
        query.bindValue(":surname", new_profile.surname());
        query.bindValue(":icon", new_profile.icon());
        if (update_password) query.bindValue(":password", new_password);
        return query;
    }

    QSqlQuery query_select_document(const QSqlDatabase& database, const Document& document, bool for_update) {
        QString query_string = QString{} +
                "SELECT * FROM document WHERE owner=:owner AND name=:name" +
                (for_update ? " FOR UPDATE" : "");
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":owner", document.owner());
        query.bindValue(":name", document.name());
        return query;
    }

    QSqlQuery query_select_document(const QSqlDatabase& database, const Document& document, const QString& username,
                                    bool for_update) {
        QString query_string = QString{} +
                               "SELECT * "
                               "FROM sharing s, document d "
                               "WHERE s.document_owner=d.owner AND s.document_name=d.name AND "
                               "      d.owner=:document_owner AND d.name=:document_name AND s.sharing_user=:username" +
                               (for_update ? " FOR UPDATE" : "");
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":document_owner", document.owner());
        query.bindValue(":document_name", document.name());
        query.bindValue(":username", username);
        return query;
    }

    QSqlQuery query_select_document(const QSqlDatabase& database, const QUrl& sharing_link) {
        QString query_string = "SELECT * "
                               "FROM document "
                               "WHERE sharing_link=:sharing_link";
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":sharing_link", sharing_link.toString());
        return query;
    }

    QSqlQuery query_select_document_profiles(const QSqlDatabase& database, const Document& document) {
        QString query_string = "SELECT username, name, surname, icon "
                               "FROM user u, sharing s, document d "
                               "WHERE u.username=s.sharing_user AND s.document_owner=d.owner AND s.document_name=d.name AND"
                               "      d.owner=:document_owner AND d.name=:document_name";
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":document_owner", document.owner());
        query.bindValue(":document_name", document.name());
        return query;
    }

    QSqlQuery query_select_document_text(const QSqlDatabase& database, const Document& document) {
        QString query_string = "SELECT index, value, author "
                               "FROM character "
                               "WHERE document_owner=:document_owner AND document_name=:document_name "
                               "SORT BY index";
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":document_owner", document.owner());
        query.bindValue(":document_name", document.name());
        return query;
    }

    QSqlQuery query_select_documents(const QSqlDatabase& database, const QString& username) {
        QString query_string = "SELECT * "
                               "FROM sharing "
                               "WHERE sharing_user=:username";
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":username", username);
        return query;
    }

    QSqlQuery query_insert_document(const QSqlDatabase& database, const Document& document,
                                    const QUrl& sharing_link) {
        QString query_string = "INSERT INTO document (owner, name, sharing_link) "
                               "VALUES (:owner, :name, :sharing_link)";
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":owner", document.owner());
        query.bindValue(":name", document.name());
        query.bindValue(":sharing_link", sharing_link.toString());
        return query;
    }

    QSqlQuery query_insert_sharing(const QSqlDatabase& database, const Document& document, const QString& username) {
        QString query_string = "INSERT INTO sharing (sharing_user, document_owner, document_name) "
                               "VALUES (:username, :document_owner, :document_name)";
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":document_owner", document.owner());
        query.bindValue(":document_name", document.name());
        query.bindValue(":username", username);
        return query;
    }

    QSqlQuery query_delete_document_text(const QSqlDatabase& database, const Document& document) {
        QString query_string = "DELETE FROM character "
                               "WHERE document_owner=:document_owner AND document_name=:document_name";
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":document_owner", document.owner());
        query.bindValue(":document_name", document.name());
        return query;
    }

    QSqlQuery prepare_query_insert_character(const QSqlDatabase& database, const Document& document) {
        QString query_string = "INSERT INTO character (document_owner, document_name, index, author, value "
                               "VALUES (:document_owner, :document_name, :index, :author, :value";
        QSqlQuery query(database);
        query.prepare(query_string);
        query.bindValue(":document_owner", document.owner());
        query.bindValue(":document_name", document.name());
        return query;
    }

    void bind_query_insert_character(QSqlQuery& query, unsigned int index, const QString& author, QChar value) {
        query.bindValue(":index", index);
        query.bindValue(":author", author);
        query.bindValue(":value", value);
    }
}