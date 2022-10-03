#include "Headers/groupchat.h"
#include "../ui_groupchatwindow.h"

#include <QJsonObject>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QJsonArray>

GroupChat::GroupChat(QString roomName, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::GroupChat)
    , m_chatModel(new QStandardItemModel(this))
{

    this->roomName = roomName;
    ui->setupUi(this);
    m_chatModel->insertColumn(0);
    ui->chatView->setModel(m_chatModel);


    connect(ui->leaveBtn, &QPushButton::clicked, this, &GroupChat::leaveRoom);
    connect(ui->inviteBtn, &QPushButton::clicked, this, &GroupChat::addUser);
    connect(ui->userListBtn , &QPushButton::clicked, this , &GroupChat::leaveRoom);
    connect(ui->sendButton, &QPushButton::clicked, this , &GroupChat::sendMessage);


}

GroupChat::~GroupChat(){
    delete ui;
}

void GroupChat::receivedRoomMessage(const QString sender, const QString &message){

}

void GroupChat::addUser(){
    const QString username = QInputDialog::getText(
        this
        , tr("Write Username")
        , tr("Username of the person you want to add, please write one at a time, and they must be connected")
        , QLineEdit::Normal
        , QStringLiteral("username")
    );
    if(username.isEmpty())
        return;
    QJsonObject newUser ;
    QJsonValue usernameVal = username;
    QJsonArray user = {usernameVal};

   // user.push_back(usernameVal);
    newUser[QStringLiteral("type")] = QStringLiteral("INVITE");
    newUser[QStringLiteral("roomname")] = roomName;
    newUser[QStringLiteral("usernames")] = user;

    emit sendJson(newUser);
}

void GroupChat::sendMessage(){
    QJsonObject message;
    QString messageText = ui->messageEdit->text();
    message[QStringLiteral("type")] = QStringLiteral("ROOM_MESSAGE");
    message[QStringLiteral("roomname")] = roomName;
    message[QStringLiteral("message")]= messageText;


    ui->messageEdit->clear();
    //ui->chatView->append(messageText);

    m_chatModel->insertRow(m_chatModel->rowCount());
    //QModelIndex index = m_chatModel->index(m_chatModel->rowCount()-1);
    //m_chatModel->setData(index, messageText);
    m_chatModel->setData(m_chatModel->index(m_chatModel->rowCount(), 0), messageText);

    emit sendJson(message);


}

void GroupChat::getUserList(){
    QJsonObject getUserListJson;
    getUserListJson[QStringLiteral("type")] =QStringLiteral("ROOM_USERS");
    getUserListJson[QStringLiteral("roomname")] = roomName;

    emit sendJson(getUserListJson);

}

void GroupChat::leaveRoom(){
    QJsonObject leaveRoomJson;
    leaveRoomJson[QStringLiteral("type")] = QStringLiteral("LEAVE_ROOM");
    leaveRoomJson[QStringLiteral("roomname")] = roomName;
    emit sendJson(leaveRoomJson);
}
