#include "Headers/chatserver.h"
#include "Headers/serverworker.h"
#include "Headers/parser.h"
#include "../Common/room.h"


#include <functional>
#include <QThread>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QTimer>
#include <QDebug>
#include <QJsonArray>


ChatServer::ChatServer(QObject *parent)
    : QTcpServer(parent)
    , m_idealThreadCount(qMax(QThread::idealThreadCount(), 1))
    , m_parser(new Parser(this))
    //depends on how many logical processors we have on the machine, in any case we are going to have a minimum thread count of 1
{
    m_availableThreads.reserve(m_idealThreadCount); //we try to allocate memory to at least the size of idealThreadCount
    m_threadsLoad.reserve(m_idealThreadCount);

    // connecting parser and chatserver signals and slots
    connect(this, &ChatServer::parseJson, m_parser, &Parser::parseJson);

    //we connect the client petitions
    connect(m_parser, &Parser::publicMessage, this, &ChatServer::broadcastAll, Qt::QueuedConnection);

    connect(m_parser, &Parser::userListRequest, this,&ChatServer::userListRequest, Qt::QueuedConnection );

    connect(m_parser, &Parser::updateStatus, this,&ChatServer::updateStatus, Qt::QueuedConnection );

    connect(m_parser, &Parser::newRoomRequest, this, &ChatServer::createRoom, Qt::QueuedConnection);
    connect(m_parser, &Parser::invitationsToRoom, this, &ChatServer::sendOutRoomInvitations, Qt::QueuedConnection);
    connect(m_parser, &Parser::roomMessage, this, &ChatServer::sendRoomMessage, Qt::QueuedConnection);
    connect(m_parser, &Parser::joinRoomRequest, this, &ChatServer::joinRoomRequest, Qt::QueuedConnection);
    connect(m_parser, &Parser::leaveRoom, this, &ChatServer::leaveRoom);
    connect(m_parser, &Parser::privateMessage, this , &ChatServer::broadcastOne, Qt::QueuedConnection);
    connect(m_parser, &Parser::roomUsersRequest, this, &ChatServer::roomUsersRequest);



}


ChatServer::~ChatServer(){
    //cerramos todos los procesos
    for(QThread *singleThread : m_availableThreads){
        singleThread -> quit();
        singleThread -> wait();
    }
}

void ChatServer::incomingConnection(qintptr socketDescriptor){
    ServerWorker *worker = new ServerWorker;
        if (!worker->setSocketDescriptor(socketDescriptor)) {
            worker->deleteLater();
            return;
        }
        int threadIdx = m_availableThreads.size();
        if (threadIdx < m_idealThreadCount) {
            m_availableThreads.append(new QThread(this));
            m_threadsLoad.append(1);
            //starting the thread we just appended so signals and slots work
            worker->moveToThread(m_availableThreads.at(threadIdx));
            m_availableThreads.last()->start();

        } else {
            //if we are full we add to the one with the least
            threadIdx = std::distance(m_threadsLoad.cbegin(), std::min_element(m_threadsLoad.cbegin(), m_threadsLoad.cend()));
            ++m_threadsLoad[threadIdx];
            worker->moveToThread(m_availableThreads.at(threadIdx));
        }



        connect(m_availableThreads.at(threadIdx), &QThread::finished, worker, &QObject::deleteLater);
        connect(m_availableThreads.at(threadIdx), &QThread::finished, this, &ChatServer::logFinished);
        connect(worker, &ServerWorker::disconnectedFromClient, this, std::bind(&ChatServer::userDisconnected, this, worker, threadIdx), Qt::QueuedConnection);

        connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));
        connect(worker, &ServerWorker::jsonReceived, this, std::bind(&ChatServer::jsonReceived, this, worker, std::placeholders::_1));
        connect(this, &ChatServer::stopAllClients, worker, &ServerWorker::disconnectFromClient);
        m_clients.append(worker);
        emit logMessage(QStringLiteral("New client Connected"));



}

