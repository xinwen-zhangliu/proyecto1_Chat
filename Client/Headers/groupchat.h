#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include <QObject>

#include <QDialog>
#include <QByteArray>
#include <QMessageBox>
#include <QStandardItemModel>


namespace Ui {class GroupChat;}

class GroupChat : public QDialog
{
    Q_OBJECT
public:
    explicit GroupChat( QString roomName,QWidget* parent);
    ~GroupChat();
private:
    Ui::GroupChat* ui;
    QString roomName;
    QStandardItemModel *m_chatModel;
public slots:
    void receivedRoomMessage(const QString sender, const QString &message);
private slots:
    void addUser();
    void getUserList();
    void leaveRoom();
    void sendMessage();
signals:

    void sendJson(const QJsonObject &json);


};

#endif // GROUPCHAT_H