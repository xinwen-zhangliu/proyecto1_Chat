#ifndef PARSER_H
#define PARSER_H



#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

class ChatClient;

class Parser : public QObject
{
    Q_OBJECT


public:
    explicit Parser(QObject* parent = nullptr);
public slots:
    void parseJson(const QJsonObject &json);
signals:
    void loggedIn(const QString &username);
    void loginError(const QString &reason);
    void publicMessageReceived(const QString &sender, const QString &text);
    void privateMessageReceived(const QString &sender, const QString &message);
    void roomMessageReceived(const QString &sender, const QString &roomName, const QString &message);
    void userJoined(const QString &username);
    void userLeft(const QString &username);
    void receivedUserList( const QJsonArray &list);
    void sendJson(const QJsonObject &json);
    void newStatus(const QString &username, const int &newStatus);
    void newRoomCreated();
    void errorCreatingRoom(const QString &roomName);
    void showJson(const QString &json);
    void newRoomRejected();
    void invitationReceived(const QString &roomName, const QString &message, const QString &sender);
    void userJoinedRoom(const QString &roomName, const QString &user);
    void userLeftRoom(const QString &roomName, const QString &user);
    void receivedRoomUserList( const QJsonArray &list);




};

#endif // PARSER_H