void ChatServer::userListRequest(ServerWorker *sender){

    qDebug() << "received user list request, processing";
    QJsonArray usernames;
    QJsonValue name;
    for(int i =0 ; i <m_clients.size(); i++){
       name = m_clients[i]->userName();
       usernames.append(name);
    }


    QJsonObject userListJson;
    userListJson[QStringLiteral("type")]= QStringLiteral("USER_LIST");
    userListJson[QStringLiteral("usernames")] = usernames;

    QJsonDocument doc(userListJson);
    qDebug() << "userList: " << doc.toJson(QJsonDocument::Compact);

    sendJson(sender, userListJson);
}

void ChatServer::updateStatus(ServerWorker *sender, const int newStatus){
    int currentStatus = sender->getStatus();
    QString status;
    switch (newStatus) {
    case 1:
        status = QLatin1String("ACTIVE");
        break;
    case 2:
        status = QLatin1String("AWAY");
        break;
    case 3:
        status = QLatin1String("BUSY");
        break;
    default:
        break;
    }
    if(currentStatus==newStatus){

        QJsonObject warningMessage;
        warningMessage[QStringLiteral("type")] = QStringLiteral("WARNING");
        warningMessage[QStringLiteral("message")] = QStringLiteral("El estado ya es '") + status+QStringLiteral("'");
        warningMessage[QStringLiteral("operation")] = QStringLiteral("STATUS");
        warningMessage[QStringLiteral("status")] = status;
        sendJson(sender, warningMessage);
        return;
    }
    sender->setStatus(newStatus);
    QJsonObject statusUpdated;
    statusUpdated[QStringLiteral("type")] = QStringLiteral("NEW_STATUS");
    statusUpdated[QStringLiteral("username")] = sender->userName();
    statusUpdated[QStringLiteral("status")] = status;

    broadcastAll(statusUpdated,sender);

}

void ChatServer::createRoom(ServerWorker *sender, const QString &roomname){
    for(int i = 0; i<m_rooms.size(); i++){
        if(m_rooms[i]->getRoomName().compare(roomname, Qt::CaseInsensitive)==0){
            QJsonObject warningJson;
            warningJson[QStringLiteral("type")] = QStringLiteral("WARNING");
            warningJson[QStringLiteral("message")] = QStringLiteral("El cuarto '") +roomname+ QStringLiteral("' ya existe");
            warningJson[QStringLiteral("operation")] = QStringLiteral("NEW_ROOM");
            warningJson[QStringLiteral("roomname")] = roomname;
             sendJson(sender , warningJson);
             return;

        }
    }

    QJsonObject succesfulJson;
    succesfulJson[QStringLiteral("type")] = QStringLiteral("INFO");
    succesfulJson[QStringLiteral("message")] = QStringLiteral("success");
    succesfulJson[QStringLiteral("operation")] = QStringLiteral("NEW_ROOM");

    Room *newRoom = new Room(roomname, this);
    m_rooms.push_back(newRoom);
    newRoom->addInvitation(sender->userName());
    newRoom->addUser(sender->userName());
    sendJson(sender, succesfulJson);
    for(QString users : newRoom->getUsers()){
        qDebug() << users;
    }

}


