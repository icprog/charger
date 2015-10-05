#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <QObject>
#include <QHostInfo>

#include "message_bus.h"
#include "charger_state.h"
#include "registeredtyperesolver.h"

namespace nzmqt {
    class ZMQSocket;
    class ZMQContext;
}

/**
 * @brief The ClientMessagingController class discovers the required zmq subcscription and
 * req/resp endpoints and connects/configures the appropriate sockets to the MessageBus class.
 * It continues to monitor the bonjour information and if the sockets change or go down it 
 * will re-create the messaging bus instance.
 * 
 * There are two states, CS_DISCOVERY and CS_CONNECTED.  Only when both endpoints to zmq
 * have been discovered and connected does the state change to CS_CONNECTED.  If the socket
 * endpoints (according to bonjour) change, the class goes back into the CS_DISCOVERY state.
 */
class ClientMessagingController : public QObject
{
    Q_OBJECT
public:
    enum State {
        DISCOVERY = 0,
        CONNECTED = 1
    };
    
    Q_ENUMS(State)

    Q_PROPERTY(MessageBus* messageBus READ messageBus NOTIFY messageBusChanged)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(ChargerState charger READ charger NOTIFY chargerChanged)
    Q_PROPERTY(QString hostname READ hostname NOTIFY hostnameChanged)
    Q_PROPERTY(int publishPort READ publishPort NOTIFY publishPortChanged)
    Q_PROPERTY(int messagePort READ messagePort NOTIFY messagePortChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    
    explicit ClientMessagingController(QObject *parent = 0);
    virtual ~ClientMessagingController();
    
    void init(int pub_port = 0, int msg_port = 0);
    
    MessageBus* messageBus() const { return _message_bus; }
    ChargerState* charger() const { return _charger_state; }
    
signals:
    void messageBusChanged();
    void chargerChanged();
    void stateChanged();
    void hostnameChanged();
    void publishPortChanged();
    void messagePortChanged();
    void connectedChanged();
    
protected slots:
    void routeStatusUpdated(const ChannelStatus& status);
    void routeDeviceInfoChanged(const DeviceInfo& info);
    
public slots:
    void resolvedService(QString type, QHostInfo addr, int port);
    void serviceResolutionError(QString type, int err);    
    void serviceRemoved(QString type);
        
private:
    bool connected() const { return _state == CONNECTED; }
                                             
    QString hostname() const { return _host; }
    void setHostname(QString value);
    
    int publishPort() const { return _pub_port; }
    void setPublishPort(int value);
    
    int messagePort() const { return _msg_port; }
    void setMessagePort(int value);
    
    State state() const { return _state; }
    void setState(State s);
    
    nzmqt::ZMQSocket* createSubscriberSocket();
    nzmqt::ZMQSocket* createRequestSocket();
    
    void closeRequestSocket();
    void closeSubscribeSocket();
    
    void closeMessagingHandler();
    void checkIsMessageBusReady();
    
    nzmqt::ZMQContext* _ctx;
    nzmqt::ZMQSocket* _reqresp_socket;
    nzmqt::ZMQSocket* _subscribe_socket;

    RegisteredTypeResolver* _resolve_message;
    RegisteredTypeResolver* _resolve_subscribe;
    
    MessageBus* _message_bus;
    
    // this would typically be a list of devices - but today the system supports only
    // a single iCharger on the bus - so this IS our entire data model.
    ChargerState* _charger_state;
    
    State _state;
    
    QString _host;
    int _pub_port, _msg_port;
};

#endif // TESTCONTROLLER_H
