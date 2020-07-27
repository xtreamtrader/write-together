/*
 * Author: Antonino Musmeci
 */



#pragma once
#include <QStackedWidget>
#include <QListWidgetItem>
#include "newFileDialog.h"
#include "myClient.h"
#include "changePasswordDialog.h"
#include "changeUsernameDialog.h"

namespace Ui {
    class loginTextEditor;

}

class loginTextEditor: public QStackedWidget {
    Q_OBJECT




public:
    explicit loginTextEditor(QWidget *parent = nullptr);
    void open_editor(QString filename);

private:
    std::shared_ptr<myClient> client;
    Ui::loginTextEditor *ui;
    std::shared_ptr< newFileDialog> file_dialog;
//    newFileDialog * file_dialog;
    std::shared_ptr<changeUsernameDialog> changeuser_dialog;
    std::shared_ptr<changePasswordDialog> changepass_dialog;
    texteditor * editor;
    void init_user_page(std::vector<QString>);
//    void open_editor(QString filename);
    void cleanAll();

private slots:
    void on_connect_pushButton_clicked();
    void on_login_signup_pushButton_clicked();
    void on_signup_login_pushButton_clicked();
    void on_login_signin_pushButton_clicked();
    void on_singup_register_pushButton_clicked();
    void on_user_create_file_pushButton_clicked();
    void on_user_change_password_pushButton_clicked();
    void on_user_logout_pushButton_clicked();
    void on_user_file_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_user_change_username_pushButton_clicked();
    void on_user_share_pushButton_clicked();
    void share_file(QString filename);

};