void ChatServer::sendOutRoomInvitations(ServerWorker *sender,  const QString &roomName, QJsonArray usernames){
    qDebug() << "ChatServer::sendOutInvitations processing";
    //check if room exists

    bool roomFound = false;
    qDebug()<< m_rooms.size();
    for(Room *room : m_rooms){
        qDebug() << "rooms availables, sending out invitations: "<< room->getRoomName();
        if(room->getRoomName().compare(roomName, Qt::CaseSensitive)==0){

            roomFound = true;
            for(QJsonValue val : usernames){
                if(room->getUsers().contains(val.toString())){
                    return;
                }
                QJsonObject invitation;
                invitation[QStringLiteral("type")] = QStringLiteral("INVITATION");
                invitation[QStringLiteral("message")] = sender->userName() +QStringLiteral(" te invita al cuarto '") + roomName +QStringLiteral("'");
                invitation[QStringLiteral("username")] = sender->userName();
                invitation[QStringLiteral("roomname")] = roomName;

                QString operation = QStringLiteral("INVITE");

                broadcastOne( invitation,sender,val.toString(),operation);

                //add the user to the invitated list
                if(!room->getInvitations().contains(val.toString()))
                    room->addInvitation(val.toString());
            }


            break;
        }
    }

    if(!roomFound){
        QJsonObject roomNotFound;
        roomNotFound[QStringLiteral("type")] = QStringLiteral("WARNING");
        roomNotFound[QStringLiteral("message")] = QStringLiteral("El cuarto '") + roomName + QStringLiteral("' no existe");
        roomNotFound[QStringLiteral("operation")] = QStringLiteral("INVITE");
        roomNotFound[QStringLiteral("roomname")] = roomName;
        sendJson(sender, roomNotFound);
        return;
    }



    QJsonObject successJson;
    successJson[QStringLiteral("type")] = QStringLiteral("INFO");
    successJson[QStringLiteral("message")] = QStringLiteral("success");
    successJson[QStringLiteral("operation")] = QStringLiteral("INVITE");
    successJson[QStringLiteral("roomname")] = roomName;
    sendJson(sender, successJson);
}

void ChatServer::sendRoomMessage(ServerWorker *sender, const QString &roomName, const QString &message){
    //check if the user is a member of the room
    //check if the room exists

    qDebug() << "processing message request";
    bool roomFound = false;
    bool userInRoom= false;
    for(Room *room: m_rooms){
        if(room->getRoomName().compare(roomName, Qt::CaseSensitive)==0){
            for(QString username : room->getUsers()){
                qDebug() <<"in sending message"<< username;
                if(username.compare(sender->userName(), Qt::CaseSensitive) == 0){
                    userInRoom= true;
                    break;
                }
            }
            roomFound = true;
            break;
        }

    }

    if(!roomFound || !userInRoom){
        QJsonObject warningMessage;
        QString message;

        if(!roomFound){
            message = QStringLiteral("El cuarto '") + roomName + QStringLiteral("' no existe");

        }

        if(!userInRoom){
            message= QStringLiteral("El usuario no ha se ha unido al cuarto '") + roomName + QStringLiteral("'");
        }


        warningMessage[QStringLiteral("type")] = QStringLiteral("WARNING");
        warningMessage[QStringLiteral("message")] = message;
        warningMessage[QStringLiteral("operation")] = QStringLiteral("ROOM_MESSAGE");
        warningMessage[QStringLiteral("roomname")] = roomName;
        sendJson(sender, warningMessage);
        return;
    }





    //now we send the message to the users

    QJsonObject roomMessage;
    roomMessage[QStringLiteral("type")] = QStringLiteral("ROOM_MESSAGE_FROM");
    roomMessage[QStringLiteral("roomname")] = roomName;
    roomMessage[QStringLiteral("username")]    = sender->userName();
    roomMessage[QStringLiteral("message")] = message;
    broadcastRoom(roomMessage,sender,roomName);

}

void ChatServer::joinRoomRequest(ServerWorker *sender, const QString &roomName){
    qDebug() << "PROCESSING JOIN ROOOM REQUEST";
    QVector<QString> invitations;
    QVector<QString> users;
    bool invited = false;
    bool inRoom = false;
    for(Room *room :m_rooms){
        if(room->getRoomName().compare(roomName) ==0){
            //we found the room
            if(room->getInvitations().contains(sender->userName())){
                if(!room->getUsers().contains(sender->userName())){
                    for(QString invitation :room->getInvitations()){
                        qDebug() << "check if user is in invtiation list" << invitation;
                    }
                    // person was invited
                    room->addUser(sender->userName());
                    //tell user that they joined
                    QJsonObject success;
                    success[QStringLiteral("type")] = QStringLiteral("INFO");
                    success[QStringLiteral("message")] = QStringLiteral("success");
                    success[QStringLiteral("operation")] = QStringLiteral("JOIN_ROOM");
                    success[QStringLiteral("roomname")] = roomName;
                    QJsonObject userJoined;
                   userJoined[QStringLiteral("type")] = QStringLiteral("JOINED_ROOM");
                   userJoined[QStringLiteral("roomname")] = roomName;
                   userJoined[QStringLiteral("username")] = sender->userName();
                    broadcastRoom(userJoined,sender,roomName);
                    sendJson(sender, success);

                }




            }else{
                //person was not invited
               QJsonObject notInvited;
               notInvited[QStringLiteral("type")] = QStringLiteral("WARNING");
               notInvited[QStringLiteral("message")] = QStringLiteral("El usuario no a sido invitado al cuarto '") + roomName+ QStringLiteral("'");
               notInvited[QStringLiteral("operation")] = QStringLiteral("JOIN_ROOM");
               notInvited[QStringLiteral("roomname")] = roomName;
               sendJson(sender, notInvited);
            }
        }
    }




}

