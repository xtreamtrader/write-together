/*
 * Author: Antonino Musmeci
 */

#pragma once
#define APPLICATION "TEXTEDITOR"
#include <QMainWindow>
#include <QStackedWidget>
#include <QDockWidget>
#include <QPointer>
#include <qtextedit.h>
#include <QListWidget>
#include "crdt/SharedEditor.h"
#include "myClient.h"
#include "fileInfo.h"
using namespace collaborative_text_editor;
class texteditor : public QMainWindow{
    Q_OBJECT


public:
    texteditor(QStackedWidget *parent, std::shared_ptr<myClient> ,fileInfo file);
    bool change_from_server;
    void setupFileActions();
    void closeEvent(QCloseEvent *event) override;
signals:
    void show_user_page();
    void share_file(const QString string);

private slots:

    void file_to_pdf();
    void file_share();
    void file_close();

    void setupEditActions();
    void readyRead();
    void contentsChange(int position, int charsRemoved, int charsAdded);

private:
    QDockWidget *connected_client ;
    QTextEdit *editor;
    std::shared_ptr<myClient> client;
    std::shared_ptr<SharedEditor> shared_editor;
    QAction *actionUndo;
    QAction *actionRedo;
    fileInfo file;
    QListWidget *list_user;

#ifndef QT_NO_CLIPBOARD
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
#endif



};