void ChatServer::roomUsersRequest(ServerWorker *sender, const QString &roomName){
    qDebug() << "processing room user request";
    for(Room *room:m_rooms){
        if(room->getRoomName().compare(roomName, Qt::CaseSensitive)==0){
            QVector<QString> users =room->getUsers();
            QJsonArray usersArray;
            for(QString username : users){
                usersArray.push_back(username);
            }
            QJsonObject userList;
            userList[QStringLiteral("type")] = QStringLiteral("ROOM_USER_LIST");
            userList[QStringLiteral("usernames")] = usersArray;
            sendJson(sender, userList);
            return;
        }
    }

    QJsonObject warning;
    warning[QStringLiteral("type")]= QStringLiteral("WARNING");
    warning[QStringLiteral("message")] = QStringLiteral("El cuarto '") + roomName + QStringLiteral("' no existe");
    warning[QStringLiteral("operation")] = QStringLiteral("ROOM_USERS");
    warning[QStringLiteral("roomname")] = roomName;
    sendJson(sender , warning);
}

void ChatServer::leaveRoom(ServerWorker *sender, const QString &roomName){
    qDebug()<< "kicking you out of the room";
    for(Room *room: m_rooms){
        if(room->getRoomName().compare(roomName)==0){
            if(room->getUsers().size()<= 1){
                //sice the user is the last person in the room , we can just delete it
                int index = m_rooms.indexOf(room, 0);
                m_rooms.remove(index);
                return;
            }
            if(room->getUsers().contains(sender->userName())){

                room->deleteUser(sender->userName());

                QJsonObject success;
                success[QStringLiteral("type")] = QStringLiteral("INFO");
                success[QStringLiteral("message")] = QStringLiteral("success");
                success[QStringLiteral("operation")] = QStringLiteral("LEAVE_ROOM");
                success[QStringLiteral("roomname")] = roomName;
                QJsonObject left;
                left[QStringLiteral("type")] = QStringLiteral("LEFT_ROOM");
                left[QStringLiteral("username")] = sender->userName();
                left[QStringLiteral("roomname")] = roomName;

                broadcastRoom(left, sender, roomName);

                sendJson(sender, success);




                return;
            }else{
                QJsonObject notInvited;
                notInvited[QStringLiteral("type")] = QStringLiteral("WARNING");
                notInvited[QStringLiteral("message")] = QStringLiteral("El usuario no a sido invitado al cuarto '") + roomName+ QStringLiteral("'");
                notInvited[QStringLiteral("operation")] = QStringLiteral("LEAVE_ROOM");
                notInvited[QStringLiteral("roomname")] = roomName;
                sendJson(sender, notInvited);
                return;
            }


        }


    }
    QJsonObject warning;
    warning[QStringLiteral("type")]= QStringLiteral("WARNING");
    warning[QStringLiteral("message")] = QStringLiteral("El cuarto '") + roomName + QStringLiteral("' no existe");
    warning[QStringLiteral("operation")] = QStringLiteral("LEAVE_ROOM");
    warning[QStringLiteral("roomname")] = roomName;
    sendJson(sender , warning);

}

void ChatServer::sendConnectedUsers(ServerWorker *sender){
    QJsonArray users;
    for(ServerWorker *worker : m_clients){
        QJsonValue username = worker->userName();
        users.append(username);

    }
    QJsonObject requestJson;
    requestJson[QStringLiteral("type")] = QStringLiteral("USER_LIST");
    requestJson[QStringLiteral("usernames")]= users;

    QJsonDocument doc(requestJson);
    qDebug() << "connect users json: "<<doc.toJson();

    sendJson(sender, requestJson);




}

void ChatServer::sendPrivateMessage(const QString &destination, const QJsonObject &message){

}

void ChatServer::logFinished(){
    qDebug() << "QThread::finished";
}

void ChatServer::sendJson(ServerWorker *destination, const QJsonObject &message)
{
    Q_ASSERT(destination);
    QJsonDocument doc(message);
    QString jsonStr = QString::fromUtf8(doc.toJson(QJsonDocument::Indented));
    qDebug()<<"ChatServer::sendJson, json being sent out"<<jsonStr;
    QTimer::singleShot(2000,Qt::VeryCoarseTimer ,destination, std::bind(&ServerWorker::sendJson, destination, message));
    //QTimer::singleShot(0, destination,SLOT( test()));

}


void ChatServer::broadcastAll(const QJsonObject &message, ServerWorker *exclude)
{

    for (ServerWorker *worker : m_clients) {
        Q_ASSERT(worker);
        if (worker == exclude)
            continue;
        sendJson(worker, message);
    }

}


void ChatServer::broadcastRoom(const QJsonObject &message, ServerWorker *sender, const QString &roomName){

    qDebug() << "in broadcast room" ;

    QVector<QString> usernames;

   for(Room *room : m_rooms){
       if(room->getRoomName().compare(roomName, Qt::CaseSensitive)==0){
           usernames = room->getUsers();
       }
   }


   for(int i = 0; i<usernames.size(); i++){

    qDebug() << "usernames" << usernames[i];
       for(int j = 0; j<m_clients.size(); j++){
           qDebug() << "client username " << m_clients[j]->userName();
           if(m_clients[j]->userName().compare(usernames[i], Qt::CaseSensitive)==0 && m_clients[j]->userName().compare(sender->userName(), Qt::CaseSensitive)!=0){
               qDebug() << "broadcast room sending message to user" << m_clients[j]->userName();
                sendJson(m_clients[j], message);
                break;
           }
       }
   }

}



void ChatServer::broadcastOne(const QJsonObject &message,ServerWorker *sender, const QString &destination, const QString &operation){
    bool userFound = false;
    for (ServerWorker *worker : m_clients) {
        Q_ASSERT(worker);
        if (worker->userName().compare(destination, Qt::CaseSensitive)==0){
            userFound = true;
            sendJson(worker, message);
            break;
        }

    }

    if(!userFound){
        const QJsonObject userNotFoundWarning;

        if(operation.compare(QLatin1String("MESSAGE"), Qt::CaseInsensitive)==0){
            QString message = QLatin1String("El usuario '") + destination + QLatin1String("' no existe");
            userNotFoundWarning[QStringLiteral("type")] = QStringLiteral("WARNING");
            userNotFoundWarning[QStringLiteral("message")] = message;
            userNotFoundWarning[QStringLiteral("operation")] = QStringLiteral("MESSAGE");
            userNotFoundWarning[QStringLiteral("username")] = destination;
        }else if(operation.compare(QLatin1String("INVITE"), Qt::CaseSensitive)==0){
            QString message = QLatin1String("El usuario '") + destination + QLatin1String("' no existe");
            userNotFoundWarning[QStringLiteral("type")] = QStringLiteral("WARNING");
            userNotFoundWarning[QStringLiteral("message")] = message;
            userNotFoundWarning[QStringLiteral("operation")] = QStringLiteral("INVITE");
            userNotFoundWarning[QStringLiteral("username")] = destination;
        }

    sendJson(sender,userNotFoundWarning);
    userFound=false;

    }

}




void ChatServer::jsonReceived(ServerWorker *sender, const QJsonObject &json)
{
    Q_ASSERT(sender);
    emit logMessage(QLatin1String("JSON received ") + QString::fromUtf8(QJsonDocument(json).toJson()));
    if (sender->userName().isEmpty())
        return jsonFromLoggedOut(sender, json);
    jsonFromLoggedIn(sender, json);
}

void ChatServer::userDisconnected(ServerWorker *sender, int threadIdx)
{
    --m_threadsLoad[threadIdx];
    m_clients.removeAll(sender);
    const QString userName = sender->userName();
    if (!userName.isEmpty()) {
        QJsonObject disconnectedMessage;
        disconnectedMessage[QStringLiteral("type")] = QStringLiteral("DISCONNECTED");
        disconnectedMessage[QStringLiteral("username")] = userName;
        broadcastAll(disconnectedMessage, nullptr);
        emit logMessage(userName + QLatin1String(" disconnected"));
    }

    //also deleteuserfrom rooms userlists and broadcast user left to each room
    QVector<QString> rooms= sender->getRooms();


    for(int i =0 ; i < m_rooms.size();i++){
        QString roomName = m_rooms[i]->getRoomName();
        for(int i = 0; i < rooms.size(); i++){
            if(roomName.compare(rooms[i], Qt::CaseSensitive)==0){
                if(m_rooms[i]->getUsers().size() <= 1){
                    //m_rooms.remove(i);
                    break;
                }

                //otherwise there are other users in the room so we bradcast
                QJsonObject userLeft;
                userLeft[QStringLiteral("type")] = QStringLiteral("LEFT_ROOM");
                userLeft[QStringLiteral("roomname")] = roomName;
                userLeft[QStringLiteral("username")] = sender->userName();
                m_rooms[i]->deleteUser(sender->userName());//deleting person from room
                broadcastRoom(userLeft, sender, roomName); //telling users the person has left the room


            }
        }
    }

    sender->deleteLater();
}



void ChatServer::userError(ServerWorker *sender)
{
    Q_UNUSED(sender)
    emit logMessage(QLatin1String("Error from ") + sender->userName());
}
/*!
 * \brief ChatServer::stopServer
 *
 */
void ChatServer::stopServer()
{
    emit stopAllClients();
    close();
}


void ChatServer::jsonFromLoggedOut(ServerWorker *sender, const QJsonObject &docObj)
{
    qDebug() << "ChatServer::jsonFromLoggedOut";
    Q_ASSERT(sender);
    const QJsonValue typeVal = docObj.value(QLatin1String("type"));
    if (typeVal.isNull() || !typeVal.isString())
        return;
    if (typeVal.toString().compare(QLatin1String("IDENTIFY"), Qt::CaseInsensitive) != 0)
        return;
    const QJsonValue usernameVal = docObj.value(QLatin1String("username"));
    if (usernameVal.isNull() || !usernameVal.isString())
        return;
    const QString newUserName = usernameVal.toString().simplified();
    if (newUserName.isEmpty())
        return;
    for (ServerWorker *worker : qAsConst(m_clients)) {
        if (worker == sender)
            continue;
        if (worker->userName().compare(newUserName, Qt::CaseInsensitive) == 0) {
            QJsonObject message;
            message[QStringLiteral("type")] = QStringLiteral("WARNING");
            message[QStringLiteral("message")] = QStringLiteral("El usuarion '") + newUserName + QStringLiteral("' ya existe");
            message[QStringLiteral("operation")] = QStringLiteral("IDENTIFY");
            message[QStringLiteral("username")] = newUserName;
            sendJson(sender, message);
            return;
        }
    }
    sender->setUserName(newUserName);

    QJsonObject successMessage;
    successMessage[QStringLiteral("type")] = QStringLiteral("INFO");
    successMessage[QStringLiteral("message")] = QStringLiteral("success");
    successMessage[QStringLiteral("operation")]= QStringLiteral("IDENTIFY");
    sendJson(sender, successMessage);

    QJsonObject connectedMessage;
    connectedMessage[QStringLiteral("type")] = QStringLiteral("NEW_USER");
    connectedMessage[QStringLiteral("username")] = newUserName;
    broadcastAll(connectedMessage, sender);
}




void ChatServer::jsonFromLoggedIn(ServerWorker *sender, const QJsonObject &doc){
    emit parseJson(sender, doc);
}
